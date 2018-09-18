

#include "hw_mscan.h"
#include "hw_mcu.h"    // MCU register definitions

bool ignore_FIN_input = FALSE;
uint missed_FIN_events = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////


const uint8_t msg_size=sizeof(hw_can_msg_t) ;

const hw_mscan_t::cfg_t hw_mscan_t::DEFAULT_CFG=
{
    0x00, // initial_CANBTR0: << SJW(2-bits): BRP(6-bits) >>
                             //    SJW=0   ;
                             //    BRP=0   ;

    0x1C, // initial_CANBTR1: << SAMP:TSEG2(3-bits):TSEG1(4-bits)
                             //    SAMP=0  ;one smaple per bit
                             //    TSEG2=1 ;
                             //    TSEG1=12;
    0x01, // initial_CANRIER: << WUPIE:CSCIE:RSTATE(2-bits):TSTATE(2-bits):OCRIE:RXFIE >>

    0x00, // initial_CANIDAC

    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // initial_CANIDAR[0] -> [7]
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}  // initial_CANIDMR[0] -> [7]

};


static void null_callback(hw_can_msg_t *msg)
{

}




void hw_mscan_t::initialize(reg_t * reg_)
{
    reg = reg_;

    if (!cfg)
        cfg = &DEFAULT_CFG;

    tx_isr_callback = null_callback;
    rx_isr_callback = null_callback;

    reg->canctl0 = 0x01;  // Initilaization mode request.
    reg->canctl1 = 0x80;  // CANCTL1: << CANE:CLKSRC:LOOPB:LISTEN:0:WUPM:SLPAK:INITAK >>
                          //  CANE=1    ;enable this MSCAN module.
                          //  CLKSRC=0  ;

    reg->canbtr0 = cfg->initial_CANBTR0;

    reg->canbtr1 = cfg->initial_CANBTR1;

    // set up the hardware filter...
    reg->canidac = cfg->initial_CANIDAC;

    reg->canidar0 = cfg->initial_CANIDAR[0];
    reg->canidar1 = cfg->initial_CANIDAR[1];
    reg->canidar2 = cfg->initial_CANIDAR[2];
    reg->canidar3 = cfg->initial_CANIDAR[3];
    reg->canidar4 = cfg->initial_CANIDAR[4];
    reg->canidar5 = cfg->initial_CANIDAR[5];
    reg->canidar6 = cfg->initial_CANIDAR[6];
    reg->canidar7 = cfg->initial_CANIDAR[7];

    reg->canidmr0 = cfg->initial_CANIDMR[0];
    reg->canidmr1 = cfg->initial_CANIDMR[1];
    reg->canidmr2 = cfg->initial_CANIDMR[2];
    reg->canidmr3 = cfg->initial_CANIDMR[3];
    reg->canidmr4 = cfg->initial_CANIDMR[4];
    reg->canidmr5 = cfg->initial_CANIDMR[5];
    reg->canidmr6 = cfg->initial_CANIDMR[6];
    reg->canidmr7 = cfg->initial_CANIDMR[7];

    reg->canctl0 &= 0xFE;  // clear the INITRQ bit

    while( reg->canctl1 & 0x01 )
        ; //wait until the INITAK bit is cleared, indicating the MSCAN has been initialized.

    reg->canrflg |= 0xFE;                      // Reset error flags
    reg->canrier  = cfg->initial_CANRIER;      // Enable interrupts
}

// only using TX buffer #0 for now...
bool hw_mscan_t::TxBufferAvailiable(void)  const
{
    return reg->cantflg & 0x01;//0x07;
}

bool hw_mscan_t::TxBuffersEmpty(void) const
{
    uint8_t val = reg->cantflg & 0x07;

    return val == 0x07;
}

void hw_mscan_t::SendFrame(hw_can_msg_t *msg)
{
    uint8_t buff_mask = 1;//reg->CANTFLG;

    reg->cantbsel = buff_mask;  // select next availiable transmit buffer.
                                //   (see MSCAN Block Guide V02.14 Section 3.3.1.11)

    // write data
    reg->cantxfg.id = msg->id;

    for (uint8_t i=0; i<=7 ; ++i)
        reg->cantxfg.DSR[i] = msg->DSR[i];


    reg->cantxfg.DLR = msg->DLR;
    reg->cantxfg.TBPR = msg->TBPR;

    reg->cantflg  = buff_mask;   // initiate the transmission.
    reg->cantier |= buff_mask;   // set TXEIE0
}


void hw_mscan_t::transmit_isr (void)
{
    reg->cantier &= ~0x01;       // clear TXEIE0
    tx_isr_callback(&reg->cantxfg) ;
}

void hw_mscan_t::receive_isr  (void)
{
    rx_isr_callback(&reg->canrxfg);

    // Check if there is a timer interrupt pending
    if (TFLG1 & 0x01)
    {
      // Set a flag so this particular capture can be ignored
      ignore_FIN_input = TRUE;

      // Keep track of how many times this happens
      missed_FIN_events++;
    }

    reg->canrflg |= 0x01;   // reset RXF flag by writing a one
}

void hw_mscan_t::error_isr    (void)
{

}

void hw_mscan_t::wakeup_isr   (void)
{

}