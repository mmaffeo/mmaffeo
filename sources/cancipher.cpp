#include "cancipher.h"

#define XTEA_ROUNDS 32
#define XTEA_HASH_ROUNDS 17
#define XTEA_KEY_ELEMENTS (sizeof(key) / sizeof(key[0]))
#define XTEA_DELTA 0x9E3779B9

#define DEFAULT_KEY_0 0xd88cb272
#define DEFAULT_KEY_1 0x285ecede
#define DEFAULT_KEY_2 0xb4b525af
#define DEFAULT_KEY_3 0x19666d97

#define HASH_KEY_0 0x19cd98d1
#define HASH_KEY_1 0x3e429287
#define HASH_KEY_2 0x5a5205c1
#define HASH_KEY_3 0x08754901

CanCipher CanCipher::inst;

uint32_t const hashKey[4] = {HASH_KEY_0, HASH_KEY_1, HASH_KEY_2, HASH_KEY_3};

CanCipher::CanCipher()
{
  setSerialNumber(0, 0);
}

void CanCipher::setSerialNumber(uint8_t const * serialNumber, uint8_t length)
{
  key[0] = DEFAULT_KEY_0;
  key[1] = DEFAULT_KEY_1;
  key[2] = DEFAULT_KEY_2;
  key[3] = DEFAULT_KEY_3;

  for (uint8_t i = 0; i < length; i++)
  {
    key[i % XTEA_KEY_ELEMENTS] ^= serialNumber[i];
  }
}

void CanCipher::saltThatKey(uint32_t * keyToSalt, hw_can_msg_t const * msg)
{
  uint16_t pgn = msg->id.get_J1939_PGN();
  uint32_t pgnSalt = (uint32_t)(((pgn & 0xffff) << 16) | ((~pgn) & 0xffff));

  keyToSalt[0] = key[0] ^ pgnSalt;
  keyToSalt[1] = key[1] * pgnSalt;
  keyToSalt[2] = key[2] & pgnSalt;
  keyToSalt[3] = key[3] | pgnSalt;
}

void CanCipher::encipher(hw_can_msg_t * msg)
{
  uint32_t data[2];
  uint8_t * msgDSR = msg->DSR;

  data[0] = msgDSR[3];
  data[0] <<= 8;
  data[0] |= msgDSR[2];
  data[0] <<= 8;
  data[0] |= msgDSR[1];
  data[0] <<= 8;
  data[0] |= msgDSR[0];

  data[1] = msgDSR[7];
  data[1] <<= 8;
  data[1] |= msgDSR[6];
  data[1] <<= 8;
  data[1] |= msgDSR[5];
  data[1] <<= 8;
  data[1] |= msgDSR[4];

  uint32_t saltedKey[4];
  saltThatKey(saltedKey, msg);

  encipherXtea(XTEA_ROUNDS, data, saltedKey);

  msgDSR[0] = (uint8_t)data[0];
  data[0] >>= 8;
  msgDSR[1] = (uint8_t)data[0];
  data[0] >>= 8;
  msgDSR[2] = (uint8_t)data[0];
  data[0] >>= 8;
  msgDSR[3] = (uint8_t)data[0];

  msgDSR[4] = (uint8_t)data[1];
  data[1] >>= 8;
  msgDSR[5] = (uint8_t)data[1];
  data[1] >>= 8;
  msgDSR[6] = (uint8_t)data[1];
  data[1] >>= 8;
  msgDSR[7] = (uint8_t)data[1];
}

void CanCipher::decipher(hw_can_msg_t * msg)
{
  uint32_t data[2];
  uint8_t * msgDSR = msg->DSR;

  data[0] = msgDSR[3];
  data[0] <<= 8;
  data[0] |= msgDSR[2];
  data[0] <<= 8;
  data[0] |= msgDSR[1];
  data[0] <<= 8;
  data[0] |= msgDSR[0];

  data[1] = msgDSR[7];
  data[1] <<= 8;
  data[1] |= msgDSR[6];
  data[1] <<= 8;
  data[1] |= msgDSR[5];
  data[1] <<= 8;
  data[1] |= msgDSR[4];

  uint32_t saltedKey[4];
  saltThatKey(saltedKey, msg);

  decipherXtea(XTEA_ROUNDS, data, saltedKey);

  msgDSR[0] = (uint8_t)data[0];
  data[0] >>= 8;
  msgDSR[1] = (uint8_t)data[0];
  data[0] >>= 8;
  msgDSR[2] = (uint8_t)data[0];
  data[0] >>= 8;
  msgDSR[3] = (uint8_t)data[0];

  msgDSR[4] = (uint8_t)data[1];
  data[1] >>= 8;
  msgDSR[5] = (uint8_t)data[1];
  data[1] >>= 8;
  msgDSR[6] = (uint8_t)data[1];
  data[1] >>= 8;
  msgDSR[7] = (uint8_t)data[1];
}

uint64_t CanCipher::hash(const uint8_t * input, const uint8_t length)
{
  uint32_t data[2];
  data[0] = hashKey[1];
  data[1] = hashKey[3];

  for (uint8_t i = 0; i < length; i++)
  {
    data[i % 2] = data[i % 2] ^ (((uint32_t)input[i]) << (8 * (i % 4)));
  }

  decipherXtea(XTEA_HASH_ROUNDS, data, hashKey);

  uint64_t retval = data[0];
  retval <<= 32;
  retval |= data[1];

  return retval;
}

void CanCipher::encipherXtea(unsigned int const num_rounds, uint32_t v[2], uint32_t const key[4])
{
  unsigned int i;
  uint32_t v0 = v[0];
  uint32_t v1 = v[1];
  uint32_t sum = 0;
  uint32_t delta = XTEA_DELTA;

  for (i = 0; i < num_rounds; i++)
  {
    v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
    sum += delta;
    v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
  }
  v[0] = v0;
  v[1] = v1;
}

void CanCipher::decipherXtea(unsigned int const num_rounds, uint32_t v[2], uint32_t const key[4])
{
  unsigned int i;
  uint32_t v0 = v[0];
  uint32_t v1 = v[1];
  uint32_t delta = XTEA_DELTA;
  uint32_t sum = delta * num_rounds;

  for (i = 0; i < num_rounds; i++) {
    v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
    sum -= delta;
    v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
  }
  v[0] = v0;
  v[1] = v1;
}
