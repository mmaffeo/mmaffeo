#include "passwordverifier.h"
#include "cancipher.h"

#define PASSWORD_TERMINATING_CHAR 0x0
#define PASSWORD_MAX_LENGTH 10
#define PASSWORD_MIN_LENGTH 4
#define PASSED_PASSWORD_MASK 0x00FFFFFFFFFFFFFF
#define LENGTH_OFFSET 0

PasswordVerifier::PasswordVerifier() {}

bool PasswordVerifier::validateHash(const uint8_t * password, uint64_t hash)
{
    uint8_t length = PASSWORD_MAX_LENGTH;

    for (uint8_t i = PASSWORD_MIN_LENGTH; i < PASSWORD_MAX_LENGTH; i++)
    {
        if (password[i] == PASSWORD_TERMINATING_CHAR)
        {
            length = i + LENGTH_OFFSET;
            break;
        }
    }

    uint64_t temp = CanCipher::inst.hash(password, length);
    return hash == (PASSED_PASSWORD_MASK & temp);
}
