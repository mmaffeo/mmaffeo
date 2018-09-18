


#ifndef j1939_tp_h
#define j1939_tp_h

#include "J1939_msg.h"
#include "hw_io.h"


class J1939_TP
{
public:
  enum // connection managment control bytes
  {
    CM_RTS = 16,
    CM_CTS = 17,
    CM_EndOfMsgACK = 19,
    CM_BAM = 32,
    CM_Conn_Abort = 255
  };
};




#endif
