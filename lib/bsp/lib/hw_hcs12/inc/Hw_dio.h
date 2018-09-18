

#ifndef hw_dio_h
#define hw_dio_h

#include "hw_mcu.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// digital inputs

typedef enum
{
    // serial latch 1
    HWC_DIN_NU1, HWC_DIN_NU2, HWC_DIN18, HWC_DIN17,
    HWC_DIN16,   HWC_DIN15,   HWC_DIN14, HWC_DIN13,

  // serial latch 2
  HWC_DIN12,   HWC_DIN11,   HWC_DIN10, HWC_DIN09,
  HWC_DIN08,   HWC_DIN07,   HWC_DIN06, HWC_DIN05,

  // serial latch 3
  HWC_DIN_LC_HSD8_DFBK, HWC_DIN_LC_HSD7_DFBK, HWC_DIN_LC_HSD6_DFBK, HWC_DIN_LC_HSD5_DFBK,
  HWC_DIN_LC_HSD4_DFBK, HWC_DIN_LC_HSD3_DFBK, HWC_DIN_LC_HSD2_DFBK, HWC_DIN_LC_HSD1_DFBK,

    HWC_DIN_QTY
} hw_din_ch_t;

bool     hw_din_GetValue (hw_din_ch_t ch);


// "Banked" digital input interface...
// If HWC_DIN_QTY=="n" then the banks are grouped as shown below.
//    bank==0:  CH16:CH15:CH14:CH13:CH12:CH11:CH10:CH09:CH08:CH07:CH06:CH05:CH04:CH03:CH02:CH01
//    bank==1:  CH32:CH31:CH30:CH29:CH28:CH27:CH26:CH25:CH24:CH23:CH22:CH21:CH20:CH19:CH18:CH17
//    ...  :   ...
//    bank==m:     0:   0:   0:   0:       ...      CH_n: CHn-1:       ...
//    bank >m:     0:   0:   0:   0:   0:   0:   0:   0:   0:   0:   0:   0:   0:   0:   0:   0

#define HW_DIN_BANK_QTY 2
uint16_t hw_din_GetBank(uint16_t bank);


///////////////////////////////////////////////////////////////////////////////////////////////////
// digital outputs

typedef enum
{

    // >>>>>>>>BANK0*******************************************************************************-
    // PORT A
    HWC_DOUT_HC_LSD1_CMD, HWC_DOUT_HC_LSD2_CMD, HWC_DOUT_HC_LSD3_CMD, HWC_DOUT_HC_LSD4_CMD,
    HWC_DOUT_HC_LSD5_CMD, HWC_DOUT_HC_LSD6_CMD, HWC_DOUT_NU1,         HWC_DOUT_NU2,
    // PORT B
    HWC_DOUT_LC_HSD1_CMD,  HWC_DOUT_LC_HSD3_CMD,  HWC_DOUT_LC_HSD5_CMD,  HWC_DOUT_LC_HSD7_CMD,
    HWC_DOUT_DIN01_ENABLE, HWC_DOUT_DIN02_ENABLE, HWC_DOUT_DIN03_ENABLE, HWC_DOUT_DIN04_ENABLE,

    // >>>>>>>>BANK1*******************************************************************************-
    // PP0, PP2, PP4, PP6
    HWC_DOUT_LC_HSD2_CMD,   HWC_DOUT_LC_HSD4_CMD,  HWC_DOUT_LC_HSD6_CMD,  HWC_DOUT_LC_HSD8_CMD,
    HWC_DOUT_CAN_TERM_OFF1, HWC_DOUT_CAN_TERM_OFF2,
    HWC_DOUT_WC_ON1,        HWC_DOUT_WC_ON1_AUTO,
    HWC_DOUT_WC_ON2,        HWC_DOUT_WC_ON2_AUTO,
    HWC_DOUT_WC_ON3,        HWC_DOUT_WC_ON3_AUTO,
    HWC_DOUT_WC_ON4,        HWC_DOUT_WC_ON4_AUTO,
    HWC_DOUT_WC_ON5,        HWC_DOUT_WC_ON5_AUTO,

    // >>>>>>>>BANK2*******************************************************************************-
    HWC_DOUT_WC_ON6,        HWC_DOUT_WC_ON6_AUTO,  HWC_DOUT_WC_ON7,       HWC_DOUT_WC_ON7_AUTO,
    HWC_DOUT_WC_ON8,        HWC_DOUT_WC_ON8_AUTO,
    HWC_DOUT_WC_CONFIG1,    HWC_DOUT_WC_CONFIG1_AUTO,
    HWC_DOUT_WC_CONFIG2,    HWC_DOUT_WC_CONFIG2_AUTO,
    HWC_DOUT_WC_CONFIG3,    HWC_DOUT_WC_CONFIG3_AUTO,
    HWC_DOUT_WC_CONFIG4,    HWC_DOUT_WC_CONFIG4_AUTO,


    HWC_DOUT_QTY
} hw_dout_ch_t;



bool hw_dout_GetValue(hw_dout_ch_t ch            );
void hw_dout_SetValue(hw_dout_ch_t ch, bool value);


// "Banked" digital output interface...
// If HWC_DOUTQTY=="n" then the banks are grouped as shown below.
//    bank==0:  CH16:CH15:CH14:CH13:CH12:CH11:CH10:CH09:CH08:CH07:CH06:CH05:CH04:CH03:CH02:CH01
//    bank==1:  CH32:CH31:CH30:CH29:CH28:CH27:CH26:CH25:CH24:CH23:CH22:CH21:CH20:CH19:CH18:CH17
//    ...  :   ...
//    bank==m:     0:   0:   0:   0:       ...      CH_n: CHn-1:       ...
//    bank >m:     0:   0:   0:   0:   0:   0:   0:   0:   0:   0:   0:   0:   0:   0:   0:   0

#define HW_DOUT_BANK_QTY 3
uint16_t hw_dout_GetBank(uint8_t bank);
void     hw_dout_SetBank(uint8_t bank, uint16_t data);



/////////////////////////////////////////////////////////////////////////////////////////////////////
// hw_io diver interface, the user of the "hw_io" modules should not need to access this information.
void hw_dio_initialize(void);
void hw_dio_update    (void);

#ifndef HCS12_BSP_EMU
void hw_dio_wc_activate  (void);
void hw_dio_wc_deactivate(void);
#endif /* HCS12_BSP_EMU */


#endif