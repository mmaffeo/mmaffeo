// Reference Documents
//
//  Motorola S12EETS2KV1/D (EETS2K Block User Guide V01.03)

#include "hw_eeprom.h"

#include "hw_mcu.h"    // MCU register definitions
#include "hw_config.h"
#include "hw_adc.h"
//#include "ap_subs.h"
#include "hw_nvm.h"
#include <string.h>  //


enum
{
    ECMD_EraseVerify =0x05,
    ECMD_WordProgram =0x20,
    ECMD_SectorErase =0x40,
    ECMD_MassErase   =0x41,
    ECMD_SectorModify=0x60
};

#define MINIMUM_BATTERY_LEVEL  204

////////////////////////////////////////////////////////////////////////////////////////////////////
// eeprom write queue
#ifndef AF_EEPROM_WQ_SIZE
#define AF_EEPROM_WQ_SIZE 16
#endif

typedef struct
{
    uint8_t  size;
    uint16_t address;
    uint32_t data;
} eeprom_wq_element_t;


static uint16_t HW_EEPROM_START_ADDRESS;
static uint16_t HW_EEPROM_END_ADDRESS;

static eeprom_wq_element_t wq_e[AF_EEPROM_WQ_SIZE];
static uint16_t        wq_head;     // newest entry
static uint16_t        wq_tail;     // oldest entry
static uint16_t        wq_size;     // number of words waiting in queue.
static uint16_t        wq_max_size;   // largest depth the queue has achieved


static void wq_index_inc(uint16_t * ptr)
{
    *ptr += 1;

    if (*ptr == AF_EEPROM_WQ_SIZE)
        *ptr = 0;
}


uint8_t hw_eeprom_write_pending(void) { return wq_size!=0 || ESTAT_CCIF==0;}



uint8_t hw_eeprom_read(uint16_t size_, uint16_t address,uint8_t *data)
{
    uint8_t rvalue;
    uint16_t tempVBattery;

    tempVBattery = hw_adc_GetValue(HWC_ADC_BATT_AFBK);

    if(tempVBattery > MINIMUM_BATTERY_LEVEL)
    {

      switch (size_) // make sure address is valid
      {
          case 1:  address &=0xFFF; break;
          case 2:  address &=0xFFE; break;
          default:
          case 4:  address &=0xFFC; break;
      }

      if ( address <  HW_EEPROM_START_ADDRESS  || address > HW_EEPROM_END_ADDRESS )
      {
          rvalue = ERR_RANGE;
      }
      else if ( hw_eeprom_write_pending() ) // Can only read EEPROM when no commands are in progress.
      {
          rvalue  = ERR_BUSY;
      }
      else
      {
          rvalue = ERR_OK;
          memcpy2(data,(uint8_t *) address, size_ ) ;
      }
    }
    else
    {
      rvalue = ERR_BATT;
    }

    return rvalue;
}

uint8_t hw_eeprom_read_uint8 (uint16_t address,uint8_t  *data){return hw_eeprom_read(1, address, (uint8_t*) data); }
uint8_t hw_eeprom_read_uint16(uint16_t address,uint16_t *data){return hw_eeprom_read(2, address, (uint8_t*) data); }
uint8_t hw_eeprom_read_uint32(uint16_t address,uint32_t *data){return hw_eeprom_read(4, address, (uint8_t*) data); }


static uint8_t add_to_wq_e(uint8_t size_, uint16_t address, uint32_t data )
{
    uint8_t rvalue;

    uint16_t tempVBattery;

    tempVBattery = hw_adc_GetValue(HWC_ADC_BATT_AFBK);

    if(tempVBattery > MINIMUM_BATTERY_LEVEL)
    {
      if (size_==2)
          address &=0xFFFE;    // even address and withing map
      else  //size==4
          address &=0xFFFC;

      if ( address <  HW_EEPROM_START_ADDRESS  || address > HW_EEPROM_END_ADDRESS )
      {
          rvalue = ERR_RANGE;
      }
      else if (wq_size >= AF_EEPROM_WQ_SIZE ) // queue is full
      {
          rvalue = ERR_BUSY;
      }
      else
      {
          rvalue = ERR_OK;
          // add new data to the eeprom write queue
          ++wq_size;
          if (wq_size > wq_max_size)
              wq_max_size = wq_size;

          wq_index_inc(&wq_head);

          wq_e[wq_head].size    = size_;
          wq_e[wq_head].address = address;
          wq_e[wq_head].data    = data;
      }
    }
    else
    {
      rvalue = ERR_BATT;
    }

    return rvalue;
}

uint8_t hw_eeprom_write_uint16(uint16_t address, uint16_t value) { return add_to_wq_e(2,address,value);    }
uint8_t hw_eeprom_write_uint32(uint16_t address, uint32_t value) { return add_to_wq_e(4,address,value);    }


///////////////////////////////////////////////////////////////////////////////////////////////////
// EEPROM test functionality...
///////////////////////////////////////////////////////////////////////////////////////////////////

uint16_t            hwt_eeprom_tcmd;
uint16_t            hwt_eeprom_tfailures;
hwt_eeprom_tstate_t hwt_eeprom_tstate;



static void hwt_eeprom_test_initialize(void)
{
     hwt_eeprom_tcmd = 0;
     hwt_eeprom_tfailures = 0;
     hwt_eeprom_tstate = HWT_EETS_IDLE;
}


enum eet_state_t
{
    EET_IDLE,
    EET_WRITE,
    EET_READ,
    EET_ERASE_VERIFY
};
static eet_state_t  eet_state;

static uint8_t eet_pattern=0 ;
static uint16_t * eet_address;


static const uint16_t EET_PATTERN[] = {0x0102,0x0408,0x1020,0x4080,0xA55A,
                                       0xFEFD,0xFBF7,0xEFDF,0xBF7F,0x00FF  };



#define EET_PATTERN_SIZE (sizeof(EET_PATTERN)/sizeof(uint16_t))


static void inc_tfailures(void)
{
    if ( hwt_eeprom_tfailures < UINT16_MAX )
        ++hwt_eeprom_tfailures;
}

static void hwt_eeprom_test_update(void)
{
    switch (eet_state)
    {
        case EET_IDLE:
            if (ESTAT_CCIF && hwt_eeprom_tcmd !=0)
            {
                hwt_eeprom_tcmd = 0;
                hwt_eeprom_tfailures = 0;
                hwt_eeprom_tstate = HWT_EETS_RUNNING;

                eet_state = EET_WRITE;
                eet_address = (uint16_t *) HW_EEPROM_START_ADDRESS;

                ESTAT |= 0x30;  // write ones to PVIOL and ACCERR
                *eet_address = 0x0000; //dummy write to
                ECMD=ECMD_MassErase;
                ESTAT_CBEIF=1; // initiate the command by writing a "one" to CBEIF
            }

            break;

        case EET_WRITE:
            uint8_t i = 0;

            if (ESTAT_CCIF)
            while ( i<EET_PATTERN_SIZE &&
                    eet_address < (uint16_t *) HW_EEPROM_END_ADDRESS  )
            {
                while (ESTAT_CCIF ==0);

                ESTAT |= 0x30;  // write ones to PVIOL and ACCERR
                *eet_address = EET_PATTERN[i];

                ECMD=ECMD_WordProgram;
                ESTAT_CBEIF=1; // initiate the command by writing a "one" to CBEIF

                ++eet_address;
                ++i;
            }

            if (eet_address > (uint16_t *) HW_EEPROM_END_ADDRESS )
                eet_state   = EET_READ;

            break;
        case EET_READ:

            uint8_t i = 0;
            eet_address = (uint16_t *) HW_EEPROM_START_ADDRESS;

            if (ESTAT_CCIF)
            while ( eet_address < (uint16_t *) HW_EEPROM_END_ADDRESS  )
            {
                if ( *eet_address != EET_PATTERN[i])
                    inc_tfailures();

                ++eet_address;
                ++i;
                if ( i >= EET_PATTERN_SIZE )
                    i = 0;
            }

            eet_state = EET_ERASE_VERIFY;
            ESTAT |= 0x30;  // write ones to PVIOL and ACCERR
            *(uint16_t *) HW_EEPROM_START_ADDRESS = 0x0000; //dummy write to  initiate command sequence
            ECMD=ECMD_MassErase;
            ESTAT_CBEIF=1; // initiate the command by writing a "one" to CBEIF

            break;

        case EET_ERASE_VERIFY:
      eet_address = (uint16_t *) HW_EEPROM_START_ADDRESS;

            if (ESTAT_CCIF)
            while ( eet_address < (uint16_t *) HW_EEPROM_END_ADDRESS  )
            {
                if ( *eet_address != 0xFFFF)
                    inc_tfailures();

                ++eet_address;
            }

            hwt_eeprom_tstate =  hwt_eeprom_tfailures==0 ? HWT_EETS_IDLE_SUCCESS:    HWT_EETS_IDLE_FAILURE;
            eet_state = EET_IDLE;

            break;
    }
}





//////////////////////////////////////////////////////////////////////////////////////
// eeprom write queue handling functions...


void hw_eeprom_initialize(void)
{
    uint8_t eep_sw = (MEMSIZ0 & 0x30) >> 4;

    switch (eep_sw)
    {
        default:
        case 1:  // 2k of EEPROM
            HW_EEPROM_START_ADDRESS = 2048;
            HW_EEPROM_END_ADDRESS   = 4079;
            break;
        case 2:  // 4k of EEPROM
            HW_EEPROM_START_ADDRESS = 1024;
            HW_EEPROM_END_ADDRESS   = 4079;
            break;

    }

    // wq_* variables get initialized to zero by the compiler startup code.


    uint8_t PRDIV8_value = OSCCLK_FREQ_KHZ > 12800 ? 0x40:0;

    uint8_t EDIV_value = (uint8_t) (OSCCLK_FREQ_KHZ / ((PRDIV8_value?8:1)*200));


    ECLKDIV =  PRDIV8_value // EEPROM Clock divider Register
             | EDIV_value;  //  << EDIVLD:PRDIV8:EDIV(6-bits) >>
                        //  EDIVLD (Clock Divider Loaded) Read Only
                            //      0-register has not been written since last reset
                            //      1-register has been initialized
                            //
                            //  PRDIV8 -Enable Prescaler by 8
                            //  EDIV   -Clock Divider Bits

                            // EEPROM clock must be between 150kHz and 200kHz
                            // EEPROM clock = OSCCLK_FREQ / ((PRDIV8?8:1)*EDIV)


    hwt_eeprom_test_initialize();


}


void hw_eeprom_update    (void)    // called periodically (every 10mS)
{
    if ( ESTAT_CCIF && wq_size > 0 )
    {
        --wq_size;           // increment the tail of the queue pointer.
        wq_index_inc(&wq_tail);

        // write the next peice of data from the write queue.
        uint16_t Addr = wq_e[wq_tail].address;
        uint32_t Data = wq_e[wq_tail].data;
        uint8_t  Size = wq_e[wq_tail].size;

        if (Size == 2 && *(volatile uint16_t *)Addr == 0xFFFF)
        {   //The given EEPROM row is erased
            ESTAT |= 0x30;  // write ones to PVIOL and ACCERR
            *(volatile uint16_t *) Addr = (uint16_t) Data;     // write the new data...
            ECMD=ECMD_WordProgram;
            ESTAT_CBEIF=1; // initiate the command by writing a "one" to CBEIF
        }
        else
        {
            uint16_t sec_address = Addr & 0xFFFC;
            uint32_t sec_data;

            if (Size==2)
                sec_data = (Addr & 0x02) ?
                             ((uint32_t)Data        | ((*(volatile uint32_t *)(Addr & 0xFFFC) & 0xFFFF0000))) :
                             ((uint32_t)Data << 16) |  (*(volatile  uint16_t *)(Addr + 2))                     ;
            else // size==4
                sec_data =  Data;

            ESTAT |= 0x30;  // write ones to PVIOL and ACCERR
            *(volatile uint16_t *) sec_address = (uint16_t)(sec_data >> 16);
            ECMD = ECMD_SectorModify;
            ESTAT_CBEIF=1; // initiate the command by writing a "one" to CBEIF

            while (ESTAT_CBEIF == 0);    // wait for the command buffer to empty.

            ESTAT |= 0x30;  // write ones to PVIOL and ACCERR
            *(volatile uint16_t *) (sec_address+2) = (uint16_t) sec_data;     // write the new data...
            ECMD=ECMD_WordProgram;
            ESTAT_CBEIF=1; // initiate the command by writing a "one" to CBEIF
        }
    }
    else
    {
        hwt_eeprom_test_update();
    }
}




