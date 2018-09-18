

#ifndef J1939_name_h
#define J1939_name_h

#include "stdint.h"
#include "stdbool.h"
#include "hw_can.h"


class J1939_name
{
public:

  uint32_t idNumber;
  uint16_t manufacturerCode;
  uint8_t ecuInstance;
  uint8_t functionInstance;
  uint8_t function;
  uint8_t vehicleSystem;
  uint8_t vehicleSystemInstance;
  uint8_t industryGroup;
  bool arbitraryAddressCapable;

  void pack(uint8_t *data) const;
  void unpack(uint8_t const *data);
  void claimAddress(hw_can_txq_t *canChannel, uint8_t sourceAddress) const;
};

#endif  // J1939_name_h

