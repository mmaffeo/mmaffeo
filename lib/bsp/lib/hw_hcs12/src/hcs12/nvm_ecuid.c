


#include "nvm_ecuid.h"



nvm_ecuid_t nvm_ecuid;

void nvm_ecuid_t::initialize(void)
{
    uint16_t checksum = 0;

    uint16_t *near m = (uint16_t *near) 0x4000;
    uint16_t *near e = (uint16_t *near) 0x41FF;

    do
    {
        checksum += *m;
        ++m;
    } while ( m <= e);

    if (checksum == 0x0000)
    {
        j1939_source_address = *((uint8_t  *) 0x4000);
        bobcat_module_id     = *((uint8_t  *) 0x4001);
        ap_sw_code_smask     = *((uint16_t *) 0x4002);
        ap_sw_const_smask    = *((uint16_t *) 0x4004);
    }
    else
    {
        //use default values since numbers in nvm appear corrupted
        j1939_source_address = 253;

        bobcat_module_id     = 0x00;

        ap_sw_code_smask     = 0xFFFF;
        ap_sw_const_smask    = 0xFFFF;
    }
}


