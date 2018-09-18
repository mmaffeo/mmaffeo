
#include "hw_can.h"
#include "hw_mcu.h"
#include "hw_mscan.h"
#include <stdlib.h>

#define HWC_CAN0_BASE_ADDRESS  ((hw_mscan_t::reg_t *) 0x0140 )
#define HWC_CAN4_BASE_ADDRESS  ((hw_mscan_t::reg_t *) 0x0280 )


hw_can_tx_scheduler_t hw_can_tx_scheduler[HWC_CAN_QTY];
hw_can_rx_handler_t   hw_can_rx_handler  [HWC_CAN_QTY];
hw_can_txq_t          hw_can_txq         [HWC_CAN_QTY];


static hw_mscan_t hw_mscan [HWC_CAN_QTY];


#ifdef HWC_CAN0


static void CAN0_receive_handler(hw_can_msg_t *msg) { hw_can_rx_handler[HWC_CAN0].process_msg(msg); }
static void CAN0_msg_tx_success (hw_can_msg_t *msg)
{
    hw_can_txmsg *txmsg = hw_can_tx_scheduler[HWC_CAN0].get_next_msg();

    if (txmsg)
    {
        hw_mscan[HWC_CAN0].SendFrame(&txmsg->mbuff);

        if (txmsg->post_tx_callback)
            txmsg->post_tx_callback(txmsg);
    }
}
#endif


#ifdef HWC_CAN4

static void CAN4_receive_handler(hw_can_msg_t *msg) { hw_can_rx_handler[HWC_CAN4].process_msg(msg); }
static void CAN4_msg_tx_success (hw_can_msg_t *msg)
{
    hw_can_txmsg *txmsg = hw_can_tx_scheduler[HWC_CAN4].get_next_msg();

    if (txmsg)
    {
        hw_mscan[HWC_CAN4].SendFrame(&txmsg->mbuff);

        if (txmsg->post_tx_callback)
            txmsg->post_tx_callback(txmsg);
    }

}
#endif


void hw_can_initialize(void)
{
#ifdef HWC_CAN0
    hw_mscan           [HWC_CAN0].initialize( HWC_CAN0_BASE_ADDRESS );
    hw_can_tx_scheduler[HWC_CAN0].initialize(HWC_CAN0);
    hw_can_rx_handler  [HWC_CAN0].initialize();
    hw_can_txq         [HWC_CAN0].initialize(HWC_CAN0);
    hw_mscan           [HWC_CAN0].Set_rx_isr_callback(CAN0_receive_handler);
    hw_mscan           [HWC_CAN0].Set_tx_isr_callback(CAN0_msg_tx_success );
#endif

#ifdef HWC_CAN4
    hw_mscan           [HWC_CAN4].initialize(HWC_CAN4_BASE_ADDRESS );
    hw_can_tx_scheduler[HWC_CAN4].initialize(HWC_CAN4);
    hw_can_rx_handler  [HWC_CAN4].initialize();
    hw_can_txq         [HWC_CAN4].initialize(HWC_CAN4);
    hw_mscan           [HWC_CAN4].Set_rx_isr_callback(CAN4_receive_handler);
    hw_mscan           [HWC_CAN4].Set_tx_isr_callback(CAN4_msg_tx_success );
#endif
}


void hw_can_update(void)
{
    for (uint8_t i=0; i<HWC_CAN_QTY; ++i )
    {
        hw_can_tx_scheduler[i].update();
        hw_can_rx_handler  [i].update();
    }
}

bool hw_can_TxBufferAvailiable(uint8_t port)
{
  return hw_mscan[port].TxBufferAvailiable();
}

void hw_can_SendFrame(uint8_t port, hw_can_msg_t *msg)
{
  hw_mscan[port].SendFrame(msg);
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED

#ifdef HWC_CAN0
__interrupt void CAN0_Tx_Vector (void) { hw_mscan[HWC_CAN0].transmit_isr(); }
__interrupt void CAN0_Rx_Vector (void) { hw_mscan[HWC_CAN0].receive_isr();  }
__interrupt void CAN0_Err_Vector(void) { hw_mscan[HWC_CAN0].error_isr();    }
__interrupt void CAN0_Wup_Vector(void) { hw_mscan[HWC_CAN0].wakeup_isr();   }
#endif

#ifdef HWC_CAN4
__interrupt void CAN4_Tx_Vector (void) { hw_mscan[HWC_CAN4].transmit_isr(); }
__interrupt void CAN4_Rx_Vector (void) { hw_mscan[HWC_CAN4].receive_isr();  }
__interrupt void CAN4_Err_Vector(void) { hw_mscan[HWC_CAN4].error_isr();    }
__interrupt void CAN4_Wup_Vector(void) { hw_mscan[HWC_CAN4].wakeup_isr();   }
#endif

#pragma CODE_SEG DEFAULT





