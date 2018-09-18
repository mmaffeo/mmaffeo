#include "hw_io.h"

uint16_t dropped_message;

#ifdef HWC_CAN0
    void          hw_can_txq_t::HWC_CAN0_txq_post_tx_calback(hw_can_txmsg *msg)
    {
        HWC_CAN0_txq->post_tx_callback(msg);
    }
    hw_can_txq_t *hw_can_txq_t::HWC_CAN0_txq;
#endif

#ifdef HWC_CAN4
    void          hw_can_txq_t::HWC_CAN4_txq_post_tx_calback(hw_can_txmsg *msg)
    {
        HWC_CAN4_txq->post_tx_callback(msg);
    }
    hw_can_txq_t *hw_can_txq_t::HWC_CAN4_txq;
#endif



void hw_can_txq_t::initialize(uint8_t port)
{

    tx_mbox.initialize();
    tx_mbox.set_send_rate(hw_stimer::OFF_CNT);

#ifdef HWC_CAN0
    if (port == HWC_CAN0 )
    {
        tx_mbox.post_tx_callback = hw_can_txq_t::HWC_CAN0_txq_post_tx_calback;
        HWC_CAN0_txq = this;
    }
#endif

#ifdef HWC_CAN4
    if (port == HWC_CAN4 )
    {
        tx_mbox.post_tx_callback = hw_can_txq_t::HWC_CAN4_txq_post_tx_calback;
        HWC_CAN4_txq = this;
    }
#endif

    head = 0;
    tail = 0;
    size = 0;
    dropped_message = 0;

    hw_can_tx_scheduler[port].add_msg(&tx_mbox);
}



bool hw_can_txq_t::send_msg(const hw_can_msg_t *m)
{
    // need to ensure this function is atomic,
    // this function can be called from multiple places asyncronously.
    EnterCritical();

    if (size == 0 && tx_mbox.timer.off())
    {
        tx_mbox.mbuff = *m;
        tx_mbox.SendNow();
    }
    else
    {
        // add to queue
        if (size < (HW_CAN_TXQ_SIZE-1)  )
        {
            mbuff[head] = *m;
            ++size;
            ++head;
            if (head >= HW_CAN_TXQ_SIZE) head = 0;

            ++q_count;
        }
        else
        {
          dropped_message++;
        }
    }

    ExitCritical();

    return true;
}



void hw_can_txq_t::post_tx_callback(hw_can_txmsg *msg)
{
    // always called from within an ISR, so this function can be assumed to be atomic.
    if (size > 0)
    {
        // copy to mbox and send...
        tx_mbox.mbuff = mbuff[tail];
        --size;
        ++tail;
        if (tail >= HW_CAN_TXQ_SIZE) tail = 0;
        
        tx_mbox.SendNow();
    }
}

