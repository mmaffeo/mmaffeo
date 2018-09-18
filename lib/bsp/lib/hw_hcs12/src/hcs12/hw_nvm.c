/*
    This module checks the application software programmed into this control.
*/
#include "hw_nvm.h"

#include "hw_eeprom.h"


typedef struct
{
    uint16_t section;
    uint32_t min_addr;
    uint32_t max_addr;
} section_t;


const section_t EEPROM_SECTIONS[]=
{
    {(uint16_t)  E0,  0xFFFFC0, 0xFFFFEF},  // Manufacturing Data
    {(uint16_t)  E1,  0xFFFF80, 0xFFFFBF},  // Hour Meter
    {(uint16_t)  E2,  0xFFFF40, 0xFFFF7F},  // Unused
    {(uint16_t)  E3,  0xFFF000, 0xFFFF3F},  // Mirror
};

static const uint8_t EEPROM_SECTION_QTY= sizeof(EEPROM_SECTIONS)/sizeof(section_t);


uint16_t hw_nvm_eeprom_checksum (uint16_t section_mask)
{
    uint16_t checksum=0;

    for (uint8_t i=0; i<EEPROM_SECTION_QTY; ++i)
    {
        if (EEPROM_SECTIONS[i].section & section_mask)
        {
            #pragma MESSAGE DISABLE C1860
            uint16_t *near m = (uint16_t *near)(0xFFF & (uint16_t) EEPROM_SECTIONS[i].min_addr);
            uint16_t *near e = (uint16_t *near)(0xFFF & (uint16_t) EEPROM_SECTIONS[i].max_addr);
            #pragma MESSAGE DEFAULT C1860

            do
            {
                checksum += *m;
                ++m;
            } while ( m <= e);
        }
    }

    return checksum;
}

bool hw_nvm_eeprom_write_pending(void)
{
  return (bool)hw_eeprom_write_pending();
}

void hw_nvm_initialize(void)
{
}

void hw_nvm_update(void)
{
}


static hw_nvm_status get_eeprom_address(hw_nvm_eeprom_section_t s,
                                        uint16_t nvm_address,
                                        uint16_t *eeprom_address)
{
    uint8_t i=0;

    while (i <EEPROM_SECTION_QTY && s!=EEPROM_SECTIONS[i].section)
        ++i;

    if (i==EEPROM_SECTION_QTY)
        return NVM_RANGE;

    uint16_t s_size = 1+ (uint16_t)EEPROM_SECTIONS[i].max_addr - (uint16_t)EEPROM_SECTIONS[i].min_addr;

    if (nvm_address >= (s_size ) )
        return NVM_RANGE;

    *eeprom_address = ((0xFFF) & (uint16_t) EEPROM_SECTIONS[i].min_addr) + nvm_address;

    return NVM_OK;
}

hw_nvm_status hw_nvm_eeprom_read(hw_nvm_eeprom_section_t s, uint16_t size_, uint16_t address, uint8_t *data)
{
  uint16_t ee_address;

  hw_nvm_status status = get_eeprom_address(s, address, &ee_address);

  if (status == NVM_OK)
  {
    status = (hw_nvm_status)hw_eeprom_read(size_, ee_address, data);
  }

  return status;
}


hw_nvm_status hw_nvm_eeprom_read_uint8 (hw_nvm_eeprom_section_t s, uint16_t address, uint8_t *data)
{
    uint16_t ee_address;

    hw_nvm_status status = get_eeprom_address(s, address, &ee_address);

    if (status == NVM_OK)
        status = (hw_nvm_status) hw_eeprom_read_uint8(ee_address, data) ;

    return status;
}


hw_nvm_status hw_nvm_eeprom_read_uint16 (hw_nvm_eeprom_section_t s, uint16_t address, uint16_t *data)
{
    uint16_t ee_address;

    hw_nvm_status status = get_eeprom_address(s, address, &ee_address);

    if (status == NVM_OK)
        status = (hw_nvm_status) hw_eeprom_read_uint16(ee_address, data) ;

    return status;
}

hw_nvm_status hw_nvm_eeprom_read_uint32(hw_nvm_eeprom_section_t s, uint16_t address, uint32_t *data)
{
    uint16_t ee_address;

    hw_nvm_status status = get_eeprom_address(s, address, &ee_address);

    if (status == NVM_OK)
        status = (hw_nvm_status) hw_eeprom_read_uint32(ee_address, data) ;

    return status;
}
hw_nvm_status hw_nvm_eeprom_write_uint16(hw_nvm_eeprom_section_t s,
                                         uint16_t address,
                                         uint16_t data)
{
    uint16_t ee_address;

    hw_nvm_status status = get_eeprom_address(s, address, &ee_address);

    if (status == NVM_OK)
        status = (hw_nvm_status) hw_eeprom_write_uint16(ee_address, data);

    return status;
}


hw_nvm_status hw_nvm_eeprom_write_uint32(hw_nvm_eeprom_section_t s,
                                         uint16_t address,
                                         uint32_t data)
{
    uint16_t ee_address;

    hw_nvm_status status = get_eeprom_address(s, address, &ee_address);

    if (status == NVM_OK)
        status = (hw_nvm_status) hw_eeprom_write_uint32(ee_address, data);

    return status;
}



#ifdef BB_COMPILE

#include "flash.h"

const section_t FLASH_SECTIONS[]=
{
    {(uint16_t)  F0,  0x3FB800, 0x3FBFFE},
    {(uint16_t)  F1,  0x3FB000, 0x3FB7FE},
    {(uint16_t)  F2,  0x3FA000, 0x3FAFFE},
    {(uint16_t)  F3,  0x3F8000, 0x3F9FFE},
    {(uint16_t)  F4,  0x3EA000, 0x3EBFFE},
    {(uint16_t)  F5,  0x3E9000, 0x3E9FFE},
    {(uint16_t)  F6,  0x3E8800, 0x3E8FFE},
    {(uint16_t)  F7,  0x3E8400, 0x3E87FE},
    {(uint16_t)  F8,  0x3E8200, 0x3E83FE},
    {(uint16_t)  F9,  0x3E8000, 0x3E81FE},
    {(uint16_t) F10,  0x3D8000, 0x3DBFFE},
    {(uint16_t) F11,  0x3C8000, 0x3CBFFE},
    {(uint16_t) F12,  0x3B8000, 0x3BBFFE},
    {(uint16_t) F12,  0x3A8000, 0x3ABFFE},
    {(uint16_t) F12,  0x398000, 0x39BFFE},
    {(uint16_t) F12,  0x388000, 0x38BFFE},
    {(uint16_t) F13,  0x378000, 0x37BFFE},
    {(uint16_t) F13,  0x368000, 0x36BFFE},
    {(uint16_t) F13,  0x358000, 0x35BFFE},
    {(uint16_t) F13,  0x348000, 0x34BFFE},
    {(uint16_t) F13,  0x338000, 0x33BFFE},
    {(uint16_t) F13,  0x328000, 0x32BFFE},
    {(uint16_t) F13,  0x318000, 0x31BFFE},
    {(uint16_t) F13,  0x308000, 0x30BFFE}
};
static const uint8_t FLASH_SECTION_QTY= sizeof(FLASH_SECTIONS)/sizeof(section_t);


uint16_t hw_nvm_flash_checksum (uint16_t section_mask)
{
    uint16_t checksum=0;

    for (uint8_t i=0; i<FLASH_SECTION_QTY ; ++i)
    {
        if (FLASH_SECTIONS[i].section & section_mask)
        {
            #pragma MESSAGE DISABLE C1860
            uint16_t *near m = (uint16_t *near) FLASH_SECTIONS[i].min_addr;
            uint16_t *near e = (uint16_t *near) FLASH_SECTIONS[i].max_addr;
            #pragma MESSAGE DEFAULT C1860

            uint8_t page = (uint8_t) ( (uint32_t) FLASH_SECTIONS[i].min_addr >> 16   ) ;
            PPAGE = page;

            do
            {
                checksum += *m;
                ++m;
            } while ( m <= e);
        }
    }

    return checksum;
}



hw_nvm_status hw_nvm_flash_erase    (uint16_t section_mask)
{
    uint8_t rvalue=0;;
    for (uint8_t i=0; i<(sizeof(FLASH_SECTIONS)/sizeof(section_t)); ++i)
    {
        if (FLASH_SECTIONS[i].section & section_mask)
        {
            if      (FLASH_SECTIONS[i].section == F12)
            {
               rvalue |= flash_erase_blocks(BLOCK1);
            }
            else if (FLASH_SECTIONS[i].section == F13)
            {
                rvalue |= flash_erase_blocks(BLOCK2|BLOCK3);
            }
            else
            {
                uint32_t addr = PROG_to_SSD_address((uint32_t)FLASH_SECTIONS[i].min_addr);

                uint32_t top = PROG_to_SSD_address((uint32_t) FLASH_SECTIONS[i].max_addr);

                uint16_t size = (uint16_t)((top-addr+2)/FLASH_SECTOR_SIZE);
                rvalue |= flash_erase_sectors(addr, size);
            }


        }
    }
    return (rvalue == FLASH_OK)? NVM_OK: !NVM_OK;
}


hw_nvm_status hw_nvm_program(uint32_t dest_address,
                             uint32_t size,
                             uint16_t src_address   )
{
    uint32_t ssd_addr = dest_address;

    uint8_t status = flash_program(ssd_addr, size, src_address);

    return (status == FLASH_OK)? NVM_OK: !NVM_OK;
}


hw_nvm_status hw_nvm_eeprom_erase    (uint16_t section_mask)
{
    uint8_t rvalue=0;
    for (uint8_t i=0; i<(sizeof(EEPROM_SECTIONS)/sizeof(section_t)); ++i)
    {
        if (EEPROM_SECTIONS[i].section & section_mask)
        {
            uint32_t addr = 0xFFF & (uint16_t) EEPROM_SECTIONS[i].min_addr;

            uint32_t top = 0xFFF &  (uint16_t) EEPROM_SECTIONS[i].max_addr;

            uint16_t size = (uint16_t)((top-addr+2)/EEPROM_SECTOR_SIZE);
            rvalue |= flash_erase_sectors(addr, size);
        }
    }
    return (rvalue == FLASH_OK)? NVM_OK: !NVM_OK;
}


#endif


