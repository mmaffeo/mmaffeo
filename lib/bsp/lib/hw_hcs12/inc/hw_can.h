
#ifndef hw_can_h
#define hw_can_h

#include "stdbool.h"

#include "hw_can_msg.h"
#include "hw_can_tx.h"
#include "hw_can_txq.h"
#include "hw_can_rx.h"
#include "hw_can_cfg.h"


extern hw_can_tx_scheduler_t hw_can_tx_scheduler[HWC_CAN_QTY];
extern hw_can_rx_handler_t   hw_can_rx_handler  [HWC_CAN_QTY];
extern hw_can_txq_t          hw_can_txq         [HWC_CAN_QTY];

void hw_can_initialize(void);
void hw_can_update(void);
void hw_can_update_fast(void);

bool hw_can_TxBufferAvailiable(uint8_t port);
void hw_can_SendFrame(uint8_t port, hw_can_msg_t *msg);


#ifndef HCS12_BSP_EMU

#pragma CODE_SEG __NEAR_SEG NON_BANKED

#ifdef HWC_CAN0
__interrupt void CAN0_Tx_Vector (void);
__interrupt void CAN0_Rx_Vector (void);
__interrupt void CAN0_Err_Vector(void);
__interrupt void CAN0_Wup_Vector(void);
#endif

#ifdef HWC_CAN4
__interrupt void CAN4_Tx_Vector (void);
__interrupt void CAN4_Rx_Vector (void);
__interrupt void CAN4_Err_Vector(void);
__interrupt void CAN4_Wup_Vector(void);
#endif
#pragma CODE_SEG DEFAULT

#endif /* HCS12_BSP_EMU */



#endif
