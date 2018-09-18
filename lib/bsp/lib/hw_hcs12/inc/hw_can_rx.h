/*
    This module processes received CAN messages.
*/

#ifndef hw_can_rx_h
#define hw_can_rx_h

#include "hw_can.h"


class hw_can_rxmsg
{
public:
    void initialize(void);


    hw_can_id rx_id;
    hw_can_id rx_id_mask;
 
    uint8_t D0_data, D0_mask;
    uint8_t D1_data, D1_mask;

    void (*rx_callback)(hw_can_msg_t * msg);
    void (*rx_callback_freePointer)(hw_can_msg_t * msg, void *freePointer);
    void * freePointer;

    hw_can_msg_t mbuff;

    uint16_t msg_age_mS;    // age of the data (in milliseconds)
                            //    -> set to zero when new data arrives
                            //    -> saturates at 60000mS (1 minute)

    hw_can_rxmsg *next;
};


class hw_can_rx_handler_t
{
public:
    void initialize(void);
    void update(void);

    void process_msg(hw_can_msg_t * msg);
    void add_msg   (hw_can_rxmsg *rxmsg);
private:
    hw_can_rxmsg *msg_list;
};




#endif


