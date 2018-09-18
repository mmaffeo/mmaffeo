
#include "hw_dio.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
// digital inputs...
////////////////////////////////////////////////////////////////////////////////////////////////////
uint16_t hw_din_data[HW_DIN_BANK_QTY];

bool hw_din_GetValue(hw_din_ch_t ch)
{
    uint8_t bank = (uint8_t)  ch >> 4;
    uint16_t mask = 0x01u << ((uint8_t)ch  & 0x0F);

    return hw_din_data[bank] & mask ? true : false ;
}

uint16_t hw_din_GetBank(uint16_t bank) { return hw_din_data[bank]; }

////////////////////////////////////////////////////////////////////////////////////////////////////
// digital outputs
////////////////////////////////////////////////////////////////////////////////////////////////////
uint16_t hw_dout_data[HW_DOUT_BANK_QTY];
extern uint8_t hw_can_term_state;

void hw_dout_SetValue(hw_dout_ch_t ch, bool value)
{
    uint8_t bank = (uint8_t) ch >> 4;
    uint16_t mask = 0x01 << ((uint8_t)ch  & 0x0F);

    if (value)
        hw_dout_data[bank] |= mask;
    else
        hw_dout_data[bank] &= ~mask;
}

bool hw_dout_GetValue(hw_dout_ch_t ch )
{
  uint8_t bank = (uint8_t) ch >> 4;
    uint16_t mask = 0x01 << ((uint8_t)ch  & 0x0F);

    return hw_dout_data[bank]&mask ? true: false;
}

uint16_t hw_dout_GetBank(uint8_t bank)                { return hw_dout_data[bank];       }
void     hw_dout_SetBank(uint8_t bank, uint16_t data) {        hw_dout_data[bank] = data;}

static void hw_dout_SetOutput(hw_dout_ch_t ch, bool value)
{
    switch(ch)
    {
        case HWC_DOUT_HC_LSD1_CMD:  if (value) PORTA |= 0x01; else  PORTA &= ~0x01; break;
        case HWC_DOUT_HC_LSD2_CMD:  if (value) PORTA |= 0x02; else  PORTA &= ~0x02; break;
        case HWC_DOUT_HC_LSD3_CMD:  if (value) PORTA |= 0x04; else  PORTA &= ~0x04; break;
        case HWC_DOUT_HC_LSD4_CMD:  if (value) PORTA |= 0x08; else  PORTA &= ~0x08; break;
        case HWC_DOUT_HC_LSD5_CMD:  if (value) PORTA |= 0x10; else  PORTA &= ~0x10; break;
        case HWC_DOUT_HC_LSD6_CMD:  if (value) PORTA |= 0x20; else  PORTA &= ~0x20; break;

        case HWC_DOUT_LC_HSD1_CMD:  if (value) PORTB |= 0x01; else  PORTB &= ~0x01; break;
        case HWC_DOUT_LC_HSD3_CMD:  if (value) PORTB |= 0x02; else  PORTB &= ~0x02; break;
        case HWC_DOUT_LC_HSD5_CMD:  if (value) PORTB |= 0x04; else  PORTB &= ~0x04; break;
        case HWC_DOUT_LC_HSD7_CMD:  if (value) PORTB |= 0x08; else  PORTB &= ~0x08; break;
        case HWC_DOUT_DIN01_ENABLE: if (value) PORTB |= 0x10; else  PORTB &= ~0x10; break;
        case HWC_DOUT_DIN02_ENABLE: if (value) PORTB |= 0x20; else  PORTB &= ~0x20; break;
        case HWC_DOUT_DIN03_ENABLE: if (value) PORTB |= 0x40; else  PORTB &= ~0x40; break;
        case HWC_DOUT_DIN04_ENABLE: if (value) PORTB |= 0x80; else  PORTB &= ~0x80; break;

        case HWC_DOUT_LC_HSD2_CMD:  if (value) PTP   |= 0x01; else  PTP   &= ~0x01; break;
        case HWC_DOUT_LC_HSD4_CMD:  if (value) PTP   |= 0x04; else  PTP   &= ~0x04; break;
        case HWC_DOUT_LC_HSD6_CMD:  if (value) PTP   |= 0x10; else  PTP   &= ~0x10; break;
        case HWC_DOUT_LC_HSD8_CMD:  if (value) PTP   |= 0x40; else  PTP   &= ~0x40; break;

        case HWC_DOUT_WC_CONFIG1:   if (value) PORTK |= 0x01; else  PORTK &= ~0x01; break;
        case HWC_DOUT_WC_CONFIG2:   if (value) PORTK |= 0x02; else  PORTK &= ~0x02; break;
        case HWC_DOUT_WC_CONFIG3:   if (value) PORTK |= 0x04; else  PORTK &= ~0x04; break;
        case HWC_DOUT_WC_CONFIG4:   if (value) PORTK |= 0x08; else  PORTK &= ~0x08; break;
        case HWC_DOUT_CAN_TERM_OFF1:if (value) PORTK |= 0x10; else  PORTK &= ~0x10; break;
        case HWC_DOUT_CAN_TERM_OFF2:if (value) PORTK |= 0x20; else  PORTK &= ~0x20; break;

        case HWC_DOUT_WC_ON1:       if (value) PTS   |= 0x01; else  PTS   &= ~0x01; break;
        case HWC_DOUT_WC_ON2:       if (value) PTS   |= 0x02; else  PTS   &= ~0x02; break;
        case HWC_DOUT_WC_ON3:       if (value) PTS   |= 0x04; else  PTS   &= ~0x04; break;
        case HWC_DOUT_WC_ON4:       if (value) PTS   |= 0x08; else  PTS   &= ~0x08; break;
        case HWC_DOUT_WC_ON5:       if (value) PTS   |= 0x10; else  PTS   &= ~0x10; break;
        case HWC_DOUT_WC_ON6:       if (value) PTS   |= 0x20; else  PTS   &= ~0x20; break;
        case HWC_DOUT_WC_ON7:       if (value) PTS   |= 0x40; else  PTS   &= ~0x40; break;
        case HWC_DOUT_WC_ON8:       if (value) PTS   |= 0x80; else  PTS   &= ~0x80; break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// shared digital input/output functions
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "hw_mcu.h"
#include "hw_spi.h"
#include "hw_clock.h"

static hw_spi SPI0;



void hw_dio_initialize(void)
{
    SPI0.initialize((hw_spi::reg_t *) &SPI0CR1 );

    hw_dout_SetValue(HWC_DOUT_WC_ON1_AUTO,     1);
    hw_dout_SetValue(HWC_DOUT_WC_ON2_AUTO,     1);
    hw_dout_SetValue(HWC_DOUT_WC_ON3_AUTO,     1);
    hw_dout_SetValue(HWC_DOUT_WC_ON4_AUTO,     1);
    hw_dout_SetValue(HWC_DOUT_WC_ON5_AUTO,     1);
    hw_dout_SetValue(HWC_DOUT_WC_ON6_AUTO,     1);
    hw_dout_SetValue(HWC_DOUT_WC_ON7_AUTO,     1);
    hw_dout_SetValue(HWC_DOUT_WC_ON8_AUTO,     1);
    hw_dout_SetValue(HWC_DOUT_WC_CONFIG1_AUTO, 1);
    hw_dout_SetValue(HWC_DOUT_WC_CONFIG2_AUTO, 1);
    hw_dout_SetValue(HWC_DOUT_WC_CONFIG3_AUTO, 1);
    hw_dout_SetValue(HWC_DOUT_WC_CONFIG4_AUTO, 1);

    hw_dout_SetValue(HWC_DOUT_CAN_TERM_OFF1, hw_can_term_state & 0x01);
    hw_dout_SetValue(HWC_DOUT_CAN_TERM_OFF2, hw_can_term_state & 0x02);

    hw_dio_update();
}



void hw_dio_update    (void)
{
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Read digital input ports...

    uint16_t start_clock_uS;
    hw_mcu_din_load_PutVal(1);    // tansfer input port data into shift registers...

    uint8_t latch[3];

    SPI0.TxChar(0);   // dummy write to generate read pulses
    start_clock_uS = hw_clock_uS();
    while (!SPI0.RxDataAvailiable() && ((hw_clock_uS()-start_clock_uS)<1000) );
    latch[0] = SPI0.RxChar();

    SPI0.TxChar(0);   // dummy write to generate read pulses
    start_clock_uS = hw_clock_uS();
    while (!SPI0.RxDataAvailiable() && ((hw_clock_uS()-start_clock_uS)<1000) );
    latch[1] = SPI0.RxChar();

    SPI0.TxChar(0);   // dummy write to generate read pulses
    start_clock_uS = hw_clock_uS();
    while (!SPI0.RxDataAvailiable() && ((hw_clock_uS()-start_clock_uS)<1000) );
    latch[2] = SPI0.RxChar();


    hw_mcu_din_load_PutVal(0);   // transfer output shift register into output latches...

    hw_din_data[0] = latch[0] + 0x100u * latch[1];
    hw_din_data[1] = latch[2];




    // update outputs
    if ( hw_dout_GetValue(HWC_DOUT_CAN_TERM_OFF1) ) hw_can_term_state |= 0x01; else  hw_can_term_state &= ~0x01;
    if ( hw_dout_GetValue(HWC_DOUT_CAN_TERM_OFF2) ) hw_can_term_state |= 0x02; else  hw_can_term_state &= ~0x02;

    for (int i=0; i<HWC_DOUT_QTY; ++i)
    {
        hw_dout_SetOutput(i,hw_dout_GetValue(i) );
    }
}



static void hw_dio_wc_activate(hw_dout_ch_t auto_ch, hw_dout_ch_t dout_ch)
{//// if auto mode turn wetting current output on...
    if (hw_dout_GetValue(auto_ch))
    {
        hw_dout_SetOutput(dout_ch, 1);
        hw_dout_SetValue (dout_ch, 0);
    }
}

void hw_dio_wc_activate(void)
{
    hw_dio_wc_activate(HWC_DOUT_WC_ON1_AUTO,     HWC_DOUT_WC_ON1    );
    hw_dio_wc_activate(HWC_DOUT_WC_ON2_AUTO,     HWC_DOUT_WC_ON2    );
    hw_dio_wc_activate(HWC_DOUT_WC_ON3_AUTO,     HWC_DOUT_WC_ON3    );
    hw_dio_wc_activate(HWC_DOUT_WC_ON4_AUTO,     HWC_DOUT_WC_ON4    );
    hw_dio_wc_activate(HWC_DOUT_WC_ON5_AUTO,     HWC_DOUT_WC_ON5    );
    hw_dio_wc_activate(HWC_DOUT_WC_ON6_AUTO,     HWC_DOUT_WC_ON6    );
    hw_dio_wc_activate(HWC_DOUT_WC_ON7_AUTO,     HWC_DOUT_WC_ON7    );
    hw_dio_wc_activate(HWC_DOUT_WC_ON8_AUTO,     HWC_DOUT_WC_ON8    );
    hw_dio_wc_activate(HWC_DOUT_WC_CONFIG1_AUTO, HWC_DOUT_WC_CONFIG1);
    hw_dio_wc_activate(HWC_DOUT_WC_CONFIG2_AUTO, HWC_DOUT_WC_CONFIG2);
    hw_dio_wc_activate(HWC_DOUT_WC_CONFIG3_AUTO, HWC_DOUT_WC_CONFIG3);
    hw_dio_wc_activate(HWC_DOUT_WC_CONFIG4_AUTO, HWC_DOUT_WC_CONFIG4);
}


void hw_dio_wc_deactivate(void)
{
    // if auto mode turn wetting current output off...
    if ( hw_dout_GetValue(HWC_DOUT_WC_ON1_AUTO    )) hw_dout_SetOutput(HWC_DOUT_WC_ON1    ,0);
    if ( hw_dout_GetValue(HWC_DOUT_WC_ON2_AUTO    )) hw_dout_SetOutput(HWC_DOUT_WC_ON2    ,0);
    if ( hw_dout_GetValue(HWC_DOUT_WC_ON3_AUTO    )) hw_dout_SetOutput(HWC_DOUT_WC_ON3    ,0);
    if ( hw_dout_GetValue(HWC_DOUT_WC_ON4_AUTO    )) hw_dout_SetOutput(HWC_DOUT_WC_ON4    ,0);
    if ( hw_dout_GetValue(HWC_DOUT_WC_ON5_AUTO    )) hw_dout_SetOutput(HWC_DOUT_WC_ON5    ,0);
    if ( hw_dout_GetValue(HWC_DOUT_WC_ON6_AUTO    )) hw_dout_SetOutput(HWC_DOUT_WC_ON6    ,0);
    if ( hw_dout_GetValue(HWC_DOUT_WC_ON7_AUTO    )) hw_dout_SetOutput(HWC_DOUT_WC_ON7    ,0);
    if ( hw_dout_GetValue(HWC_DOUT_WC_ON8_AUTO    )) hw_dout_SetOutput(HWC_DOUT_WC_ON8    ,0);
    if ( hw_dout_GetValue(HWC_DOUT_WC_CONFIG1_AUTO)) hw_dout_SetOutput(HWC_DOUT_WC_CONFIG1,0);
    if ( hw_dout_GetValue(HWC_DOUT_WC_CONFIG2_AUTO)) hw_dout_SetOutput(HWC_DOUT_WC_CONFIG2,0);
    if ( hw_dout_GetValue(HWC_DOUT_WC_CONFIG3_AUTO)) hw_dout_SetOutput(HWC_DOUT_WC_CONFIG3,0);
    if ( hw_dout_GetValue(HWC_DOUT_WC_CONFIG4_AUTO)) hw_dout_SetOutput(HWC_DOUT_WC_CONFIG4,0);
}


