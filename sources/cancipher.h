#ifndef CANCIPHER_H
#define CANCIPHER_H

#include <stdint.h>
#include "hw_can_msg.h"

class CanCipher
{
public:
  static CanCipher inst;

  /**
   * Initialize the key using a machine's serial number
   *
   * @brief setSerialNumber
   * @param serialNumber ASCII representation of a machine's serial number
   * @param length Length of serial number array
   */
  void setSerialNumber(uint8_t const * serialNumber, uint8_t const length);

  /**
   * Encipher the payload of a CAN message in place
   *
   * @brief encipher
   * @param msg The CAN message containing the payload to encipher
   */
  void encipher(hw_can_msg_t * msg);

  /**
   * Decipher the payload of a CAN message in place
   *
   * @brief decipher
   * @param msg The CAN message containing the payload to decipher
   */
  void decipher(hw_can_msg_t * msg);

  /**
   * Generate a hash of a byte array
   *
   * @brief hash
   * @param input The data to hash
   * @param length The length of the input array
   * @return Generated hash
   */
  uint64_t hash(const uint8_t * input, const uint8_t length);

private:
  CanCipher();

  void encipherXtea(unsigned int const num_rounds, uint32_t v[], const uint32_t key[]);
  void decipherXtea(unsigned int const num_rounds, uint32_t v[], const uint32_t key[]);

  uint32_t key[4];
  void saltThatKey(uint32_t * keyToSalt, hw_can_msg_t const * msg);
};

#endif // CANCIPHER_H
