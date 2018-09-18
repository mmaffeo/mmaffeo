#include "CANOpen_tx.h"


void CANOpen_tx::initialize(uint8_t port)
{
  tx_mbox.initialize();
  tx_mbox.set_send_rate(hw_stimer::OFF_CNT);
  hw_can_tx_scheduler[port].add_msg(&tx_mbox);

  // set up the rx_mbox to receive the CM message
  rx_mbox.rx_id.set_CANOpenID(0, 0xEC, 0xFF, 0xFE);   // initially only receive from the NULL address
  rx_mbox.rx_id_mask.set_CANOpenID(0, 0xFF, 0xFF, 0xFF);
  rx_mbox.msg_age_mS = 60000;
  rx_mbox.initialize();
  hw_can_rx_handler[port].add_msg(&rx_mbox);

  mode = IDLE;
}


void CANOpen_tx::update(void)
{
  // process any new "CM" messages which may have arrived...
  if (rx_mbox.msg_age_mS < 60000)
  {
    switch (rx_mbox.mbuff.get_byte(0))
    {
    case CM_CTS:
      {
        uint8_t next_packet = rx_mbox.mbuff.get_byte(2);
        packets_to_send = rx_mbox.mbuff.get_byte(1);

        if (next_packet >= 1) next_packet -= 1;

        next_byte = next_packet * 7;

        mode = TRANSMITTING_DT;
      }
      break;
    case CM_EndOfMsgACK:
      if (mode == WAITING_FOR_EndOfMsgACK)
      {
        mode = IDLE_TX_SUCESSFUL;

      }

      rx_mbox.rx_id.set_CANOpen_SA(0xFE);


      break;
    case CM_Conn_Abort:
      mode = IDLE_REMOTE_ABORT;
      rx_mbox.rx_id.set_CANOpen_SA(0xFE);

      break;
    }

    rx_mbox.msg_age_mS = 60000;  // set this message to "old"
  }

  timeout.update();

  switch (mode)
  {
  case IDLE:
  default:
    break;
  case WAITING_FOR_CTS:
    if (timeout.expired()) mode = IDLE_CTS_TIMEOUT;

    break;
  case WAITING_FOR_EndOfMsgACK:
    if (timeout.expired()) mode = IDLE_EndOfMsgACK_TIMEOUT;
    break;
  case TRANSMITTING_DT:
    // send next DT message.
    if (tx_mbox.timer.off())
    {
      if (packets_to_send > 0)
      {
        --packets_to_send;

        //send the next DT_frame
        tx_mbox.mbuff.id.set_CANOpenID(7, 0xEB, jmsg->id.get_CANOpen_DA(), jmsg->id.get_CANOpen_SA());
        tx_mbox.mbuff.DLR = 8;

        tx_mbox.mbuff.set_byte(0, next_byte / 7 + 1); // set sequence number
        for (uint8_t i = 1; i < 8; ++i)
        {
          if (next_byte < jmsg->length) tx_mbox.mbuff.set_byte(i, jmsg->data[next_byte]);
          else tx_mbox.mbuff.set_byte(i, 0xFF);

          ++next_byte;
        }

        if (type == CM_BAM) tx_mbox.timer.set(2);  // send in 50mS
        else tx_mbox.SendNow();     // send ASAP

        if (next_byte >= jmsg->length) mode = (type == CM_BAM) ? IDLE_TX_SUCESSFUL : WAITING_FOR_EndOfMsgACK;
      } else
      {
        mode = WAITING_FOR_CTS;
      }

      if (mode == WAITING_FOR_CTS || mode == WAITING_FOR_EndOfMsgACK) timeout.set(130);
    }
    break;
  case TRANSMITTING_SF:   // transmitting a message <= 8 bytes (Single Frame)
    if (tx_mbox.timer.off())  // message has been sent
      mode = IDLE_TX_SUCESSFUL;

    break;
  }
}


void CANOpen_tx::SendMsg(CANOpen_msg_t *jmsg)
{
  if (Idle())
  {
    this->jmsg = jmsg;

    hw_can_msg_t *mptr = &tx_mbox.mbuff;

    mptr->DLR = 8;

    if (jmsg->length <= 8)
    {
      mode = TRANSMITTING_SF;

      // send as a single message frame
      mptr->id = jmsg->id;
      for (uint8_t i = 0; i <= 7; ++i) mptr->DSR[i] = jmsg->data[i];
    } else
    {   // send a CM message to initiate this tranmsmit protocol session...
      uint8_t sa = jmsg->id.get_CANOpen_SA();
      rx_mbox.rx_id.set_CANOpen_DA(sa);        // only receive CM dessages directed at this source address

      uint8_t da = jmsg->id.get_CANOpen_DA();
      rx_mbox.rx_id.set_CANOpen_SA(da);   // and from the SA the message is being sent to...

      uint16_t size = jmsg->length;
      uint8_t packets = size / 7 + (size % 7 ? 1 : 0);

      if (da == 0xFF)
      {
        type = CM_BAM;
        mode = TRANSMITTING_DT;
        next_byte = 0;
        packets_to_send = packets;
      } else
      {
        type = CM_RTS;
        mode = WAITING_FOR_CTS;
        timeout.set(130);
        packets_to_send = 0;
      }

      mptr->id.set_CANOpenID(7, 0xEC, da, sa);

      mptr->set_byte(0, type);
      mptr->set_byte(1, size & 0xFF);
      mptr->set_byte(2, size >> 8);
      mptr->set_byte(3, packets);
      mptr->set_byte(4, 0xFF);     // no limit on the number of response packets at a time.

      uint16_t pgn = jmsg->id.get_CANOpen_PGN();
      mptr->set_byte(5, pgn & 0xFF);
      mptr->set_byte(6, pgn >> 8);
      mptr->set_byte(7, 0x00);
    }
    tx_mbox.SendNow();  // initiate transmission (ASAP)
  }
}


void CANOpen_tx::Abort(void)
{
  if (Busy())
  {
    mode = IDLE_LOCAL_ABORT;
    // ??? still need to figure out when a "CM_Conn_Abort" message should sent out and to whom
  }

}


