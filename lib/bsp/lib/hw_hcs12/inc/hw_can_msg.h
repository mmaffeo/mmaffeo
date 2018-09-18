
// Reference Documents
//
//  Motorola S12MSCANV2/D (MSCAN Block Guide V02.14)

#ifndef hw_can_msg_h
#define hw_can_msg_h

#include "stdint.h"
#include "stdbool.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// Message object class

// Identifier Registers
//
// Extended ID (29-bit) mapping...
//                 Bit0   Bit1    Bit2    Bit3      Bit4      Bit5    Bit6    Bit7
//     IDR[0]:  << ID28 : ID27  : ID26  : ID25    : ID24    : ID23  : ID22  : ID21  >>
//     IDR[1]:  << ID20 : ID19  : ID18  : SRR(=1) : IDE(=1) : ID17  : ID16  : ID15  >>
//     IDR[2]:  << ID14 : ID13  : ID12  : ID11    : ID10    : ID9   : ID8   : ID7   >>
//     IDR[3]:  << ID6  : ID5   : ID4   : ID3     : ID2     : ID1   : ID0   : RTR   >>
//
// Standard ID (11-bit) mapping...
//     IDR[0]:  << ID10 : ID9   : ID8   : ID7     : ID6     : ID5   : ID4   : ID3   >>
//     IDR[1]:  <<  ID2 : ID1   : ID0   : RTR     : IDE(=0) : ---   : ---   : ---   >>
//     IDR[2]:  << ---- : ---   : ---   : ---     : ------- : ---   : ---   : ---   >>
//     IDR[3]:  << ---- : ---   : ---   : ---     : ------- : ---   : ---   : ---   >>

class hw_can_id
{
public:
  uint32_t idr(void) const
  {
    uint32_t retVal;

    retVal = IDR[0];
    retVal <<= 8;
    retVal |= IDR[1];
    retVal <<= 8;
    retVal |= IDR[2];
    retVal <<= 8;
    retVal |= IDR[3];

    return retVal;
  }

  void set_idr(uint32_t value)
  {
    IDR[3] = (uint8_t)value;
    value >>= 8;
    IDR[2] = (uint8_t)value;
    value >>= 8;
    IDR[1] = (uint8_t)value;
    value >>= 8;
    IDR[0] = (uint8_t)value;
  }

  void set_extID  (uint32_t id)
  {
    uint32_t tempIDR = ((id << 3) & 0xFFE00000u) |  // set id28..id18
                       0x00080000u               |  // set IDE bit to 1
                       ((id << 1) & 0x0007FFFFu) ;  // set id17..id0
    set_idr(tempIDR);
  }

  void set_stdID  (uint16_t id)
  {
    uint32_t tempIDR = (uint32_t)id << 21;
    set_idr(tempIDR);
  }

  void set_J1939ID(uint8_t priority, uint8_t PF, uint8_t PS, uint8_t SA)
  {
    IDR[0] = priority << 5  |   // priority_2:priority_1:priority_0:R=0:DP=0:PF7:PF6:PF5
             PF >> 5;

    IDR[1] = (PF & 0x1C)<<3 |   // PF4:PF3:PF2:SRR=1:IDE=1:PF1:PF0:PS7
             0x18       |
             (PF & 0x03)<<1 |
             (PS & 0x80)>>7   ;

    IDR[2] = PS<<1    |       // PS6:PS5:PS4:PS3:PS2:PS1:PS0:SA7
             (SA & 0x80)>>7 ;

    IDR[3] = SA<<1;             // SA6:SA5:SA4:SA3:SA2:SA1:SA0:RTR=0
  }

  void    set_J1939_SA(uint8_t SA)
  {
    IDR[2] = (IDR[2]&0xFE) | (SA>>7);
    IDR[3] = SA << 1;
  }

  uint8_t get_J1939_SA(void) const
  {
    uint16_t t = IDR[2];
    t <<= 8;
    t |= IDR[3];
    t >>= 1;

    return t & 0xFF;
  }

  void set_J1939_PF(uint8_t PF)
  {
    IDR[0] = (IDR[0]&0xF8) | (PF>>5);
    IDR[1] = (IDR[1]&0xFE) |
              0x18         |
             ((PF<<3)&0xE0)|
             ((PF<<1)&0x06) ;
  }

  uint8_t get_J1939_PF(void) const
  {
    uint8_t b765 = (IDR[0] & 0x07) << 5;
    uint8_t b432 = (IDR[1] & 0xE0) >> 3;
    uint8_t b10  = (IDR[1] & 0x06) >> 1;
    return b765 | b432 | b10;
  }

  void set_J1939_PS(uint8_t DA)
  {
    IDR[1] = (IDR[1]&0xFE) | (DA>>7);
    IDR[2] = (IDR[2]&0x01) | (DA<<1) ;
  }

  uint8_t get_J1939_PS(void) const
  {
    uint16_t t = IDR[1];
    t <<= 8;
    t |= IDR[2];
    t >>= 1;

    return t & 0xFF;
  }

  void set_J1939_DA(uint8_t ps)
  {
    set_J1939_PS(ps);
  }

  uint8_t get_J1939_DA(void) const
  {
    uint8_t pf = get_J1939_PF();
    uint8_t da = pf < 240 ? get_J1939_PS() : 0xFF;
    return da;
  }

  uint16_t get_J1939_PGN(void) const
  {
    uint8_t pf = get_J1939_PF();
    uint8_t ps = (pf >= 240)? get_J1939_PS():0x00;

    return (256u * pf) + ps;
  }

  bool Extended_ID(void) const
  {
    return IDR[1] & 0x08 ? true:false;
  }

  bool DataFrame(void)
  {
    uint8_t rvalue;

    if ( IDR[1] & 0x08 )
        rvalue = (IDR[3] & 0x01) ? false:true;
    else
        rvalue = (IDR[1] & 0x10) ? false:true;

    return rvalue;
  }

  uint32_t Get_ID(void) const
  {
    uint32_t rvalue = idr();

    if ( IDR[1] & 0x08 )
        rvalue  = ((rvalue >> 1) & 0x0003FFFF) |
                  ((rvalue >> 3) & 0xFFFC0000) ;
    else
        rvalue = rvalue >> 21;

    return rvalue;
  }

  uint8_t  IDR[4];
};


class hw_can_msg_t
{
public:
  hw_can_id id;

  uint8_t  DSR[8]; // Data Segment Registers

  uint8_t  DLR;  // Data Length Code
  uint8_t  TBPR;   // Transmit buffer priority register
  uint16_t TSR;    // Time Stamp Register

  uint8_t *data(void)
  {
    return DSR;
  }

  ////////////////////////////////////////////////////////////////////////////
  // CAN message data access macros (bit position vs macro access mapping)
  //
  //          111111 11112222 22222233 33333333 44444444 44455555 55556666
  //   01234567 89012345 67890123 45678901 23456789 01234567 89012345 67890123
  //  | byte0  | byte1  | byte2  | byte3  | byte4  | byte5  | byte6  | byte7  |
  //  | word0 (LSB 1st) | word1 (LSB 1st) | word2 (LSB 1st) | word3 (LSB 1st) |
  //  |dword0 (LSB 1st)                   |dword1 (LSB 1st)                   |

  void set_byte(uint8_t n, uint8_t  value)
  {
    DSR[n&7] = value;
  }

  void set_word(uint8_t n, uint16_t value)
  {
    uint8_t i  = 2*(n & 3);

    DSR[i++] = (uint8_t)value;
    value >>= 8;
    DSR[i] = (uint8_t)value;
  }

  void set_dword(uint8_t n, uint32_t value)
  {
    uint8_t i = 4*(n & 1);

    DSR[i++] = (uint8_t)value;
    value >>= 8;
    DSR[i++] = (uint8_t)value;
    value >>= 8;
    DSR[i++] = (uint8_t)value;
    value >>= 8;
    DSR[i] = (uint8_t)value;
  }

  uint8_t get_byte(uint8_t n)
  {
    return DSR[n&7];
  }

  uint16_t get_word(uint8_t n)
  {
    uint8_t i = 2*(n & 3);
    uint16_t rvalue;
    
    rvalue = DSR[i+1];
    rvalue <<= 8;
    rvalue |=DSR[i];
    
    return rvalue;
  }

  uint32_t get_dword(uint8_t n)
  {
    uint8_t i = 4*(n & 1);

    uint32_t rvalue;

    rvalue = DSR[i+3];
    rvalue <<= 8;
    rvalue |= DSR[i+2];
    rvalue <<= 8;
    rvalue |= DSR[i+1];
    rvalue <<= 8;
    rvalue |= DSR[i];

    return rvalue;
  }
  
  uint8_t get_DLR() 
  {
    return DLR;
  }

};

#endif /* hw_can_msg_h */
