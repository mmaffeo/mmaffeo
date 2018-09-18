
#include "J1939_name.h"
#include "stdint.h"
#include "stdbool.h"
//#include "hw_mscan.h"


//******************************************************************************
/**
 * Pack the fields of a j1939 name.
 *
 * \note See document saej1939-81 section 4.2.1.1
 *
 * \param data  8 byte array to pack the name data into
 *
 * \return void
 *******************************************************************************/
void J1939_name::pack(uint8_t *data) const
{
  uint32_t temp;

  // byte   7        6        5        4        3        2        1        0
  // bit    76543210 76543210 76543210 76543210 76543210 76543210 76543210 76543210
  // field  jiiihhhh gggggggf eeeeeeee dddddccc bbbbbbbb bbbaaaaa aaaaaaaa aaaaaaaa

  // a - idNumber
  temp = idNumber;
  data[0] = (uint8_t)temp;
  temp >>= 8;
  data[1] = (uint8_t)temp;
  temp >>= 8;
  data[2] = (uint8_t)(temp & 0x1F);

  // b - manufacturerCode
  temp = (manufacturerCode << 5);
  data[2] |= (uint8_t)temp;
  temp >>= 8;
  data[3] = (uint8_t)temp;

  // c - ecuInstance
  data[4] = (ecuInstance & 0x07);

  // d - functionInstance
  data[4] |= (functionInstance << 3);

  // e - function
  data[5] = function;

  // f - reserved, set to 0

  // g - vehicleSystem
  data[6] = (vehicleSystem << 1);

  // h - vehicleSystemInstance
  data[7] = (vehicleSystemInstance & 0x0F);

  // i - industryGroup
  data[7] |= ((industryGroup << 4) & 0x70);

  // j - arbitraryAddressCapable
  if (arbitraryAddressCapable)
  {
    data[7] |= 0x80;
  }
}

//******************************************************************************
/**
 * Unpack the fields of a j1939 name.
 *
 * \note See document saej1939-81 section 4.2.1.1
 *
 * \param data  8 byte array containing the packed name data
 *
 * \return void
 *******************************************************************************/
void J1939_name::unpack(uint8_t const *data)
{
  // byte   7        6        5        4        3        2        1        0
  // bit    76543210 76543210 76543210 76543210 76543210 76543210 76543210 76543210
  // field  jiiihhhh gggggggf eeeeeeee dddddccc bbbbbbbb bbbaaaaa aaaaaaaa aaaaaaaa

  // a - idNumber
  idNumber = (data[2] & 0x1F);
  idNumber <<= 8;
  idNumber |= data[1];
  idNumber <<= 8;
  idNumber |= data[0];

  // b - manufacturerCode
  manufacturerCode = data[3];
  manufacturerCode <<= 8;
  manufacturerCode |= data[2];
  manufacturerCode >>= 5;

  // c - ecuInstance
  ecuInstance = (data[4] & 0x07);

  // d - functionInstance
  functionInstance = (data[4] >> 3);

  // e - function
  function = data[5];

  // f - reserved, set to 0

  // g - vehicleSystem
  vehicleSystem = (data[6] >> 1);

  // h - vehicleSystemInstance
  vehicleSystemInstance = (data[7] & 0x0F);

  // i - industryGroup
  industryGroup = ((data[7] & 0x70) >> 4);

  // j - arbitraryAddressCapable
  if (data[7] & 0x80)
  {
    arbitraryAddressCapable = true;
  }
  else
  {
    arbitraryAddressCapable = false;
  }
}

//******************************************************************************
/**
 * Claim a J1939 address using this name
 *
 * \param hw_can_txq      can tx queue to transmit the claim on
 * \param sourceAddress   source address to claim
 *
 * \return void
 *******************************************************************************/
void J1939_name::claimAddress(hw_can_txq_t *hw_can_txq, uint8_t sourceAddress) const
{
  hw_can_msg_t addressClaimMsg;

  addressClaimMsg.id.set_J1939ID(6,               // Priority
                                 0xEE,            // PF - PDU Format
                                 0xFF,            // PS - PDU Specific
                                 sourceAddress);  // Source Address

  pack(addressClaimMsg.DSR);

  addressClaimMsg.DLR = 8;

  hw_can_txq->send_msg(&addressClaimMsg);
}

