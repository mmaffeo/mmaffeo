
#ifndef j1939_tp_tx_h
#define j1939_tp_tx_h

#include "J1939_msg.h"
#include "J1939_TP.h"
#include "hw_io.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// J1939 transport protocol ...message originator class


/*  example usage...
    J1939_TP_tx CAN0_TP_tx;   // create a J1939 transport protocol message originator object

    ...
    // Somewhere in the initialization code...
    CAN0_TP_tx.initialize(HWC_CAN0);   // initialize this object to be connected to a particular CAN port

    ...
    // on a periodic basis... (every 10mS)
    CAN0_TP_tx.update();               // call the periodic task execution function for this object


    // to send a message via this protocol...

    J1939_msg_t test_tp_msg;           // create a J1939 message object

    ...
    uint8_t vi_data[] ="This is the VIN number stored in this ECU.*";
    const uint16_t vi_data_length = sizeof(vi_data) / sizeof(uint8_t);

    ...
    test_tp_msg.id.set_J1939ID(6,0xFE, 0xEC, 0xb0 ) ;
    test_tp_msg.length = vi_data_length;
    test_tp_msg.data   = vi_data;

    CAN0_TP_tx.SendMsg(&test_tp_msg);


    ... somewhere else...
    if ( CAN0_TP_tx.Mode()==IDLE_TX_SUCESSFUL)
    {
        // message has been transmitted...
    }


*/


class J1939_TP_tx : J1939_TP
{
public:
  enum mode_t       // MSbit==1 ->a transmit session is currently in progress
  {
    IDLE = 0x00,
    IDLE_TX_SUCESSFUL,
    IDLE_CTS_TIMEOUT,
    IDLE_EndOfMsgACK_TIMEOUT,
    IDLE_REMOTE_ABORT,
    IDLE_LOCAL_ABORT,

    WAITING_FOR_CTS = 0x80,
    WAITING_FOR_EndOfMsgACK,
    TRANSMITTING_DT,
    TRANSMITTING_SF
  };

  void SendMsg(J1939_msg_t *jmsg);     // if jmsg->id is a PDU1 format... RTS/CTS protocol is used
                                       // if jmsg->id is a PDU2 format... BAM protocol is used

  bool Busy(void) const { return mode & 0x80;};
  bool Idle(void) const { return !Busy(); };
  uint8_t Mode(void) const { return mode; };

  void Abort(void);

  void initialize(uint8_t port = 0);

  void update(void);
private:
  J1939_msg_t *jmsg;

  uint8_t mode;
  uint8_t type;       // BAM or RTS/CTS
  uint16_t next_byte;
  uint8_t packets_to_send;

  hw_stimer timeout;

  hw_can_txmsg tx_mbox;
  hw_can_rxmsg rx_mbox;
};



#endif
