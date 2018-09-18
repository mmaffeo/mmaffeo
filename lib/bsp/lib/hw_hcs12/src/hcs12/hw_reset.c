/*
    This module provides the CPU related resets and  setups (oscillator, memory map).
*/


#include "hw_reset.h"
#include "hw_mcu.h"    // MCU register definitions
#include "hw_config.h"

#ifdef __cplusplus
extern "C"
#endif
void _Startup(void);   // "C" startup function declared in file Start12.c

uint8_t  hw_can_term_state  @0x3FFB;
uint16_t pvector_base       @0x3FFC;
uint8_t  bb_smode           @0x3FFE;
uint8_t  ap_smode           @0x3FFF;    // application software dependent (zero is the default).

uint8_t bservProg_protocolID = 0x01; // protocol id
uint8_t bservProg_options = 0x4A; // protocol options
uint8_t bservProg_customerID = 0x01; // customer id
uint8_t bservProg_maxDataSize = 0x20; // max data size



static void force_COP_reset(void)
{
    COPCTL = 0x01;   // make sure COP is enabled
    ARMCOP = 0x00;   // trigger a COP reset by writing a value different than 0x55 or 0xAA to ARMCOP.
}

void hw_reset_force(uint8_t bb_smode_,
                    uint8_t ap_smode_)
{
    bb_smode = bb_smode_;
    ap_smode = ap_smode_;

    force_COP_reset();
}


uint8_t *stkp;

// See Metrowerks Technical Note TN103, for a description as to how the linker provides this segment data/
extern uint8_t __SEG_START_SSTACK[]; // start of stack
extern uint8_t __SEG_END_SSTACK[];   // end of stack
extern char __SEG_SIZE_SSTACK[];     // size of stack

uint16_t hw_reset_max_stack(void)
{
    uint8_t *p= __SEG_START_SSTACK;

    while (*p==0xAA)
        ++p;

    return (uint16_t)(__SEG_END_SSTACK-p);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//  MEMSIZ0 = << REG_SW0:0:EEP_SW1:EEP_SW0:0:RAM_SW[210] >>
//
const uint16_t RAM_TOP[8]=
{       //   size RAM_SW[210]  address range before INITRM is set
    0x0FFF,   //    2k     000  0x0800 -> 0x0FFF
    0x0FFF,   //    4k         001    0x0000 -> 0x0FFF
    0x1FFF,   //    6k     010  0x0800 -> 0x1FFF
    0x1FFF,   //    8k         011    0x0000 -> 0x1FFF
    0x3FFF,   //   10k     100  0x1800 -> 0x3FFF
    0x3FFF,   //   12k         101    0x1000 -> 0x3FFF
    0x3FFF,   //   14k     110  0x0800 -> 0x3FFF
    0x3FFF    //   16k         111    0x0000 -> 0x3FFF
};


#define hw_can_term_state_addr_before_INITRM (uint8_t  *)( RAM_TOP[MEMSIZ0 & 0x07] - 4)
#define pvector_base_addr_before_INITRM      (uint16_t *)( RAM_TOP[MEMSIZ0 & 0x07] - 3)
#define bb_smode_addr_before_INITRM          (uint8_t  *)( RAM_TOP[MEMSIZ0 & 0x07] - 1)
#define ap_smode_addr_before_INITRM          (uint8_t  *)( RAM_TOP[MEMSIZ0 & 0x07]    )


#pragma CODE_SEG __NEAR_SEG NON_BANKED

// disable the "Create Sub-Function with Common Code" optimization since
//    the stack pointer has not been initialized yet
#pragma OPTION ADD sub_function_opt_disable "-Onf"


__interrupt void hw_PowerOn_reset(void)
{
    *(bb_smode_addr_before_INITRM) = (uint8_t) BB_SMODE_NA;

    #ifdef BB_COMPILE
    *(hw_can_term_state_addr_before_INITRM) = (uint8_t) 0;
    #endif

    asm jmp hw_COP_reset;
}

__interrupt void hw_COP_reset(void)
{
    if (*bb_smode_addr_before_INITRM == (uint8_t) BB_SMODE_JUMP_TO_AP)
    {
        *bb_smode_addr_before_INITRM     = (uint8_t) BB_SMODE_NA;
        *pvector_base_addr_before_INITRM = AP_VECTOR_BASE ;

        asm ldx AP_VECTOR_BASE;
        asm jmp [126,X];
    }
    else

    {
        #ifndef NO_FPROT
                        // Protect the "bootblock" flash memory area...
        FPROT = 0xDF;               // Flash Protection Register (FPROT)
                                    //   << FPOPEN:NV6:FPHDIS:FPHS1:FPHS0:FPLDIS:FPLS1:FPLS0 >>
        #endif


        INITRM=0x39;                // Initialization of Internal RAM postion Register (INITRM)
                                    //  << RAM15:RAM14:RAM13:RAM12:RAM11:0:0:RAMHAL >>
                                    // RAM15:RAM11 = 0:0:1:1:1
                                    // RAMHAL = 1
                                    //
                                    // RAM high aligned at address 0x3fff

        // fill stack with the pattern 0xAA;
        for (stkp =__SEG_START_SSTACK;
             stkp <__SEG_END_SSTACK  ;
             ++stkp                        )
            *stkp = 0xAA;


        #ifdef BB_COMPILE
        ap_smode = 0;
        #endif

        pvector_base = AP_VECTOR_BASE;

        INITEE=0x09;                // Initialization of Internal EEPROM Position Register (INITEE)
                                    //  << EE15:EE14:EE13:EE12:EE11:0:0:EEON >>
                                    // EE15:EE11 = 0:0:0:0:1
                                    // EEON = 1
                                    //
                                    // EEPROM is enabled with a based address of 0x800

        // initialize the clock frequecny / PLL
        CLKSEL=0x08;          // CRG Clock Select Register (CLKSEL)
                                    //  << PLLSEL:PSTP:SYSWAI:ROAWAI:PLLWAI:CWAI:RTIWAI:COPWAI >>
                                    // PLLSEL=0 ;System clocks are derived from OSCCLK
                                    // PSTP=0   ;Oscillator is disabled in Stop Mode
                                    // SYSWAI=0 ;In Wait Mode the system clocks continue to run.
                                    // ROAWAI=0 ;Normal oscillator amplitude in Wait Mode.
                                    // PLLWAI=1 ;PLL stops in Wait mode.
                                    // CWAI=0   ;Core clock keeps running in Wait Mode.
                                    // RTIWAI=0 ;RTI keeps running in Wait Mode
                                    // COPWAI=0 ;COP keeps running in Wait Mode

        PLLCTL_PLLON = 0;           // Disable the PLL

        SYNR  = SYNR_init_value;    // initialize the "CRG Synthesizer Register"
        REFDV = REFDV_init_value;   // initialize the "CRG Reference Divider Register"

        PLLCTL = 0xC0;              // CRG PLL Control Register (PLLCTL)
                                    //  << CME:PLLON:AUTO:ACQ:0:PRE:PCE:SCME >>
                                    // CME=1  ;clock monitor is enabled
                                    // PLLON=1;enable the PLL

        while(!CRGFLG_LOCK);        // wait until the PLL has "locked" into the desired frequency.

        CLKSEL_PLLSEL = 1;          // Select clock source from the PLL

        asm jmp _Startup;           // Jump to the C startup code
    }
}

#pragma OPTION DEL sub_function_opt_disable
#pragma CODE_SEG DEFAULT





