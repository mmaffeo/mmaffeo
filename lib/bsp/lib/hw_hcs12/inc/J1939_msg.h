
#ifndef J1939_msg_h
#define J1939_msg_h

#include "hw_io.h"

class J1939_msg_t
{
public:
         
    hw_can_id id;
   
    uint16_t  length;   // number of bytes in this message      
    const uint8_t  *data;  

};




#endif

