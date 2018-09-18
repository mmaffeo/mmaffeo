
#ifndef hw_mcu_h
#define hw_mcu_h


#include "hw_timer.h"
#include "stdint.h"
#include "stdbool.h"

#ifdef HCS12_BSP_EMU

# include "bsp_mcu.h"
# define __DI()
# define __EI()

# define EnterCritical()   do { bsp_enterCritical(); }while(0)
# define ExitCritical()    do { bsp_exitCritical(); }while(0)

#else

#include <mc9s12dg128.h>

#define __DI()            { asm sei; }      // Disable global interrupts
#define __EI()            { asm cli; }      // Enable global interrupts
#define EnterCritical()   { __asm pshc; __asm sei; __asm movb 1,SP+,CCR_reg; } // save CCR and /* Saves CCR register and disable global interrupts. */
#define ExitCritical()    { __asm movb CCR_reg, 1,-SP; __asm pulc; }         // restores interrupt enable state based on saved CCR

extern uint8_t CCR_reg;

void hw_mcu_output_enable_PutVal(bool value);
void hw_mcu_MuxSel_PutVal       (uint8_t value);


void hw_mcu_dout_latch_PutVal(bool value);
void hw_mcu_din_load_PutVal  (bool value);

void hw_initialize(void);       // initialize various PCB specific I/O ports.
void hw_mcu_watchdog_feed(void);

#endif


uint16_t hw_mcu_HardwareID(void);

void hw_mcu_SetPowerHold(bool state);
bool hw_mcu_GetPowerHold(void);

void hw_mcu_initialize(void);
void hw_mcu_update(void);


class status_LED_t
{
public:
    void initialize(void);
    void update(void);

    enum  state_t { OFF, ON, FLASH }   ;

    void SetState(state_t state_ ) { state = state_;  };
    void SetFlashRate(uint16_t periodmS);   // period in mS of a complete On/Off flash cycle

private:
    state_t  state;
    uint8_t value;
    hw_stimer timer;
};
extern status_LED_t hw_mcu_heartbeatLED;

#endif