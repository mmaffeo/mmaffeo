#ifndef hw_can_txq_h
#define hw_can_txq_h


#include "hw_can_cfg.h"



#define HW_CAN_TXQ_SIZE 15

extern uint16_t dropped_message;

class hw_can_txq_t
{
public:

    void initialize(uint8_t port);

    bool send_msg(const hw_can_msg_t *m);


private:

    void post_tx_callback(hw_can_txmsg *msg)  ;

    hw_can_msg_t mbuff[HW_CAN_TXQ_SIZE];

    uint8_t head;
    uint8_t tail;
    uint8_t size;
    uint32_t q_count;

    hw_can_txmsg tx_mbox;

#ifdef HWC_CAN0
    static void          HWC_CAN0_txq_post_tx_calback(hw_can_txmsg *msg);
    static hw_can_txq_t *HWC_CAN0_txq;
#endif

#ifdef HWC_CAN4
    static void          HWC_CAN4_txq_post_tx_calback(hw_can_txmsg *msg);
    static hw_can_txq_t *HWC_CAN4_txq;
#endif

};

#endif