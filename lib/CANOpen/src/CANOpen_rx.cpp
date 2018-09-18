/***************************************************************
* Project Name: E10 Electric
*
* Copyright 2005 Bobcat Company as an unpublished work.
* All Rights Reserved.
*
* The information contained herein is confidential
* property of Bobcat Company. The use, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Bobcat Company.
*
* First written on 06 August, 2018 
*
* Module Description:
***************************************************************/
#include "CANOpen_rx.h"
//#include <stddef.h>

PDO1::PDO1()
{
    CANOpenID.set_stdID( 0x0188);
    //CANOpenID.D0_data = 0x00;
}  

void PDO1::initialize(void)
{
  
}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//// CANOpen Transport Protocol "receive handler"...
//
////******************************************************************************
///**
// * Static CM message callback to be used by all CANOpen_rx objects. Maps a
// * hw_can_rx callback to an object specific method.
// *
// * \param msg           CM message
// * \param freePointer   this pointer points to a specific CANOpen_rx object
// *
// * \return void
// ******************************************************************************/
//void CANOpen_rx::HWC_CM_rx_callback(hw_can_msg_t *msg, void * freePointer)
//{
//  CANOpen_rx *tp = (CANOpen_rx *)freePointer;
//
//  if (tp != NULL)
//  {
//    tp->CM_rx_callback(msg);
//  }
//}
//
////******************************************************************************
///**
// * Static DT message callback to be used by all CANOpen_rx objects. Maps a
// * hw_can_rx callback to an object specific method.
// *
// * \param msg           CM message
// * \param freePointer   this pointer points to a specific CANOpen_rx object
// *
// * \return void
// ******************************************************************************/
//void CANOpen_rx::HWC_DT_rx_callback(hw_can_msg_t *msg, void * freePointer)
//{
//  CANOpen_rx *tp = (CANOpen_rx *)freePointer;
//
//  if (tp != NULL)
//  {
//    tp->DT_rx_callback(msg);
//  }
//}
//
//void CANOpen_rx::initialize(uint8_t node_id_, uint8_t port)
//{
//  initialize_sa(node_id_, port, 0, 0);
//}
//
//void CANOpen_rx::initialize_sa(uint8_t node_id_, uint8_t port, uint8_t sa, uint8_t saMask)
//{
//  CM_rx.rx_callback_freePointer = HWC_CM_rx_callback;
//  CM_rx.freePointer = (void *)this;
//  DT_rx.rx_callback_freePointer = HWC_DT_rx_callback;
//  DT_rx.freePointer = (void *)this;
//
//  jmsg.data = data;
//  CANOpen_da = node_id_;
//  CANOpen_sa = sa;
//  CANOpen_saMask = saMask;
//
//  CM_tx.initialize();
//  CM_tx.set_send_rate(hw_stimer::OFF_CNT);
//  hw_can_tx_scheduler[port].add_msg(&CM_tx);
//
//  CM_rx.rx_id.set_CANOpenID(0, 0xEC, CANOpen_da, CANOpen_sa);
//  CM_rx.rx_id_mask.set_CANOpenID(0, 0xFF, 0xFF, CANOpen_saMask);
//  CM_rx.msg_age_mS = 60000;
//  CM_rx.initialize();
//  hw_can_rx_handler[port].add_msg(&CM_rx);
//
//  DT_rx.rx_id.set_CANOpenID(0, 0xEB, CANOpen_da, CANOpen_sa);
//  DT_rx.rx_id_mask.set_CANOpenID(0, 0xFF, 0xFF, CANOpen_saMask);
//  DT_rx.msg_age_mS = 60000;
//  DT_rx.initialize();
//  hw_can_rx_handler[port].add_msg(&DT_rx);
//}
//
//
//void CANOpen_rx::update(void)
//{
//  if (rx_mode == RECEIVING_CM_MSG || rx_mode == RECEIVING_BAM_MSG)
//  {
//    if (timeout_count < 2000)
//    {
//      ++timeout_count;
//    } else
//    {
//      // timeout...
//      FreeBuffer(IDLE_DUE_TO_TIMEOUT);
//    }
//  }
//}
//
//
//void CANOpen_rx::CM_rx_callback(hw_can_msg_t *msg)
//{
//  timeout_count = 0;
//
//  uint8_t control = msg->get_byte(0);
//
//
//  switch (control)
//  {
//  case CM_RTS:  // request to send...
//  case CM_BAM:
//    {
//      uint16_t size = 256u * msg->get_byte(2) + msg->get_byte(1);
//
//      //if ( rx_mode==IDLE && size < RX_BUFFER_SIZE  /* && PGN is of interest ??? */ )
//      if (!(rx_mode & 0x80) && (size < RX_BUFFER_SIZE)/* && PGN is of interest ??? */)
//      {
//        // start a receive session
//        jmsg.length = size;
//
//        uint8_t pf = msg->get_byte(6);
//        uint8_t ps = msg->get_byte(5);
//        if (pf < 240 && ps == 0) ps = msg->id.get_CANOpen_DA();
//        jmsg.id.set_CANOpenID(0,
//                            pf,
//                            ps,
//                            msg->id.get_CANOpen_SA());
//
//        // set RX masks to only accept messages from the source which initiated this connection.
//        uint8_t sa = msg->id.get_CANOpen_SA();
//        CM_rx.rx_id.set_CANOpen_SA(sa);
//        CM_rx.rx_id_mask.set_CANOpen_SA(0xFF);
//        DT_rx.rx_id.set_CANOpen_SA(sa);
//        DT_rx.rx_id_mask.set_CANOpen_SA(0xFF);
//
//        if (control == CM_RTS)
//        {
//          rx_mode = RECEIVING_CM_MSG;
//
//          // reply with a CTS (clear to send) message
//          send_CM_CTS(msg->id.get_CANOpen_SA(),
//                      msg->get_byte(3),  // send all packets
//                      1,           // starting with packet #1
//                      jmsg.id.get_CANOpen_PGN());
//        } else
//        {
//          rx_mode = RECEIVING_BAM_MSG;
//        }
//      } else if (control == CM_RTS)
//      {   // reply with a "CM_Conn_Abort"
//        send_CM_ConnAbort(msg->id.get_CANOpen_SA(),
//                          rx_mode != IDLE ? 1 : 2,
//                          jmsg.id.get_CANOpen_PGN());
//      }
//    }
//    break;
//  case CM_Conn_Abort:
//    rx_mode = IDLE_DUE_TO_ABORT;
//
//    break;
//  default:
//  case CM_CTS:
//  case CM_EndOfMsgACK:   // should not come from transmitter...
//    break;
//  }
//}
//
//
//void CANOpen_rx::DT_rx_callback(hw_can_msg_t *msg)
//{
//
//  timeout_count = 0;
//
//  if (rx_mode == RECEIVING_CM_MSG ||
//      rx_mode == RECEIVING_BAM_MSG)
//  {
//    // copy data from this packet into the message buffer
//    uint8_t i = 1;
//    uint8_t packet = msg->get_byte(0);
//    uint16_t next_byte = 7u * (packet - 1);
//    while (next_byte <= (jmsg.length - 1) && i <= 7)
//    {
//      data[next_byte] = msg->get_byte(i);
//      ++next_byte; ++i;
//    }
//
//    if (next_byte >= jmsg.length)
//    {
//      if (rx_mode == RECEIVING_CM_MSG)
//      {
//        send_CM_EndOfMsgACK(CM_rx.mbuff.id.get_CANOpen_SA(),
//                            jmsg.length,
//                            packet,
//                            jmsg.id.get_CANOpen_PGN());
//      }
//      rx_mode = NEW_MSG_AVAILAIBLE;
//    }
//  }
//}
//
//
//void CANOpen_rx::FreeBuffer(uint8_t mode)
//{
//  // Reapply sa and saMask
//  CM_rx.rx_id.set_CANOpenID(0, 0xEC, CANOpen_da, CANOpen_sa);
//  CM_rx.rx_id_mask.set_CANOpenID(0, 0xFF, 0xFF, CANOpen_saMask);
//  DT_rx.rx_id.set_CANOpenID(0, 0xEB, CANOpen_da, CANOpen_sa);
//  DT_rx.rx_id_mask.set_CANOpenID(0, 0xFF, 0xFF, CANOpen_saMask);
//
//  rx_mode = mode;
//}
//
//
//void CANOpen_rx::send_CM_CTS(uint8_t da,
//                              uint8_t num_of_packets,
//                              uint8_t starting_packet,
//                              uint32_t pgn)
//{
//  hw_can_msg_t *mb = &CM_tx.mbuff;
//
//  mb->id.set_CANOpenID(7, 0xEC, da, CANOpen_da);
//  mb->set_byte(0, CM_CTS);
//  mb->set_byte(1, num_of_packets);  // number of packets to reply with
//  mb->set_byte(2, starting_packet);  // starting packet number
//  mb->set_byte(3, 0xFF);
//  mb->set_byte(4, 0xFF);
//  mb->set_byte(5, pgn & 0xFF);
//  mb->set_byte(6, (uint8_t)(pgn >> 8));
//  mb->set_byte(7, 0x00);
//
//  CM_tx.SendNow();
//}
//
//
//void CANOpen_rx::send_CM_EndOfMsgACK(uint8_t da,
//                                      uint16_t msg_size,
//                                      uint8_t packets,
//                                      uint32_t pgn)
//{
//  hw_can_msg_t *mb = &CM_tx.mbuff;
//
//  mb->id.set_CANOpenID(7, 0xEC, da, CANOpen_da);
//  mb->set_byte(0, CM_EndOfMsgACK);
//  mb->set_byte(1, msg_size & 0xFF);  // number of packets to reply with
//  mb->set_byte(2, msg_size >> 8);  // starting packet number
//  mb->set_byte(3, packets);
//  mb->set_byte(4, 0xFF);
//  mb->set_byte(5, pgn & 0xFF);
//  mb->set_byte(6, (uint8_t)(pgn >> 8));
//  mb->set_byte(7, 0x00);
//
//  CM_tx.SendNow();
//}
//
//
//void CANOpen_rx::send_CM_ConnAbort(uint8_t da, uint8_t reason, uint32_t pgn)
//{
//  hw_can_msg_t *mb = &CM_tx.mbuff;
//
//  mb->id.set_CANOpenID(7, 0xEC, da, CANOpen_da);
//  mb->set_byte(0, CM_Conn_Abort);
//  mb->set_byte(1, reason);  // number of packets to reply with
//  mb->set_byte(2, 0xFF);  // starting packet number
//  mb->set_byte(3, 0xFF);
//  mb->set_byte(4, 0xFF);
//  mb->set_byte(5, pgn & 0xFF);
//  mb->set_byte(6, (uint8_t)(pgn >> 8));
//  mb->set_byte(7, 0x00);
//
//  CM_tx.SendNow();
//}

