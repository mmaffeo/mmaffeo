
#include <stdint.h>

typedef struct ecuid_s
{
  uint8_t sourceAddress;
  uint8_t moduleID;
  uint8_t reserved_00;
  uint8_t reserved_01;
  uint32_t swMask_ap_code;
  uint32_t swMask_ap_const;
  uint8_t part_number[7];
} ecuid_t;

#pragma location=".ecuid"
__root ecuid_t const ecuid =
{
  0xB0,         // sourceAddress
  0x0C,         // moduleID
  0x00,         // reserved_00
  0x00,         // reserved_01
  0x00000FC0,   // swMask_ap_code
  0x00000030,    // swMask_ap_const
  {0x37,0x32,0x36,0x30,0x39,0x34,0x30}  //part_number  7260939 Parker 7260940 Pektron
};

#pragma location=".checksum"
__root uint32_t const __checksum;
