

#include "hw_can.h"
#include "hw_config.h"
#include "hw_reset.h"
#include "hw_fin.h"
#include "hw_adc.h"
#include "hw_clock.h"
#include "hw_vectors.h"
#include "hw_pwm_ect.h"



#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void nu_isr(void)  {}
#pragma CODE_SEG DEFAULT    /* Change code section to DEFAULT. */


const tIsrFunc hw_pvector_table[] 
#ifndef BB_COMPILE
@0x7F80 
#endif
= 
{   /* Interrupt table */
    nu_isr,                     // 63 - 
    nu_isr,                     // 62 - 
    nu_isr,                     // 61 - 
    nu_isr,                     // 60 - 
    nu_isr,                     // 59 -
    nu_isr,                     // 58 - 
    nu_isr,                     // 57 - PWM emergency shutdown
    nu_isr,                     // 56 - Port P

    #ifdef HWC_CAN4
    CAN4_Tx_Vector,             // 55 - CAN4 transmit
    CAN4_Rx_Vector,             // 54 - CAN4 receive
    CAN4_Err_Vector,            // 53 - CAN4 errors
    CAN4_Wup_Vector,            // 52 - CAN4 wakeup
    #else HWC_CAN4
    nu_isr,                     // 55 - CAN4 transmit
    nu_isr,                     // 54 - CAN4 receive
    nu_isr,                     // 53 - CAN4 errors
    nu_isr,                     // 52 - CAN4 wakeup
    #endif

    nu_isr,                     // 51 - 
    nu_isr,                     // 50 - 
    nu_isr,                     // 49 - 
    nu_isr,                     // 48 - 
    nu_isr,                     // 47 - BF general
    nu_isr,                     // 46 - BF synchronization
    nu_isr,                     // 45 - BF receive
    nu_isr,                     // 44 - BF Rx FIFO not empty
    nu_isr,                     // 43 - CAN1 transmit
    nu_isr,                     // 42 - CAN1 receive
    nu_isr,                     // 41 - CAN1 errors
    nu_isr,                     // 40 - CAN1 wakeup
    CAN0_Tx_Vector,             // 39 - CAN0 transmit
    CAN0_Rx_Vector,             // 38 - CAN0 receive
    CAN0_Err_Vector,            // 37 - CAN0 errors
    CAN0_Wup_Vector,            // 36 - CAN0 wakeup
    nu_isr,                     // 35 - Flash
    nu_isr,                     // 34 - EEPROM
    nu_isr,                     // 33 -
    nu_isr,                     // 32 - SPI1
    nu_isr,                     // 31 - IIC bus
    nu_isr,                     // 30 - BDLC
    nu_isr,                     // 29 - CRG self clock mode
    nu_isr,                 	// 28 - CRG PLL lock
    nu_isr,                     // 27 - Pulse Accumulator B overflow
    nu_isr,		                // 26 - Modulus Down Counter underflow
    nu_isr,                     // 25 - Port H
    nu_isr,						// 24 - Port J
    nu_isr,					    // 23 - ATD1
    nu_isr,					    // 22 - ATD0
    nu_isr,                     // 21 - SCI1
    nu_isr,                     // 20 - SCI0
    nu_isr,						// 19 - SPI0
    nu_isr,                 	// 18 - Pulse Accumulator input edge
    nu_isr,                 	// 17 - Pulse Accumulator A overflow
    hw_clock_TCNT_overflow,		// 16 - ECT TOF
    ECT7_isr,                 	// 15 - ECT7
    nu_isr,                 	// 14 - ECT6
    nu_isr,                 	// 13 - ECT5
    nu_isr,                 	// 12 - ECT4
    nu_isr,                     // 11 - ECT3
    nu_isr,                     // 10 - ECT2
    nu_isr,		                //  9 - ECT1
    hw_fin0_OnCapture,			//  8 - ECT0
    nu_isr,                     //  7 - RTI
    nu_isr,                     //  6 - IRQ
    nu_isr,                     //  5 - XIRQ   
    nu_isr,                     //  4 - SWI     
    hw_PowerOn_reset,           //  3 - unimplemented intruction
    hw_COP_reset,               //  2 - COP reset
    hw_PowerOn_reset,           //  1 - Clock monitor fail
    hw_PowerOn_reset            //  0 - Power-On Reset 
};

   
