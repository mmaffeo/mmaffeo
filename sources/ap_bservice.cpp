
/*
    This module implements the "Bobcat Service" tool command set.
*/



#include "hw_io.h"
#include <string.h>

#include "ap_bservice.h"
#include "ap_bservice_dv.h"
#include "ap_bservice_prog.h"

#include "nvm_ecuid.h"
#include "ap_version.h"
#include "ap_hwt.h"
#include "global.h"

#include "ap_eeprom.h"


const uint16_t ts_base_address  = 0x0f00;
const uint16_t hwt_base_address = 0x1000; // two additional blocks are also used.

///////////////////////////////////////////////////////////////////////////////////////////////////
// bservice dv block definition
#ifdef BB_COMPILE
extern
#endif
    uint8_t bb_status;

const uint16_t ZEROS=0;
const uint8_t * p_sw_title = sw_title;

const void * const bservice_dv_table[] =
{
    NULL                           , // 0
    &sw_type               , // 1
    &sw_version_major          , // 2
    &sw_version_minor          , // 3
    &hw_version              , // 4
    &nvm_ecuid.bobcat_module_id    , // 5
    &p_sw_title               , // 6
    &bb_status                 , // 7
    &sw_ed_number                  , // 8
    &ZEROS                         , // 9
    &hwt_support_level             , // 10
    &hwt_base_address              , // 11
    &nvm_ecuid.j1939_source_address, // 12
    &nvm_ecuid.ap_sw_code_smask    , // 13
    &nvm_ecuid.ap_sw_const_smask   , // 14
    &ts_base_address         , // 15
};


dv_table_block bservice_dv_block;

uint8_t bservice_dv_read_byte(uint16_t i)
{
    uint8_t rvalue = 0;

    switch (i)
    {
        case 1:    case 2:    case 3:
        case 5:    case 7:
            rvalue = *(uint8_t*)bservice_dv_table[i];
            break;
    }
    return rvalue;
}

uint16_t bservice_dv_read_word(uint16_t i)
{
    uint16_t rvalue = 0;

    if ((i == 6)
        || ((i >= 8) && (i < (sizeof(bservice_dv_table) / sizeof(const uint8_t * const)))) )
    {
        rvalue = *(uint16_t*)bservice_dv_table[i];
    }
    return rvalue;
}

static void bservice_dv_block_initialize(void)
{
    bservice_dv_block.initialize(0);
    bservice_dv_block.set_read_byte_f(bservice_dv_read_byte);
    bservice_dv_block.set_read_word_f(bservice_dv_read_word);
    
    dv_list.add_block(&bservice_dv_block);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
///////////////////////////////////////////////////////////////////////////////////////////////////
// CAN01 heartbeat message
///////////////////////////////////////////////////////////////////////////////////////////////////
static uint8_t CAN01_tx_msg_cnt=0;

bool CAN01_tx_enable=true;

static void CAN01_tx_msg_update(void)
{
    if (CAN01_tx_enable)
    {
        if (CAN01_tx_msg_cnt > 0 )
        {
            --CAN01_tx_msg_cnt ;
        }
        else
        {
            CAN01_tx_msg_cnt = 250;

            hw_can_msg_t msg_data;

            msg_data.id.set_J1939ID(6, 0xFF, 0xFF,nvm_ecuid.j1939_source_address );
            msg_data.DLR = 0x08;
            msg_data.set_byte(0,1);
            msg_data.set_byte(1, nvm_ecuid.bobcat_module_id );
            msg_data.set_byte(2, nvm_ecuid.j1939_source_address );
            msg_data.set_byte(3, bservice_dv_read_byte(1));//sw_type;
            msg_data.set_byte(4, bservice_dv_read_byte(2));//sw_version_major;
            msg_data.set_byte(5, bservice_dv_read_byte(3));//sw_version_minor;
            msg_data.set_byte(6, 0xFF);
            msg_data.set_byte(7, 0xFF);

            #ifdef HWC_CAN0
            hw_can_txq[HWC_CAN0].send_msg(&msg_data);
            #endif

            #ifdef HWC_CAN4
            hw_can_txq[HWC_CAN4].send_msg(&msg_data);
            #endif
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
#endif

static bool process_bservice_cmd(const hw_can_msg_t *request,
                                       hw_can_msg_t *response );

// 8-byte limited PGN 0xEF00 coming from source addresses
//                  0xF9 - DV tool
//                  0xFA - Download tool

hw_can_rxmsg j1939_propA_rx[HWC_CAN_QTY];


static void unpack_bservice_request(hw_can_msg_t *msg, uint8_t port)
{
    uint8_t da = msg->id.get_J1939_DA();
    uint8_t sa = msg->id.get_J1939_SA();

    hw_can_msg_t response_mbuff;

    if ((da==0xFF || da==nvm_ecuid.j1939_source_address ) &&
        (sa==0xF9 || sa==0xFA)                                 )
    {
        uint8_t resp = process_bservice_cmd(msg, &response_mbuff);

        if (resp)
            hw_can_txq[port].send_msg(&response_mbuff);
    }
}

static void unpack_bservice_request_0(hw_can_msg_t *msg) { unpack_bservice_request(msg,HWC_CAN0); }
static void unpack_bservice_request_1(hw_can_msg_t *msg) {
                                                            #ifdef HWC_CAN4
                                                                unpack_bservice_request(msg,HWC_CAN4);
                                                            #endif
                                                         }



void ap_bservice_initialize(void)
{
    if (bb_smode == BB_SMODE_CAPTURED)
        bservice_prog_mode.Set();  // activate the bobcat service tool programming mode
    else
        bservice_prog_mode.Clear();

    if ( bservice_prog_mode.Active() )
    {   // send an intial acknowledgement
        hw_can_msg_t response_mbuff;
        response_mbuff.id.set_J1939ID(6,0xEF,0xFA, nvm_ecuid.j1939_source_address);
        response_mbuff.DLR=6;
        response_mbuff.DSR[0] = 0x0B;
        response_mbuff.DSR[1] = 0x83;
        response_mbuff.DSR[2] = 0x82;
        response_mbuff.DSR[3] =    0;
        response_mbuff.DSR[4] =   10;
        response_mbuff.DSR[5] =   10;

        for (uint8_t i = 0; i<HWC_CAN_QTY; ++i)
            hw_can_txq[i].send_msg(&response_mbuff);  // send initial ack on each can port...
    }

    for (uint8_t i = 0; i<HWC_CAN_QTY; ++i)
    {
        j1939_propA_rx[i].rx_id     .set_J1939ID(0, 0xEF, 0x00, 0x00);
        j1939_propA_rx[i].rx_id_mask.set_J1939ID(0, 0xFF, 0x00, 0x00);
        j1939_propA_rx[i].rx_callback = i==0? unpack_bservice_request_0:unpack_bservice_request_1 ;
        j1939_propA_rx[i].initialize();

        hw_can_rx_handler[i].add_msg    (&j1939_propA_rx[i]    );
    }

    bservice_dv_block_initialize();

    //CAN01_tx_msg_update();
}

ap_bservice_pending_reset_t ap_bservice_pending_reset=NONE;
uint8_t                     ap_bservice_pending_reset_countdown = 0;

void ap_bservice_update    (void)
{
    if (ap_bservice_pending_reset != NONE)
    {
        if ( (ap_bservice_pending_reset_countdown == 0) && (eeMode == EE_IDLE))
        {
            switch(ap_bservice_pending_reset)
            {
                case TO_BB_SMODE_CAPTURED: hw_reset_force(BB_SMODE_CAPTURED,0); break;
                default:                   hw_reset_force(0,0);                 break;

            }
        }
        else
        {
            --ap_bservice_pending_reset_countdown;
        }
    }

    //CAN01_tx_msg_update();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//
static bool process_bservice_cmd(const hw_can_msg_t *request,
                                         hw_can_msg_t *response )
{
    uint8_t sa = request->id.get_J1939_SA();
    bool respond=true;

    response->id.set_J1939ID(6, 0xEF, sa, nvm_ecuid.j1939_source_address);

    switch (request->DSR[0])
    {
        case 0x07:  // read  word command
        {
            response->DLR = 5;
            response->DSR[0]    = request->DSR[0];
            uint8_t address_LSB = request->DSR[1];
            uint8_t address_MSB = request->DSR[2];
            response->DSR[1]    = address_LSB;
            response->DSR[2]    = address_MSB;

            uint16_t address =  (uint16_t) 0x0100 * address_MSB + address_LSB;
            uint16_t data = dv_list.read_word(address);

            // reply LSB first
            response->DSR[3] = (uint8_t)  data;
            response->DSR[4] = (uint8_t) (data>>8);


        }   break;
        case 0x08:  // write byte command
        {
            uint8_t  address_LSB = request->DSR[1];
            uint8_t  address_MSB = request->DSR[2];
            uint16_t address     = (uint16_t) 0x0100u * address_MSB + address_LSB;

            dv_list.write_byte(address, request->DSR[3]);

            respond = false;

        }   break;
        case 0x09:  // read  byte command
        {
            response->DLR = 5;
            response->DSR[0] = request->DSR[0];
            uint8_t address_LSB = request->DSR[1];
            uint8_t address_MSB = request->DSR[2];
            response->DSR[1] = address_LSB;
            response->DSR[2] = address_MSB;

            uint16_t address = (uint16_t) 0x0100u * address_MSB + address_LSB;
            uint8_t  data = dv_list.read_byte(address);

            response->DSR[3] = 0x00;
            response->DSR[4] = data;

        }   break;
        case 0x0A:  // write word command
         {  uint8_t  address_LSB = request->DSR[1];
            uint8_t  address_MSB = request->DSR[2];
            uint16_t address =  (uint16_t) 0x0100u * address_MSB + address_LSB;

            uint8_t data_LSB = request->DSR[3];
            uint8_t data_MSB = request->DSR[4];
            uint16_t data = (uint16_t) 0x0100u * data_MSB + data_LSB;

            dv_list.write_word(address, data);

            respond = false;

        }   break;
        case 0x0B:  // programming command
            respond = process_bservice_prog_cmd(request, response);
            break;
        case 0x0C:  // write word absolute command
        case 0x0D:  // write byte absolute command
            respond = false;
            break;
        case 0x0E:  //  read word absolute command
        case 0x0F:  //  read byte absolute command
        {
            uint32_t address;
            uint16_t data;

            address = request->DSR[4];
            address <<= 8;
            address |= request->DSR[3];
            address <<= 8;
            address |= request->DSR[2];
            address <<= 8;
            address |= request->DSR[1];

            if (request->DSR[0]== 0x0E)
            {
                data =  hw_readWordDirect(address);
            }
            else
            {
                data =  hw_readByteDirect(address);
            }

            response->DLR=7;
            response->DSR[0] = request->DSR[0];
            response->DSR[1] = request->DSR[1];
            response->DSR[2] = request->DSR[2];
            response->DSR[3] = request->DSR[3];
            response->DSR[4] = request->DSR[4];
            response->DSR[5] = data & 0xFFu;
            response->DSR[6] = data >> 8;

            respond = true;
        }   break;

        case 0x10:  // read dword command
        {
            response->DLR = 7;
            response->DSR[0]    = request->DSR[0];
            uint8_t address_LSB = request->DSR[1];
            uint8_t address_MSB = request->DSR[2];
            response->DSR[1]    = address_LSB;
            response->DSR[2]    = address_MSB;

            uint16_t address =  (uint16_t) 0x0100 * address_MSB + address_LSB;
            uint32_t data = dv_list.read_dword(address);

            // reply LSB first
            response->DSR[3] = (uint8_t) data;
            data >>= 8;
            response->DSR[4] = (uint8_t) data;
            data >>= 8;
            response->DSR[5] = (uint8_t) data;
            data >>= 8;
            response->DSR[6] = (uint8_t) data;

        }   break;

        case 0x11:  // write dword command
        {
            uint32_t data;
            uint8_t  address_LSB = request->DSR[1];
            uint8_t  address_MSB = request->DSR[2];
            uint16_t address =  (uint16_t) 0x0100u * address_MSB + address_LSB;

            data  = request->DSR[6];
            data <<= 8;
            data |= request->DSR[5];
            data <<= 8;
            data |= request->DSR[4];
            data <<= 8;
            data |= request->DSR[3];


            dv_list.write_dword(address, data);

            respond = false;

        }   break;


        case 0x12:  // read dword absolute command
        {
            uint32_t address;
            uint32_t data;

            address = request->DSR[4];
            address <<= 8;
            address |= request->DSR[3];
            address <<= 8;
            address |= request->DSR[2];
            address <<= 8;
            address |= request->DSR[1];

            data =  hw_readDwordDirect(address);
            
            response->DLR=5;
            response->DSR[0] = request->DSR[0];

            // reply LSB first
            response->DSR[1] = (uint8_t) data;
            data >>= 8;
            response->DSR[2] = (uint8_t) data;
            data >>= 8;
            response->DSR[3] = (uint8_t) data;
            data >>= 8;
            response->DSR[4] = (uint8_t) data;

            respond = true;
        }   break;

        default:
            respond = false;
            break;
    }

    return respond;
}

