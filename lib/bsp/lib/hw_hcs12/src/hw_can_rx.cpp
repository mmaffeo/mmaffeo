
#include "hw_can.h"
#include <string.h>
#include "hw_mcu.h"



void hw_can_rxmsg::initialize(void)
{
    next = NULL;

    D0_mask= 0x00;
    D1_mask = 0x00;
}


void hw_can_rx_handler_t::initialize(void)
{
    msg_list = NULL;
}

void hw_can_rx_handler_t::update(void)
{
    hw_can_rxmsg *tm = msg_list;

    while (tm != NULL)
    {
        if ( tm->msg_age_mS < 60000 )  tm->msg_age_mS += 10;
        else               tm->msg_age_mS  = 60000;

        tm = tm->next;
    }
}


void hw_can_rx_handler_t::process_msg(hw_can_msg_t * msg)
{
    hw_can_rxmsg *tm = msg_list;

    while (tm != NULL)
    {
        #define IDR0_MATCH (((msg->id.IDR[0]^tm->rx_id.IDR[0])&tm->rx_id_mask.IDR[0])==0)
        #define IDR1_MATCH ((((msg->id.IDR[1]^tm->rx_id.IDR[1])&tm->rx_id_mask.IDR[1])&0xEF)==0)
        #define IDR2_MATCH (((msg->id.IDR[2]^tm->rx_id.IDR[2])&tm->rx_id_mask.IDR[2])==0)
        #define IDR3_MATCH (((msg->id.IDR[3]^tm->rx_id.IDR[3])&tm->rx_id_mask.IDR[3])==0)
        #define IDR_MATCH  (IDR0_MATCH && IDR1_MATCH && IDR2_MATCH && IDR3_MATCH )

        #define D0_MATCH   (((msg->   DSR[0]^tm->D0_data     )&tm->D0_mask          )==0)
        #define D1_MATCH   (((msg->   DSR[1]^tm->D1_data     )&tm->D1_mask          )==0)

        if ( IDR_MATCH && D0_MATCH && D1_MATCH )
        {
            // copy message data to mbuff
            memcpy(&tm->mbuff, msg, sizeof(hw_can_msg_t)) ;

            tm->msg_age_mS=0;

            // call the rx_callback function
            if (tm->rx_callback != NULL)
            {
                tm->rx_callback(msg);
            }
            else if (tm->rx_callback_freePointer != NULL)
            {
                tm->rx_callback_freePointer(msg, tm->freePointer);
            }
        }

        tm = tm->next;
    }
}


void hw_can_rx_handler_t::add_msg(hw_can_rxmsg *rxmsg)
{
    if (msg_list == NULL)
    {
        msg_list = rxmsg;
    }
    else
    {
        hw_can_rxmsg *tm = msg_list;

        while (tm->next != NULL)
            tm = tm->next;

        EnterCritical();
        tm->next = rxmsg;
        ExitCritical();
    }
}

