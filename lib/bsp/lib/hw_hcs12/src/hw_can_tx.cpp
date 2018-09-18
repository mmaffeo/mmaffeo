

#include "hw_can.h"
#include "hw_mcu.h"

#include <stddef.h>



void hw_can_txmsg::initialize(void)
{
    next = NULL;

    timer.set_rate(hw_stimer::OFF_CNT);
    pre_tx_callback = NULL;
    post_tx_callback = NULL;

    mbuff.DLR = 8;

    insertedMsg = false;
}


void hw_can_txmsg::SendNow(void)
{
    if (hw_can_TxBufferAvailiable(scheduler->port))
    {
        //scheduler->last_txmsg_sent = this;
        if (pre_tx_callback)
            pre_tx_callback(&mbuff);

        hw_can_SendFrame(scheduler->port, &mbuff);

        if (insertedMsg)
        {
          timer.reset();
          insertedMsg = false;
        }

        if (post_tx_callback)
            post_tx_callback(this);
    }
    else
    {
        Enable();
    }
}


void hw_can_txmsg::SendRightNow(void)
{
    insertedMsg = true;
    if(scheduler != NULL)
    {
      SendNow();
    }
}



void hw_can_tx_scheduler_t::initialize(uint8_t port_)
{
    msg_list = NULL;
    last_msg = NULL;
    port = port_;
}


void hw_can_tx_scheduler_t::update(void)
{
    hw_can_txmsg *tm = msg_list;

    while (tm != NULL)
    {
        tm->timer.update();
        tm = tm->next;
    }

    EnterCritical();
    while (hw_can_TxBufferAvailiable(port))
    {

        tm = get_next_msg( );

        if (tm != NULL)
        {
            hw_can_SendFrame(port, &tm->mbuff);

            if (tm->post_tx_callback)
                tm->post_tx_callback(tm);
        }
        else
        {
          break;
        }
    }
    ExitCritical();
}


hw_can_txmsg * hw_can_tx_scheduler_t::get_next_msg( void )
{
    hw_can_txmsg *tm = NULL;
    hw_can_msg_t *m  = NULL;

    if ( last_msg != NULL )
    {
      tm = last_msg;
      last_msg = NULL;
    }
    else
    {
      tm = msg_list;
    }

    while (tm != NULL && m == NULL)
    {
        if (tm->timer.expired())
        {
            tm->timer.reset();

            m = &tm->mbuff;

            if (tm->pre_tx_callback != NULL)
            {
                for (uint8_t j=0; j<=7 ; ++j)
                    m->DSR[j] = 0xFF;

                tm->pre_tx_callback(m);
            }
            last_msg = tm;
            break;
        }
        tm = tm->next;
    }

    return tm;
}


void hw_can_tx_scheduler_t::add_msg(hw_can_txmsg *txmsg)
{
    if (msg_list == NULL)
    {
        msg_list = txmsg;
    }
    else
    {
         hw_can_txmsg *tm = msg_list;

         while (tm->next != NULL)
            tm = tm->next;

         EnterCritical();
         tm->next = txmsg;
         ExitCritical();
    }

    txmsg->scheduler = this;
}



