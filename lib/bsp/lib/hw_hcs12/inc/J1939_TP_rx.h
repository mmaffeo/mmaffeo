#ifndef j1939_tp_rx_h
#define j1939_tp_rx_h

#include "J1939_TP.h"
#include "J1939_msg.h"
#include "hw_io.h"


#ifndef RX_BUFFER_SIZE
#define RX_BUFFER_SIZE 216
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// receive

class J1939_TP_rx : J1939_TP
{
public:
  enum mode_t
  {
    IDLE = 0,
    IDLE_DUE_TO_TIMEOUT,
    IDLE_DUE_TO_ABORT,
    RECEIVING_CM_MSG = 0x80, RECEIVING_BAM_MSG, NEW_MSG_AVAILAIBLE
  };

  bool MsgAvailiable(void) const { return rx_mode == NEW_MSG_AVAILAIBLE; }
  mode_t Mode(void) const { return (enum mode_t)rx_mode; }

  void FreeBuffer(uint8_t mode = IDLE);

  J1939_msg_t jmsg;


  void initialize(uint8_t node_id, uint8_t port = HWC_CAN0);
  void initialize_sa(uint8_t node_id, uint8_t port, uint8_t sa, uint8_t saMask);
  void update(void);
private:

  void send_CM_CTS(uint8_t da,
                   uint8_t num_of_packets,
                   uint8_t starting_packet,
                   uint32_t pgn);

  void send_CM_EndOfMsgACK(uint8_t da,
                           uint16_t msg_size,
                           uint8_t packets,
                           uint32_t pgn);

  void send_CM_ConnAbort(uint8_t da, uint8_t reason, uint32_t pgn);


  uint8_t j1939_sa;
  uint8_t j1939_saMask;
  uint8_t j1939_da;
  uint8_t rx_mode;

  uint16_t timeout_count;

  uint8_t data[RX_BUFFER_SIZE];

  hw_can_rxmsg CM_rx;       // PGN 60416
  hw_can_rxmsg DT_rx;       // PGN 60160

  void CM_rx_callback(hw_can_msg_t *msg);
  void DT_rx_callback(hw_can_msg_t *msg);

  hw_can_txmsg CM_tx;       // PGN 60416


  static void HWC_CM_rx_callback(hw_can_msg_t *msg, void * freePointer);
  static void HWC_DT_rx_callback(hw_can_msg_t *msg, void * freePointer);
};



#endif
