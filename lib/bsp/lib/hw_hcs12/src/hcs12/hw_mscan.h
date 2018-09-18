
// Reference Documents
//
//  Motorola S12MSCANV2/D (MSCAN Block Guide V02.14)

#ifndef hw_mscan_h
#define hw_mscan_h

#include "stdint.h"
#include "stdbool.h"
#include "hw_can_msg.h"
#include "hw_can_cfg.h"

#ifndef HCS12_BSP_EMU
# include "stdtypes.h"
#endif




extern bool ignore_FIN_input;
extern uint missed_FIN_events;

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// MSCAN module class

class hw_mscan_t
{
public:
    struct reg_t
    {
        uint8_t canctl0;   // MSCAN Control 0 Register
        uint8_t canctl1;   // MSCAN Control 1 Register
        uint8_t canbtr0;   // MSCAN Bus Timing Register 0
        uint8_t canbtr1;   // MSCAN Bus Timing Register 1
        uint8_t canrflg;   // MSCAN Receiver Flag Register
                        //   <<WUPIF:CSCIF:RSTAT(2-bits):TSTAT(2-bits):OVRIF:RXF>>
        uint8_t canrier;
        uint8_t cantflg;
        uint8_t cantier;
        uint8_t cantarq;
        uint8_t cantaak;
        uint8_t cantbsel;
        uint8_t canidac;
        uint8_t r1;
        uint8_t r2;
        uint8_t canrxerr;
        uint8_t cantxerr;
        uint8_t canidar0;
        uint8_t canidar1;
        uint8_t canidar2;
        uint8_t canidar3;
        uint8_t canidmr0;
        uint8_t canidmr1;
        uint8_t canidmr2;
        uint8_t canidmr3;
        uint8_t canidar4;
        uint8_t canidar5;
        uint8_t canidar6;
        uint8_t canidar7;
        uint8_t canidmr4;
        uint8_t canidmr5;
        uint8_t canidmr6;
        uint8_t canidmr7;
        hw_can_msg_t canrxfg;
        hw_can_msg_t cantxfg;
    };


    struct cfg_t
    {
        uint8_t  initial_CANBTR0;
        uint8_t  initial_CANBTR1;
        uint8_t  initial_CANRIER;
        uint8_t  initial_CANIDAC;
        uint8_t  initial_CANIDAR[8];
        uint8_t  initial_CANIDMR[8];
    };


    static const cfg_t DEFAULT_CFG;

    void set_cfg(const cfg_t *cfg_)  { cfg = cfg_; }
    void initialize(reg_t * reg_);

    bool TxBufferAvailiable(void) const;

    bool TxBuffersEmpty    (void) const;

    void SendFrame(hw_can_msg_t *msg);

    void transmit_isr (void);
    void receive_isr  (void);
    void error_isr    (void);
    void wakeup_isr   (void);

    void Set_tx_isr_callback( void (*function)(hw_can_msg_t *) )
    {
        tx_isr_callback = function;
    };

    void Set_rx_isr_callback( void (*function)(hw_can_msg_t *) )
    {
        rx_isr_callback = function;
    };
    //void (* error_isr_callback) (void);
    //void (*wakeup_isr_callback) (void);

private:
    reg_t *reg;
    const cfg_t *cfg;

    void (*    tx_isr_callback) (hw_can_msg_t *msg);
    void (*    rx_isr_callback) (hw_can_msg_t *msg);
    void (* error_isr_callback) (void);
    void (*wakeup_isr_callback) (void);

};



#endif
