#ifndef hw_eeprom_h
#define hw_eeprom_h

#include "hw_mcu.h"


enum ee_status
{
    ERR_OK = 0, ERR_BUSY, ERR_NOTAVAIL, ERR_RANGE, ERR_BATT
};

uint8_t hw_eeprom_read_uint8  (uint16_t address, uint8_t  *data);
uint8_t hw_eeprom_read_uint16 (uint16_t address, uint16_t *data);
uint8_t hw_eeprom_read_uint32 (uint16_t address, uint32_t *data);
uint8_t hw_eeprom_read(uint16_t size_, uint16_t address,uint8_t *data);

uint8_t hw_eeprom_write_uint16(uint16_t address, uint16_t value);
uint8_t hw_eeprom_write_uint32(uint16_t address, uint32_t value);

/////////////////////////////////////////////////////////////////////////////////////////////////////
// hw_io diver interface "user" should not need to access this information.
void hw_eeprom_initialize(void);
void hw_eeprom_update    (void);

uint8_t hw_eeprom_write_pending(void);

#endif