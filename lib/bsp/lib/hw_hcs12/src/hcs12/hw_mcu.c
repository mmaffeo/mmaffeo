
#include "hw_mcu.h"
#include "hw_clock.h"

uint8_t CCR_reg;



void hw_initialize(void)
{
    // Initialize the required registers n the 
    // Port Integration Module (PIM) that are needed for this hardware platform.
    
    				//<<<<<<<Port T>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    PTT = 0x00;     // PTT:  Port T I/O Register
                    
                    // PTIT: Port T Input Register
                    
    DDRT = 0xFC;    // DDRT: Port T Data Direction Register
                    //       DDRT[7:0]  ;0->input
                    //                  ;1->output
                    
                    // RDRT: Port T Reduced Drive Register
                    //       RDRT[7:0]  ;0->full drive strength at output
                    //                  ;1-> associated pin drives at about 1/6 of full strength
                    
                    // PERT: Port T Pull Device Enable Register
                    //       PERT[7:0]  ;0->input pull device is disabled.
                    //                  ;1->input pull device is enabled.
                    
                    // PPST: Port T Polarity Select Register 
                    //       PPST[7:0]  ;0->input pull device is a "pull-up".
                    //                  ;1->input pull device is a "pull-down".
                    
                    
                    //<<<<<<<Port S>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    PTS = 0x00;     // PTS:  Port S I/O Register
                    
                    // PTIS: Port S Input Register
                    
    DDRS = 0xFF;    // DDRS: Port S Data Direction Register
                    //       DDRS[7:0]  ;0->input
                    //                  ;1->output
                    
                    // RDRS: Port S Reduced Drive Register
                    //       RDRS[7:0]  ;0->full drive strength at output
                    //                  ;1-> associated pin drives at about 1/6 of full strength
                    
                    // PERS: Port S Pull Device Enable Register
                    //       PERS[7:0]  ;0->input pull device is disabled.
                    //                  ;1->input pull device is enabled.
                    
                    // PPSS: Port S Polarity Select Register 
                    //       PPSS[7:0]  ;0->input pull device is a "pull-up".
                    //                  ;1->input pull device is a "pull-down".
                    
                    // WOMS: Port S Wired-Or Mode Register
                    //       WOMS[7:0]  ;0->outputs operate as push-pull.
                    //                  ;1->outputs operate as open drain.   
                    
                    
                    //<<<<<<<Port M>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
     PTM  = 0x08;   // PTM:  Port M I/O Register
                    
                    // PTIM: Port M Input Register
                    
     DDRM = 0x28;   // DDRM: Port M Data Direction Register
                    //       DDRM[7:0]  ;0->input
                    //                  ;1->output
                    
                    // RDRM: Port M Reduced Drive Register
                    //       RDRM[7:0]  ;0->full drive strength at output
                    //                  ;1-> associated pin drives at about 1/6 of full strength
                    
                    // PERM: Port M Pull Device Enable Register
                    //       PERM[7:0]  ;0->input pull device is disabled.
                    //                  ;1->input pull device is enabled.
                    
                    // PPSM: Port M Polarity Select Register 
                    //       PPSM[7:0]  ;0->input pull device is a "pull-up".
                    //                  ;1->input pull device is a "pull-down".
                    
                    // WOMM: Port M Wired-Or Mode Register
                    //       WOMM[7:0]  ;0->outputs operate as push-pull.
                    //                  ;1->outputs operate as open drain.     
    
    
    MODRR = 0x38;   // MODRR: Module Routing Register 
                    //        MODRR[7:6] ;reserved
                    //        MODRR[5]   ;SPI1 Routing
                    //                      0  ;MISO1=PP0, MOSI1=PP1, SCK1=PP2, #SS1=PP3
                    //                      1  ;MISO1=PH0, MOSI1=PH1, SCK1=PH2, #SS1=PH3
                    //
                    //        MODRR[4]   ;SPI0 Routing
                    //                      0  ;MISO0=PS4, MOSI0=PS5, SCK0=PS6, #SS0=PS7
                    //                      1  ;MISO0=PM2, MOSI0=PM4, SCK0=PM5, #SS0=PM3
                    // 
                    //        MODRR[3:2] CAN4 routing
                    //                    00  ;RXCAN4=PJ6, TXCAN4=PJ7
                    //                    01  ;RXCAN4=PM4, TXCAN4=PM4
                    //                    10  ;RXCAN4=PM6, TXCAN4=PM7
                    //                    11  ;reserved 
                    //
                    //        MODRR[1:0] CAN0 routing
                    //                    00  ;RXCAN0=PM0, TXCAN0=PM1
                    //                    01  ;RXCAN0=PM2, TXCAN0=PM3
                    //                    10  ;RXCAN0=PM4, TXCAN0=PM5
                    // 		              11  ;reserved    
                    
                    
                    //<<<<<<<Port P>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
     PTP  = 0x00;   // PTP:  Port P I/O Register
                    
                    // PTIP: Port P Input Register
                    
     DDRP = 0xFF;   // DDRP: Port P Data Direction Register
                    //       DDRP[7:0]  ;0->input
                    //                  ;1->output
                    
                    // RDRP: Port P Reduced Drive Register
                    //       RDRP[7:0]  ;0->full drive strength at output
                    //                  ;1-> associated pin drives at about 1/6 of full strength
                    
                    // PERP: Port P Pull Device Enable Register
                    //       PERP[7:0]  ;0->input pull device is disabled.
                    //                  ;1->input pull device is enabled.
                    
                    // PPSP: Port P Polarity Select Register 
                    //       PPSP[7:0]  ;0->input pull device is a "pull-up".
                    //                  ;1->input pull device is a "pull-down".
                    
                    // PIEP: Port P Interrupt Enable Register
                    //       PIEP[7:0]  ;0->interrupt is disabled
                    //                  ;1->interrupt is enabled 
                    
                    // PIFP: Port P Interrupt Flag Register
                    //                  ;write 1 to clear flag  
                    
                    
                    
                    //<<<<<<<Port H>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                    // PTH:  Port H I/O Register
       
                    // PTIH: Port H Input Register
       
                    // DDRH: Port H Data Direction Register
                    //       DDRH[7:0]  ;0->input
                    //                  ;1->output
                    
                    // RDRH: Port H Reduced Drive Register
                    //       RDRH[7:0]  ;0->full drive strength at output
                    //                  ;1-> associated pin drives at about 1/6 of full strength
                    
                    // PERH: Port H Pull Device Enable Register
                    //       PERH[7:0]  ;0->input pull device is disabled.
                    //                  ;1->input pull device is enabled.
                    
                    // PPSH: Port H Polarity Select Register 
                    //       PPSH[7:0]  ;0->input pull device is a "pull-up".
                    //                  ;1->input pull device is a "pull-down".
                    
                    // PIEH: Port H Interrupt Enable Register
                    //       PIEH[7:0]  ;0->interrupt is disabled
                    //                  ;1->interrupt is enabled 
                    
                    // PIFH: Port H Interrupt Flag Register
                    //                  ;write 1 to clear flag  
                    
                    
                    //<<<<<<<Port J>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    PTJ = 0x00;     // PTJ:  Port J I/O Register
       
                    // PTIJ: Port J Input Register
       
    DDRJ = 0xC0;    // DDRJ: Port J Data Direction Register
                    //       DDRJ[7:0]  ;0->input
                    //                  ;1->output
                    
                    // RDRJ: Port J Reduced Drive Register
                    //       RDRJ[7:0]  ;0->full drive strength at output
                    //                  ;1-> associated pin drives at about 1/6 of full strength
                    
                    // PERJ: Port J Pull Device Enable Register
                    //       PERJ[7:0]  ;0->input pull device is disabled.
                    //                  ;1->input pull device is enabled.
                    
                    // PPSJ: Port J Polarity Select Register 
                    //       PPSJ[7:0]  ;0->input pull device is a "pull-up".
                    //                  ;1->input pull device is a "pull-down".
                    
                    // PIEJ: Port J Interrupt Enable Register
                    //       PIEJ[7:0]  ;0->interrupt is disabled
                    //                  ;1->interrupt is enabled 
                    
                    // PIFJ: Port J Interrupt Flag Register
                    //                  ;write 1 to clear flag  


                    //<<<<<<<Port E>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    PORTE = 0x00;   // PORTE:  Port E I/O Register
      
    DDRE = 0x1C;    // DDRE: Port E Data Direction Register
                    //       DDRE[7:0]  ;0->input
                    //                  ;1->output

                    // PEAR: Port E Assignment Register
                    //       << NOACCE:0:PIPOE:NECLK:LSTRE:RDWE:0:0 >>
                    //       NOACCE:  CPU No Access Output Enable
                    //       PIPOE:   Pipe Status Signal Output Enable
                    //       NECLK:   No External E-Clock
                    //       LSTRE:   Low Stobe Enable
                    //       RDWE:    Read/Write Enable
                    
                    
                    //<<<<<<<Port K>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    PORTK = 0x00;   // PORTK:  Port K I/O Register
      
    DDRK = 0x3F;    // DDRK: Port K Data Direction Register
                    //       DDRK[7:0]  ;0->input
                    //                  ;1->output

                  
              
                    //<<<<<<<Port A>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    PORTA = 0x00;   // PORTA:  Port A I/O Register
      
    DDRA = 0xFF;    // DDRA: Port A Data Direction Register
                    //       DDRA[7:0]  ;0->input
                    //                  ;1->output    
                    
                    
                    //<<<<<<<Port B>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    PORTB = 0x00;   // PORTB:  Port B I/O Register
      
    DDRB = 0xFF;    // DDRB: Port B Data Direction Register
                    //       DDRB[7:0]  ;0->input
                    //                  ;1->output  
                    
    hw_clock_initialize();
  
    INTCR_IRQEN = 0;                     /* Disable the IRQ interrupt. IRQ interrupt is enabled after CPU reset by default. */
    __EI();                              /* Enable interrupts */  
    
    
}




////////////////////////////////////////////////////////////////////////////////////////////////////
// Green status LED functionality...
status_LED_t hw_mcu_heartbeatLED;   

void hw_mcu_LED_PutVal(bool value)
{
    if (value)  PORTE |=  0x04;	    //   set port bit
    else		PORTE &= ~0x04;	    // clear port bit
}

void status_LED_t::initialize(void)
{
    timer.set_rate(1000/10/2);
    state = FLASH;
}

void status_LED_t::update(void)
{   
    timer.update();
    switch (state)
    {
        case OFF:    value = 0;    break;
        case ON:	 value = 1;    break;
        case FLASH:
        default:
            if ( timer.expired() )
            {
                value = !value;
                timer.reset();
            }
            break;            
    }
    hw_mcu_LED_PutVal(value);
}

void status_LED_t::SetFlashRate(uint16_t periodmS)
{
    if (periodmS > 2500)
        periodmS = 2500;
    
    timer.set_rate((uint8_t) (periodmS/10/2) );    
}





////////////////////////////////////////////////////////////////////////////////////////////////////
// Internal Computer Operating Properly (COP) watchdog.
static void COP_initialize(void)
{
    // 
    // COPCTL   (WCOP:RSBCK:0:0: 0:CR2:CR1:CR0)
    //  WCOP=0  ; Normal COP operation
    //  RSBCK=1 ; Stops the COP and RTI counters whenever the part is in active BDM mode
    // The fields CR2:CR1:CR0 define the timeout as follows...
    //      000 ; watchdog disabled
    //      001 ; 2^14 OSCCLK cycles  (if OSCCLK==4MHz, timeout~= 4.01mS)
    //      010 ; 2^16 OSCCLK cycles  (if OSCCLK==4MHz, timeout~=16.38mS)
    //      011 ; 2^18 OSCCLK cycles  (if OSCCLK==4MHz, timeout~=65.54mS)
    //      100 ; 2^20 OSCCLK cycles  (if OSCCLK==4MHz, timeout~=262.1mS)
    //      101 ; 2^22 OSCCLK cycles  (if OSCCLK==4MHz, timeout~=1.049 S)
    //      110 ; 2^23 OSCCLK cycles  (if OSCCLK==4MHz, timeout~=2.097 S)
    //      111 ; 2^24 OSCCLK cycles  (if OSCCLK==4MHz, timeout~=4.194 S)

    COPCTL = 0x45;
}


static void COP_feed(void)
{
    ARMCOP = 0x55;
    ARMCOP = 0xAA;
}

void hw_mcu_watchdog_feed(void) {COP_feed();}
 
 
 
////////////////////////////////////////////////////////////////////////////////////////////////////
// hardware ID
uint16_t hw_mcu_HardwareID(void)
{
    return PTIH;    
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Power hold circuitry
bool p_hold_state;
void hw_mcu_SetPowerHold(bool state)
{    
    p_hold_state = state;
    
    if (state)  PORTE |=  0x08;	   // set   "D" bit    
    else        PORTE &= ~0x08;	   // clear "D" bit
    
    PORTE |=  0x10;
    PORTE &= ~0x10; 
}

bool hw_mcu_GetPowerHold(void)
{
    return p_hold_state;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Analog input muulitplexers
void hw_mcu_MuxSel_PutVal(uint8_t value)
{
    PTJ &= 0x3F;	       // clear the mux bits
    PTJ |= value << 6;     // set the new mux bits.      
}				   


/////////////////////////////////////////////////////////////////////////////////////////////////
// parrallel to serial latches
void hw_mcu_din_load_PutVal(bool value)
{
    if (value)  PTM   |=  0x08;     //   set port bit
    else 		PTM   &= ~0x08;     // clear port bit  
}


void hw_mcu_initialize(void)
{
    hw_mcu_heartbeatLED.initialize();
    
    COP_initialize();   
}

void hw_mcu_update(void)
{
     hw_mcu_heartbeatLED.update(); 
     
     COP_feed();   
}