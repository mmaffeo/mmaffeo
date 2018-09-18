
#ifndef hw_clock_h
#define hw_clock_h


#include "stdint.h"


    void hw_clock_initialize(void);

uint32_t hw_clock                         (void);     // free running timer (rate implementation specific)
uint32_t hw_clock_convert_uS_to_clockticks(uint32_t   XuS);
uint32_t hw_clock_convert_clockticks_to_uS(uint32_t ticks);


uint16_t hw_clock_S (void);  // returns the value from a free running counter (1      second per count)
               // overflows at 1*(2^16-1) = 65535 seconds -> ~1092.25minutes -> ~18.2hours

uint16_t hw_clock_mS(void);  // returns the value from a free running counter (1 millisecond per count)
                             // overflows at (1e-3)*(2^16-1) = 65.535 seconds

uint16_t hw_clock_uS(void);  // returns the value from a free running counter (1 microsecond per count)
                             // overflows at (1e-6)*(2^16-1) = 0.065535 seconds -> ~65.5mS



#ifndef HCS12_BSP_EMU

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// implementation details which may be used by other "hw" modules...
extern volatile uint16_t TCNT_overflows;

#pragma CODE_SEG __NEAR_SEG NON_BANKED // Interrupt section for this module. Placement will be in NON_BANKED area.
__interrupt void hw_clock_TCNT_overflow   (void);
#pragma CODE_SEG DEFAULT


#define initial_TSCR2_PR 0x03


// Notes concerning accuracy of this implementation...
//
//     The microprocessor is set up to keep track of time with a 48-bit free running timer
// (lets call it "frt") which increments once ever 0.32uS (25MHz base clock with a
// divide by 8 pre-scaler). The least significant 32-bits of this free running timer can be
// accessed by the application via a call to "hw_clock()".
//
// "hw_clock_S ()" is implemented as the least significant 16 bits of the product frt*K_S.
// "hw_clock_mS()" is implemented as the least significant 16 bits of the product frt*K_mS.
// "hw_clock_uS()" is implemented as the least significant 16 bits of the product frt*K_uS.
//
// Where,
//   K_S  = 0.32e-6;
//   K_mS = 0.32e-3;
//   K_uS = 0.32;
//
// Since we are using fixed point arithmetic the software is approximating these constants as follows...
//   K_S  = 687/2^31 = 0.3199093e-6
//   K_mS = 671/2^21 = 0.3199577e-3
//   K_uS = 655/2^11 = 0.3198242
//
// Because of all this...
// Calls to "hw_clock()" will always return the most accurate time known by the microcontroller. Calls to "hw_clock_S()", "hw_clock_mS()" and "hw_clock_uS()" will have some error introduced as follows...
//   hw_clock_uS(): when 10,000uS elapses it will return 9994uS.
//   hw_closk_mS(): when 10,000mS elapses it will return 9998mS.
//   hw_clock_S (): when 10,000 S elapses it will return 9997 S.

#endif /* HCS12_BSP_EMU */

#endif
