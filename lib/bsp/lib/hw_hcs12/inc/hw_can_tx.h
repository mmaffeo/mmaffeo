/*
    This module schedules the transmission of CAN message frames on a particular CAN port.
*/

#ifndef hw_can_tx_h
#define hw_can_tx_h

#include "hw_can.h"
#include "hw_timer.h"



class hw_can_tx_scheduler_t;

class hw_can_txmsg
{
public:
    void initialize(void);

    void (* pre_tx_callback)(hw_can_msg_t * msg)  ;
    void (*post_tx_callback)(hw_can_txmsg * msg)  ;


    void Enable(uint8_t delay=0)  { timer.set(delay);              };
    void Disable(void)            { timer.set(hw_stimer::OFF_CNT); };
    void SendNow(void);
    void SendRightNow(void);

    void set_send_rate(uint8_t r) { timer.set_rate(r);             };

    hw_can_msg_t mbuff;

    hw_stimer    timer;
    hw_can_txmsg *next;
    hw_can_tx_scheduler_t *scheduler;

private:
    bool insertedMsg;
};


class hw_can_tx_scheduler_t
{
public:
    void initialize(uint8_t port_);
    void update    (void);

    void add_msg   (hw_can_txmsg *txmsg);

    hw_can_txmsg * get_next_msg(void);

    uint8_t port;
private:

    hw_can_txmsg * msg_list;
    hw_can_txmsg * last_msg;
};


#endif


