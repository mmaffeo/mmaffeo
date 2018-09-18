
#include "hw_io.h"
#include <string.h>
#include <stdlib.h>

#include "ap_bservice_dv.h"
#include "ap_hwt.h"
#include "nvm_ecuid.h"

const uint16_t hwt_support_level=2;

uint16_t hwt_access_level;
uint16_t hwt_access_seed;

void hwt_txCANMessage(uint16_t channel);

///////////////////////////////////////////////////////////////////////////////////////////////////
// fcall I/O table....
///////////////////////////////////////////////////////////////////////////////////////////////////

dv_table_block  hwt_fio_block;

// DIN block range
#define MIN_DIN_I 0
#define MAX_DIN_I (MIN_DIN_I + HW_DIN_BANK_QTY -1)

// ADC block index range
#define MIN_ADC_I (MAX_DIN_I + 1                 )
#define MAX_ADC_I (MIN_ADC_I +   HWC_ADC_QTY   -1)

// FIN block index range
#define MIN_FIN_I (MAX_ADC_I + 1                 )
#define MAX_FIN_I (MIN_FIN_I + 2*HWC_FIN_QTY   -1)

// DOUT block range
#define MIN_DOUT_I (MAX_FIN_I + 1)
#define MAX_DOUT_I (MIN_DOUT_I + HW_DOUT_BANK_QTY - 1)

// PWM block index range
#define MIN_PWM_I (MAX_DOUT_I + 1               )
#define MAX_PWM_I (MIN_PWM_I +  2*HWC_PWM_QTY -1 )

// GAUGE block index range
#define MIN_GAUGE_I (MAX_PWM_I + 1               )
#define MAX_GAUGE_I (MIN_GAUGE_I +  HWC_GAUGE_QTY -1 )



uint16_t hwt_fio_read(uint16_t i)
{
    uint16_t rvalue=0;

    if      (i <= MAX_DIN_I )
    {
        rvalue = hw_din_GetBank(i - MIN_DIN_I) ;
    }
    else if (i <= MAX_ADC_I )
    {
        rvalue = hw_adc_GetValue((hw_adc_ch_t)(i-MIN_ADC_I));
    }
    else if (i <= MAX_FIN_I )
    {
        uint8_t j = i - MIN_FIN_I;
        uint32_t p =  hw_fin_GetPerioduS((hw_fin_ch_t)(j>>1));

        if (j&0x01) rvalue = p >> 16;      // MSW
        else    rvalue = p & 0xFFFF;   // LSW
    }
    else if (i <= MAX_DOUT_I )
    {
        rvalue = hw_dout_GetBank(i - MIN_DOUT_I);
    }
    else if ( i <= MAX_PWM_I )
    {
        uint8_t j = i - MIN_PWM_I;

        if (j < HWC_PWM_QTY)
            rvalue = hw_pwm_GetRatio16((hw_pwm_ch_t)j);
        else
            rvalue = hw_pwm_GetFrequency((hw_pwm_ch_t)(j- HWC_PWM_QTY));
    }
    else if ( i <= MAX_GAUGE_I )
    {
        uint8_t j = i - MIN_GAUGE_I;

        rvalue = hw_gauge_GetPosition((hw_gauge_ch_t)j);
    }

    return rvalue;
}


void hwt_fio_write(uint16_t i, uint16_t data)
{
    if (hwt_access_level >= 2)
    {
        if ( i >= MIN_DOUT_I && i <= MAX_DOUT_I)
        {
            hw_dout_SetBank(i - MIN_DOUT_I, data);
        }
        else if ( i >= MIN_PWM_I && i <= MAX_PWM_I)
        {
            uint8_t j = i - MIN_PWM_I;
            if (j < HWC_PWM_QTY)
                hw_pwm_SetRatio16((hw_pwm_ch_t)j, data);
            else
                hw_pwm_SetFrequency((hw_pwm_ch_t)(j - HWC_PWM_QTY), data );
        }
        else if ( i >= MIN_GAUGE_I && i <= MAX_GAUGE_I)
        {
            hw_gauge_SetPosition((hw_gauge_ch_t)(i- MIN_GAUGE_I), data);
        }
    }
}





///////////////////////////////////////////////////////////////////////////////////////////////////
// hwt_io table
///////////////////////////////////////////////////////////////////////////////////////////////////


const uint16_t HWT_DIN_QTY    = HWC_DIN_QTY;
const uint16_t HWT_DIN_BASE   = 0x1100  | MIN_DIN_I;
const uint16_t HWT_ADC_QTY    = HWC_ADC_QTY;
const uint16_t HWT_ADC_BASE   = 0x1100  | MIN_ADC_I;
const uint16_t HWT_FIN_QTY    = HWC_FIN_QTY;
const uint16_t HWT_FIN_BASE   = 0x1100  | MIN_FIN_I;
const uint16_t HWT_DOUT_QTY   = HWC_DOUT_QTY;
const uint16_t HWT_DOUT_BASE  = 0x1100  | MIN_DOUT_I;
const uint16_t HWT_PWM_QTY    = HWC_PWM_QTY;
const uint16_t HWT_PWM_BASE   = 0x1100  | MIN_PWM_I;
const uint16_t HWT_GAUGE_QTY  = HWC_GAUGE_QTY;
const uint16_t HWT_GAUGE_BASE = 0x1100  | MIN_GAUGE_I;
const uint16_t HWT_FCALL_BASE = 0x1200 ;


const uint16_t* const hwt_io_table[] =
{
    &hwt_access_level,  // + 0
    &hwt_access_seed ,  // + 1
    NULL           ,    // + 2
    &HWT_DIN_QTY   ,    // + 3
    &HWT_DIN_BASE  ,    // + 4
    &HWT_ADC_QTY   ,    // + 5
    &HWT_ADC_BASE  ,    // + 6
    &HWT_FIN_QTY   ,    // + 7
    &HWT_FIN_BASE  ,    // + 8
    &HWT_DOUT_QTY  ,    // + 9
    &HWT_DOUT_BASE ,    // +10
    &HWT_PWM_QTY   ,    // +11
    &HWT_PWM_BASE  ,    // +12
    &HWT_GAUGE_QTY ,    // +13
    &HWT_GAUGE_BASE,    // +14
    &HWT_FCALL_BASE,    // +15
};


dv_table_block  hwt_block;

uint16_t hwt_io_read(uint16_t i)
{
    uint16_t rvalue=0;

    if (i == 1)
    {
        do { hwt_access_seed = rand(); }
        while ( hwt_access_seed==0 );    // can't send a "seed" of zero.

        rvalue = hwt_access_seed;
    }
    else if (i != 2)    // HWT_ACCESS_KEY
    {
        rvalue = *hwt_io_table[i];
    }

    return rvalue;
}


void hwt_io_write(uint16_t i, uint16_t data)
{
    if ( i == 2 )       // HWT_ACCESS_KEY
    {
        if ( hwt_access_seed != 0 &&
             data== ((hwt_access_seed&0xFA5F) + 2) )
        {
            hw_reset_force(1, 1);
        }
        else
        {
            hwt_access_seed = 0;

            if (hwt_access_level != 1)
                hw_reset_force(1,0);
        }
    }

}




///////////////////////////////////////////////////////////////////////////////////////////////////
// function call block
///////////////////////////////////////////////////////////////////////////////////////////////////
#define HWT_RESET_FORCE          0
#define HWT_RESET_SMODES         1
#define HWT_MCU_HARDWARE_ID      2
#define HWT_MCU_POWER_HOLD       3
#define HWT_CLOCK_US             4
#define HWT_CLOCK_MS             5
#define HWT_CLOCK_S              6
#define HWT_NVM_EEPROM_STATUS    8
#define HWT_NVM_EEPROM_SECTION   9
#define HWT_NVM_EEPROM_ADDRESS   10
#define HWT_NVM_EEPROM_ERASE     11
#define HWT_NVM_EEPROM_READ      12
#define HWT_NVM_EEPROM_WRITE     13
#define HWT_NVM_EEPROM_CHECKSUM  14
#define HWT_NVM_EEPROM_TCMD      15
#define HWT_NVM_EEPROM_TSTATE    16
#define HWT_NVM_EEPROM_TFAILURES 17
#define HWT_CAN_LOOPBACK         19

dv_table_block  hwt_fcall_block;


uint16_t hwt_eeprom_status;
uint16_t hwt_eeprom_section;
uint16_t hwt_eeprom_address;

uint16_t hwt_fcall_read(uint16_t i)
{
    uint16_t rvalue=0;

    if (hwt_access_level >= 2)
    switch (i)
    {
        case HWT_RESET_SMODES:
            rvalue = 0x0100*hw_reset_get_bb_smode() + hw_reset_get_ap_smode();
            break;
        case HWT_MCU_HARDWARE_ID:   rvalue = hw_mcu_HardwareID();   break;
        case HWT_MCU_POWER_HOLD:    rvalue = hw_mcu_GetPowerHold(); break;
        case HWT_CLOCK_US:          rvalue = hw_clock_uS();         break;
        case HWT_CLOCK_MS:          rvalue = hw_clock_mS();         break;
        case HWT_CLOCK_S:           rvalue = hw_clock_S();          break;
        case HWT_NVM_EEPROM_STATUS: rvalue = hwt_eeprom_status;     break;
        case HWT_NVM_EEPROM_SECTION:rvalue = hwt_eeprom_section;    break;
        case HWT_NVM_EEPROM_ADDRESS:rvalue = hwt_eeprom_address;    break;
        case HWT_NVM_EEPROM_READ:
            hwt_eeprom_status = hw_nvm_eeprom_read_uint16((hw_nvm_eeprom_section_t)hwt_eeprom_section,
                                                          hwt_eeprom_address,
                                                          &rvalue);
            break;
        case HWT_NVM_EEPROM_CHECKSUM:
            rvalue = hw_nvm_eeprom_checksum(hwt_eeprom_section);
            break;

        case HWT_NVM_EEPROM_TCMD:     rvalue = hwt_eeprom_tcmd;      break;
        case HWT_NVM_EEPROM_TSTATE:   rvalue = hwt_eeprom_tstate;    break;
        case HWT_NVM_EEPROM_TFAILURES:rvalue = hwt_eeprom_tfailures; break;
    }

    return rvalue;
}


void hwt_fcall_write(uint16_t i, uint16_t data)
{
    if (hwt_access_level >= 2)
    switch (i)
    {
        case HWT_RESET_FORCE:        hw_reset_force(data&0xFF, data>>8);      break;
        case HWT_MCU_POWER_HOLD:     hw_mcu_SetPowerHold(data!=0?true:false); break;
        case HWT_NVM_EEPROM_SECTION: hwt_eeprom_section = data;               break;
        case HWT_NVM_EEPROM_ADDRESS: hwt_eeprom_address = data;               break;
        case HWT_NVM_EEPROM_WRITE:
            hwt_eeprom_status = hw_nvm_eeprom_write_uint16((hw_nvm_eeprom_section_t)hwt_eeprom_section,
                                                            hwt_eeprom_address,
                                                            data );
            break;

        case HWT_NVM_EEPROM_TCMD:      hwt_eeprom_tcmd     = data; break;
        case HWT_NVM_EEPROM_TSTATE:    hwt_eeprom_tstate   = (hwt_eeprom_tstate_t)data; break;
        case HWT_NVM_EEPROM_TFAILURES: hwt_eeprom_tfailures= data; break;
        case HWT_CAN_LOOPBACK:         hwt_txCANMessage(data); break;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void hwt_txCANMessage(uint16_t channel)
{
  hw_can_msg_t msg_data;

  if(channel == 0)
  {
    //response message, destination=tool, source = ECU SA
    msg_data.id.set_J1939ID(6, 0xEF, 0xF9, nvm_ecuid.j1939_source_address );
  }
  else
  {
    //test message on channel 2 to be echoed back with id incremented by 1
    msg_data.id.set_J1939ID(6, 0xEF, nvm_ecuid.j1939_source_address,0xF8 );
  }

  msg_data.DLR = 0x08;
  msg_data.set_byte(0, 0x0A);   //write word
  msg_data.set_byte(1, HWT_CAN_LOOPBACK ); //Set address for CAN
  msg_data.set_byte(2, HWT_FCALL_BASE >> 8  ); //loopback function
  msg_data.set_byte(3, 0x00);   //set CAN channel to 0
  msg_data.set_byte(4, 0x00);   //for response
  msg_data.set_byte(5, 0xFF);
  msg_data.set_byte(6, 0xFF);
  msg_data.set_byte(7, 0xFF);

  if(channel < HWC_CAN_QTY)
  {
    hw_can_txq[channel].send_msg(&msg_data);
  }
}




void ap_hwt_initialize(void)
{
    uint8_t hwt_block_id = hwt_base_address >> 8;
    hwt_block.initialize    (hwt_block_id);
    hwt_block.set_read_word_f (hwt_io_read);
    hwt_block.set_write_word_f(hwt_io_write);
    dv_list.add_block(&hwt_block);

    hwt_fio_block.initialize(hwt_block_id+1);
    hwt_fio_block.set_read_word_f (hwt_fio_read);
    hwt_fio_block.set_write_word_f(hwt_fio_write);
    dv_list.add_block(&hwt_fio_block);

    hwt_fcall_block.initialize(hwt_block_id+2);
    hwt_fcall_block.set_read_word_f (hwt_fcall_read  );
    hwt_fcall_block.set_write_word_f(hwt_fcall_write );
    dv_list.add_block(&hwt_fcall_block);

    hwt_eeprom_section = E0;
    hwt_access_level = (hw_reset_get_ap_smode() == 1) ? 2:1;

    if (hwt_access_level == 2)
        hw_mcu_heartbeatLED.SetFlashRate(2000); // 0.5 Hz rate since in test mode


}


void ap_hwt_update(void)
{

}
