

#ifndef nvm_ecuid_h
#define nvm_ecuid_h

#include "stdint.h"


class nvm_ecuid_t
{
public:
    void initialize(void);

    uint8_t  j1939_source_address;
    uint8_t  bobcat_module_id;
    uint16_t ap_sw_code_smask;
    uint16_t ap_sw_const_smask;
};


extern nvm_ecuid_t nvm_ecuid;


#endif
