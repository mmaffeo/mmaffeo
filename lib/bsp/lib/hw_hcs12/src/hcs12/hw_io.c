
#include "hw_io.h"
#include "nvm_ecuid.h"
#include "hw_eeprom.h"

uint16_t max_stack_size = 0;


void hw_io_initialize(void)
{
  // inputs...
  hw_adc_initialize();
  hw_fin_initialize();
  hw_dio_initialize();

  // outputs...
  hw_pwm_initialize();

  hw_gauge_initialize();

  hw_eeprom_initialize();
  hw_nvm_initialize();

  hw_can_initialize();

  hw_mcu_initialize();

  nvm_ecuid.initialize();
}


void hw_io_update(void)
{
  // inputs...

  hw_dio_wc_activate();

  hw_adc_update();
  hw_fin_update();
  hw_dio_update();

  hw_dio_wc_deactivate();

  // outputs...
  hw_pwm_update();
  hw_gauge_update();

  hw_eeprom_update();
  hw_nvm_update();

  hw_can_update();

  hw_mcu_update();


  max_stack_size = hw_reset_max_stack();
}

uint8_t hw_readByteDirect(uint32_t address)
{
  return *(uint8_t * far) address;
}

uint16_t hw_readWordDirect(uint32_t address)
{
  return *(uint16_t * far) address;
}
uint32_t hw_readDwordDirect(uint32_t address)
{
  return *(uint32_t * far) address;
}



