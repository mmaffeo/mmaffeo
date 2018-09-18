

#ifndef hw_nvm_h
#define hw_nvm_h

#include "stdint.h"
#include "stdbool.h"


enum hw_nvm_eeprom_section_t
{
    E0=0x0001, E1=0x0002, E2=0x0004, E3=0x0008, E4=0x0010, E5=0x0020, E6=0x0040, E7=0x0080,
    E8=0x0100, E9=0x0200,E10=0x0400
};

enum hw_nvm_status
{
    NVM_OK=0, NVM_BUSY, NVM_NOTAVAIL, NVM_RANGE, NVM_BATT
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clarification concerning eeprom read/write function arguments...
//
// 1) Each address contains 8-bits of data.
//      An address for uint16 data -> least significant   bit   is don't care (assumed zero)
//      An address for uint32 data -> least significant 2 bits are don't care (assumed zero)
//
// 2) Multibyte data is stored and retrieved in the format native to the machine the code is executing on.
//      Example:
//         On a Motorola (Big Endian) processor
//                          ...write_uint32(E0,0,0x12345678);   // will result in
//                          ....read_uint8 (E0,0, &d0);         //    d0==0x12
//                          ....read_uint8 (E0,1, &d1);         //    d1==0x34
//                          ....read_uint8 (E0,2, &d2);         //    d2==0x56
//                          ....read_uint8 (E0,3, &d3);         //    d3==0x78
//
//         On an Intel (Little Endian) processor
//                          ...write_uint32(E0,0,0x12345678);   // will result in
//                          ....read_uint8 (E0,0, &d0);         //    d0==0x78
//                          ....read_uint8 (E0,1, &d1);         //    d1==0x56
//                          ....read_uint8 (E0,2, &d2);         //    d2==0x34
//                          ....read_uint8 (E0,3, &d3);         //    d3==0x12
//
hw_nvm_status hw_nvm_eeprom_read(hw_nvm_eeprom_section_t s, uint16_t size_, uint16_t address, uint8_t *data);
hw_nvm_status hw_nvm_eeprom_read_uint8(hw_nvm_eeprom_section_t s, uint16_t address, uint8_t *data);
hw_nvm_status hw_nvm_eeprom_read_uint16(hw_nvm_eeprom_section_t s, uint16_t address, uint16_t *data);
hw_nvm_status hw_nvm_eeprom_read_uint32(hw_nvm_eeprom_section_t s, uint16_t address, uint32_t *data);

hw_nvm_status hw_nvm_eeprom_write_uint16(hw_nvm_eeprom_section_t s, uint16_t address, uint16_t data);
hw_nvm_status hw_nvm_eeprom_write_uint32(hw_nvm_eeprom_section_t s, uint16_t address, uint32_t data);

uint16_t hw_nvm_eeprom_checksum(uint16_t section_mask);

bool hw_nvm_eeprom_write_pending(void);

void hw_nvm_initialize(void);
void hw_nvm_update(void);


///////////////////////////////////////////////////////////////////////////////////////////////////
// EEPROM test functionality...
///////////////////////////////////////////////////////////////////////////////////////////////////
enum hwt_eeprom_tstate_t
{
    HWT_EETS_IDLE, HWT_EETS_IDLE_SUCCESS, HWT_EETS_IDLE_FAILURE, HWT_EETS_RUNNING,
};
extern hwt_eeprom_tstate_t  hwt_eeprom_tstate;
extern uint16_t hwt_eeprom_tcmd;
extern uint16_t hwt_eeprom_tfailures;


// the following functions are only availiable in the bootblock
#ifdef BB_COMPILE

enum hw_nvm_flash_section_t
{
    F0=0x0001, F1=0x0002, F2=0x0004, F3=0x0008, F4=0x0010, F5=0x0020, F6=0x0040, F7=0x0080,
    F8=0x0100, F9=0x0200,F10=0x0400,F11=0x0800,F12=0x1000,F13=0x2000
};
uint16_t      hw_nvm_flash_checksum (uint16_t section_mask);
hw_nvm_status hw_nvm_flash_erase    (uint16_t section_mask);
hw_nvm_status hw_nvm_eeprom_erase   (uint16_t section_mask);

// "src_address" can't be in the same flash block as "dest_address"
hw_nvm_status hw_nvm_program(uint32_t dest_address,
                             uint32_t size,
                             uint16_t src_address    );
#endif

#endif