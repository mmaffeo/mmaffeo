#ifndef PASSWORDVERIFIER_H
#define PASSWORDVERIFIER_H

#include <stdint.h>

class PasswordVerifier
{
public:
  /**
   * Validates the supplied password (4-10 digits) against a known hash
   *
   * @brief validateHash
   * @param password ASCII representation of a password terminated with 0 if shorter than 10
   * @param hash Known hash
   * @return bool
   */
  static bool validateHash(uint8_t const * password, uint64_t hash);

private:
  PasswordVerifier();
};

#endif // PASSWORDVERIFIER_H
