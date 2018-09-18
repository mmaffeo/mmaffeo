#include "ap_version.h"

#ifdef HCS12_BSP_EMU  //M4 Controller
const uint16_t sw_ed_number=1343;
const uint8_t hw_version=0;
const uint8_t sw_title[] = "ED-1343 - MX M4 GATEWAY CONTROLLER - 23 JULY 2018";
#else //HCS12 Controller
const uint16_t sw_ed_number=1286;
const uint8_t hw_version=0;
const uint8_t sw_title[] = "ED-1286 - MX GATEWAY CONTROLLER - 25 MAY 2018";
#endif

const uint8_t sw_type='B';
const uint8_t sw_version_major=99;
const uint8_t sw_version_minor=00;