//******************************************************************************
/**
 * \file    stf4_bsp_adc.c
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   STM324xx Specific Analog to Digital Input Source
 *
 * \copyright
 * Copyright 2013 Bobcat Company as an unpublished work.
 * All Rights Reserved.
 *
 * \b Notice:
 * The information contained herein is confidential
 * property of Bobcat Company. The use, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Bobcat Company.
 *
 *******************************************************************************/

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "bsp_common.h"

/// Macro to allow inclusion of STF4 specific headers
#define STF4_INTERNAL (1)
#include "stf4_bsp_adc.h"
#include "stf4_timer.h"
#include "stf4_vectors.h"
#include "stm32f4xx.h"
#include "stf4_bsp_din.h"  // Included for wetting current syncing
#include "stf4_bsp_dout.h" // Included for wetting current syncing
#undef STF4_INTERNAL

/** \brief The number of historical samples to be kept for each
 *         peripcheral channel
 *  \note This number must equal to the number of mux
 *        channels */
#define ADC_NUM_SAMPLES           (8)

/// Maximum number of ADC peripheral channels per ADC peripheral
#define ADC_GROUP_SIZE_MAX        (16)

/// Mask used to quickly convert a sampler counter to a sample index
#define ADC_SAMPLE_INDEX_MASK     (ADC_NUM_SAMPLES - 1)

/// Timer peripheral to be used for triggering the ADC start of conversions
#define ADC_TIMER                 (TIM9)

/// Interrupt Request Number for the ADC_TIMER
#define ADC_TIMER_IRQN            (TIM1_BRK_TIM9_IRQn)

/// Peripheral Clock for ADC_TIMER
#define ADC_TIMER_CLOCK           (RCC_APB2Periph_TIM9)

/// Macro used to enable the ADC_TIMER clock
#define ADC_TIMER_CLOCK_EN_FUNC   (RCC_APB2PeriphClockCmd)

/// ADC conversion frequency in Hz
#define ADC_TIMER_FREQ            (800)

/// Wetting current pulse width. Actual DC will be 1/8 of this DC.
#define ADC_TIMER_WC_DC           (56)

/// ADC / DIN Sample DC. Must be less than ADC_TIMER_WC_DC.
#define ADC_TIMER_SAMPLE_DC       (ADC_TIMER_WC_DC - 6)

/// ADC peripheral clock prescaler
#define ADC_PRESCALER (ADC_Prescaler_Div4)

/// Number of clock cycles for each ADC conversion
#define ADC_SAMPLE_TIME           (ADC_SampleTime_56Cycles)

/// Value added to each ADC sample to center bias the unused low order bits
#define ADC_BIAS_VALUE            (0x0008)

/// Sync this sample with wetting current pulses
#define ADC_SAMPLE_WC_SYNC        (0)

#if 0
# warning "ADC Debug code enabled!"
# include "bsp_dout.h"
# define ADC_DEBUG_INIT()         do{ bsp_dout_initCh(3, false);   \
                                      bsp_dout_initCh(4, false);   \
                                      bsp_dout_initCh(5, false);   \
                                      bsp_dout_initCh(6, false);   }while(0)
# define ADC_DEBUG1_HIGH()        do{ bsp_dout_SetValue(3, true);  }while(0)
# define ADC_DEBUG1_LOW()         do{ bsp_dout_SetValue(3, false); }while(0)
# define ADC_DEBUG2_HIGH()        do{ bsp_dout_SetValue(4, true);  }while(0)
# define ADC_DEBUG2_LOW()         do{ bsp_dout_SetValue(4, false); }while(0)
# define ADC_DEBUG3_HIGH()        do{ bsp_dout_SetValue(5, true);  }while(0)
# define ADC_DEBUG3_LOW()         do{ bsp_dout_SetValue(5, false); }while(0)
# define ADC_DEBUG4_HIGH()        do{ bsp_dout_SetValue(6, true);  }while(0)
# define ADC_DEBUG4_LOW()         do{ bsp_dout_SetValue(6, false); }while(0)
#else
# define ADC_DEBUG_INIT()         ((void)0)   ///< Initialize ADC debug output
# define ADC_DEBUG1_HIGH()        ((void)0)   ///< Set ADC debug 1 output high
# define ADC_DEBUG1_LOW()         ((void)0)   ///< Set ADC debug 1 output low
# define ADC_DEBUG2_HIGH()        ((void)0)   ///< Set ADC debug 2 output high
# define ADC_DEBUG2_LOW()         ((void)0)   ///< Set ADC debug 2 output low
# define ADC_DEBUG3_HIGH()        ((void)0)   ///< Set ADC debug 3 output high
# define ADC_DEBUG3_LOW()         ((void)0)   ///< Set ADC debug 3 output low
# define ADC_DEBUG4_HIGH()        ((void)0)   ///< Set ADC debug 4 output high
# define ADC_DEBUG4_LOW()         ((void)0)   ///< Set ADC debug 4 output low
#endif

/// Enumeration of ADC peripherals
enum adc_index_e
{
  ADC1_INDEX = 0,
  ADC2_INDEX,
  ADC3_INDEX
};

/// ADC Channel Type
typedef enum adc_chType_e
{
  ADC_CH_TYPE_AVG_8 = 0,          ///< Average of previous eight sample (10ms @ 800Hz)
  ADC_CH_TYPE_AVG_4,              ///< Average of previous four sample (5ms @ 800Hz)
  ADC_CH_TYPE_AVG_2,              ///< Average of previous two sample (2.5ms @ 800Hz)
  ADC_CH_TYPE_NORMAL,             ///< No muxing or averaging, most recent sample
  ADC_CH_TYPE_MUX_1,              ///< Multiplex input, no averaging, mux channel 1
  ADC_CH_TYPE_MUX_2,              ///< Multiplex input, no averaging, mux channel 2
  ADC_CH_TYPE_MUX_3,              ///< Multiplex input, no averaging, mux channel 3
  ADC_CH_TYPE_MUX_4,              ///< Multiplex input, no averaging, mux channel 4
  ADC_CH_TYPE_MUX_5,              ///< Multiplex input, no averaging, mux channel 5
  ADC_CH_TYPE_MUX_6,              ///< Multiplex input, no averaging, mux channel 6
  ADC_CH_TYPE_MUX_7,              ///< Multiplex input, no averaging, mux channel 7
  ADC_CH_TYPE_MUX_8,              ///< Multiplex input, no averaging, mux channel 8
  ADC_CH_TYPE_WC_SYNCED           ///< Sample synced with Wetting Current pulse, no averaging
} adc_chType_t;

/// Macro used to retrieve the group index from an adc_groupIndex_e
#define ADC_GROUP_TO_GROUPINDEX(g)  ((g) & 0x0F)
/// Macro used to retrieve the sample order index from an adc_groupIndex_e
#define ADC_GROUP_TO_ADCINDEX(g)    (((g) >> 4) & 0x0F)

/** \brief Enumeration used to define grouping and sample
 *         order of each ADC peripheral channel */
enum adc_groupIndex_e
{
  ADC_G_AIN01_DIN01 = (ADC1_INDEX << 4),     // ADC123_IN0
  ADC_G_AIN02_DIN02,                         // ADC123_IN1
  ADC_G_AIN03_DIN03,                         // ADC123_IN2
  ADC_G_AIN04_DIN04,                         // ADC123_IN3
  ADC_G_AIN05,                               // ADC123_IN10
  ADC_G_AIN06,                               // ADC123_IN11
  ADC_G_AIN07,                               // ADC123_IN12
  ADC_G_AIN09,                               // ADC123_IN13
  ADC_G_INTERNAL_TEMP,                       // ADC1_IN16

  ADC_G_HC_LSD1_IFBK = (ADC2_INDEX << 4),    // ADC12_IN4
  ADC_G_HC_LSD2_IFBK,                        // ADC12_IN5
  ADC_G_HC_LSD3_IFBK,                        // ADC12_IN6
  ADC_G_HC_LSD4_IFBK,                        // ADC12_IN7
  ADC_G_HC_LSD5_IFBK,                        // ADC12_IN8
  ADC_G_HC_LSD6_IFBK,                        // ADC12_IN9
  ADC_G_VSENSOR1_AFBK,                       // ADC12_IN14
  ADC_G_MUX1_OUT,                            // ADC12_IN15

  ADC_G_AIN10 = (ADC3_INDEX << 4),           // ADC3_IN4
  ADC_G_AIN12,                               // ADC3_IN5
  ADC_G_AIN13,                               // ADC3_IN6
  ADC_G_VBAT_AFBK_V,                         // ADC3_IN7
  ADC_G_AIN11,                               // ADC3_IN8
  ADC_G_VSW_AFBK_V,                          // ADC3_IN9
  ADC_G_AIN08,                               // ADC3_IN14
  ADC_G_MUX2_OUT,                            // ADC3_IN15
};

/// ADC Channel config
typedef struct adcCh_config_s
{
  uint32_t clock;                   ///< GPIO Peripheral Clock
  GPIO_TypeDef *port;               ///< GPIO Port
  uint16_t pin;                     ///< GPIO Pin
  uint8_t adcBaseChannel;           ///< ADC Peripheral Channel
  uint8_t adcGroup;                 ///< ADC Peripheral Index and Group Index
  adc_chType_t chType;              ///< ADC Channel Type
} adcCh_config_t;

/// ADC Multiplexor config
typedef struct adcMux_config_s
{
  uint32_t portClock;               ///< GPIO Peripheral Clock
  GPIO_TypeDef *port;               ///< GPIO Port
  uint16_t selectPin0;              ///< Mux Select Pin 0
  uint16_t selectPin1;              ///< Mux Select Pin 1
  uint16_t selectPin2;              ///< Mux Select Pin 2
} adcMux_config_t;

/// ADC and DMA Peripheral config
typedef struct adc_config_s
{
  ADC_TypeDef *adc;                 ///< ADC Peripheral Base
  DMA_Stream_TypeDef *dmaStrream;   ///< DMA Stream
  uint32_t dmaChannel;              ///< DMA Channel
  IRQn_Type dmaIrq;                 ///< DMA IRQ number
  uint32_t dmaIrqFlags;             ///< DMA Interrupt flags
  vectors_entry_t irqHandler;       ///< DMA interrupt service routine
  adcMux_config_t const *muxConfig; ///< Pointer to mux config
} adc_config_t;

/// ADC data
typedef struct adc_data_s
{
  uint32_t sampleCounter;                                        ///< Sample Counter used for buffer indexing
  uint8_t groupLength;                                           ///< Number of ADC peripheral channels assigned to this ADC
  uint8_t chGroup[ADC_GROUP_SIZE_MAX];                           ///< ADC peripheral channels assigned to this ADC
  uint16_t dmaBuffer[ADC_GROUP_SIZE_MAX];                        ///< DMA Buffer
  uint16_t sampleBuffer[ADC_NUM_SAMPLES][ADC_GROUP_SIZE_MAX];    ///< Averaging/Muxing buffer
} adc_data_t;


//******************************************************************************
// Static Function Prototypes
//******************************************************************************

static void initADCData(void);
static void initDMAs(void);
static void initADCs(void);
static void initMuxIO(void);
static void initTimer(void);


//******************************************************************************
// ISR Prototypes
//******************************************************************************

static void adc1_dma_irqHandler(void);
static void adc2_dma_irqHandler(void);
static void adc3_dma_irqHandler(void);
static void timer_irqHandler(void);


//******************************************************************************
// Static Variables
//******************************************************************************

/// ADC Channel Configuration
static adcCh_config_t const adcCh_config[] =
{// Clock                   Port    Pin           Base Channel    ADC Group             Type
  { RCC_AHB1Periph_GPIOA,   GPIOA,  GPIO_Pin_0,   ADC_Channel_0,  ADC_G_AIN01_DIN01,    ADC_CH_TYPE_AVG_8  },  // 00    AIN01_DIN01
  { RCC_AHB1Periph_GPIOA,   GPIOA,  GPIO_Pin_1,   ADC_Channel_1,  ADC_G_AIN02_DIN02,    ADC_CH_TYPE_AVG_8  },  // 01    AIN02_DIN02
  { RCC_AHB1Periph_GPIOA,   GPIOA,  GPIO_Pin_2,   ADC_Channel_2,  ADC_G_AIN03_DIN03,    ADC_CH_TYPE_AVG_8  },  // 02    AIN03_DIN03
  { RCC_AHB1Periph_GPIOA,   GPIOA,  GPIO_Pin_3,   ADC_Channel_3,  ADC_G_AIN04_DIN04,    ADC_CH_TYPE_AVG_8  },  // 03    AIN04_DIN04
  { RCC_AHB1Periph_GPIOC,   GPIOC,  GPIO_Pin_0,   ADC_Channel_10, ADC_G_AIN05,          ADC_CH_TYPE_AVG_8  },  // 04    AIN05
  { RCC_AHB1Periph_GPIOC,   GPIOC,  GPIO_Pin_1,   ADC_Channel_11, ADC_G_AIN06,          ADC_CH_TYPE_AVG_8  },  // 05    AIN06
  { RCC_AHB1Periph_GPIOC,   GPIOC,  GPIO_Pin_2,   ADC_Channel_12, ADC_G_AIN07,          ADC_CH_TYPE_AVG_8  },  // 06    AIN07
  { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_4,   ADC_Channel_14, ADC_G_AIN08,          ADC_CH_TYPE_AVG_8  },  // 07    AIN08
  { RCC_AHB1Periph_GPIOC,   GPIOC,  GPIO_Pin_3,   ADC_Channel_13, ADC_G_AIN09,          ADC_CH_TYPE_AVG_8  },  // 08    AIN09
  { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_6,   ADC_Channel_4,  ADC_G_AIN10,          ADC_CH_TYPE_AVG_8  },  // 09    AIN10
  { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_10,  ADC_Channel_8,  ADC_G_AIN11,          ADC_CH_TYPE_AVG_8  },  // 10    AIN11
  { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_7,   ADC_Channel_5,  ADC_G_AIN12,          ADC_CH_TYPE_AVG_8  },  // 11    AIN12
  { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_8,   ADC_Channel_6,  ADC_G_AIN13,          ADC_CH_TYPE_AVG_8  },  // 12    AIN13
  { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_5,   ADC_Channel_15, ADC_G_MUX2_OUT,       ADC_CH_TYPE_MUX_1  },  // 13    FIN01_AFBK
  { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_5,   ADC_Channel_15, ADC_G_MUX2_OUT,       ADC_CH_TYPE_MUX_2  },  // 14    FIN03_AFBK
  { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_5,   ADC_Channel_15, ADC_G_MUX2_OUT,       ADC_CH_TYPE_MUX_3  },  // 15    FIN04_AFBK
  { RCC_AHB1Periph_GPIOC,   GPIOC,  GPIO_Pin_5,   ADC_Channel_15, ADC_G_MUX1_OUT,       ADC_CH_TYPE_MUX_1  },  // 16    HC_HSD1_AFBK
  { RCC_AHB1Periph_GPIOC,   GPIOC,  GPIO_Pin_5,   ADC_Channel_15, ADC_G_MUX1_OUT,       ADC_CH_TYPE_MUX_2  },  // 17    HC_HSD2_AFBK
  { RCC_AHB1Periph_GPIOC,   GPIOC,  GPIO_Pin_5,   ADC_Channel_15, ADC_G_MUX1_OUT,       ADC_CH_TYPE_MUX_3  },  // 18    HC_HSD3_AFBK
  { RCC_AHB1Periph_GPIOC,   GPIOC,  GPIO_Pin_5,   ADC_Channel_15, ADC_G_MUX1_OUT,       ADC_CH_TYPE_MUX_4  },  // 19    HC_HSD4_AFBK
  { RCC_AHB1Periph_GPIOC,   GPIOC,  GPIO_Pin_5,   ADC_Channel_15, ADC_G_MUX1_OUT,       ADC_CH_TYPE_MUX_5  },  // 20    HC_HSD5_AFBK
  { RCC_AHB1Periph_GPIOC,   GPIOC,  GPIO_Pin_5,   ADC_Channel_15, ADC_G_MUX1_OUT,       ADC_CH_TYPE_MUX_6  },  // 21    HC_HSD6_AFBK
  { RCC_AHB1Periph_GPIOC,   GPIOC,  GPIO_Pin_5,   ADC_Channel_15, ADC_G_MUX1_OUT,       ADC_CH_TYPE_MUX_7  },  // 22    HC_HSD7_AFBK
  { RCC_AHB1Periph_GPIOC,   GPIOC,  GPIO_Pin_5,   ADC_Channel_15, ADC_G_MUX1_OUT,       ADC_CH_TYPE_MUX_8  },  // 23    HC_HSD8_AFBK
  { RCC_AHB1Periph_GPIOA,   GPIOA,  GPIO_Pin_4,   ADC_Channel_4,  ADC_G_HC_LSD1_IFBK,   ADC_CH_TYPE_AVG_8  },  // 24    HC_LSD1_IFBK
  { RCC_AHB1Periph_GPIOA,   GPIOA,  GPIO_Pin_5,   ADC_Channel_5,  ADC_G_HC_LSD2_IFBK,   ADC_CH_TYPE_AVG_8  },  // 25    HC_LSD2_IFBK
  { RCC_AHB1Periph_GPIOA,   GPIOA,  GPIO_Pin_6,   ADC_Channel_6,  ADC_G_HC_LSD3_IFBK,   ADC_CH_TYPE_AVG_8  },  // 26    HC_LSD3_IFBK
  { RCC_AHB1Periph_GPIOA,   GPIOA,  GPIO_Pin_7,   ADC_Channel_7,  ADC_G_HC_LSD4_IFBK,   ADC_CH_TYPE_AVG_8  },  // 27    HC_LSD4_IFBK
  { RCC_AHB1Periph_GPIOB,   GPIOB,  GPIO_Pin_0,   ADC_Channel_8,  ADC_G_HC_LSD5_IFBK,   ADC_CH_TYPE_AVG_8  },  // 28    HC_LSD5_IFBK
  { RCC_AHB1Periph_GPIOB,   GPIOB,  GPIO_Pin_1,   ADC_Channel_9,  ADC_G_HC_LSD6_IFBK,   ADC_CH_TYPE_AVG_8  },  // 29    HC_LSD6_IFBK
  { RCC_AHB1Periph_GPIOC,   GPIOC,  GPIO_Pin_4,   ADC_Channel_14, ADC_G_VSENSOR1_AFBK,  ADC_CH_TYPE_AVG_8  },  // 30    VSENSOR1_AFBK
  { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_9,   ADC_Channel_7,  ADC_G_VBAT_AFBK_V,    ADC_CH_TYPE_AVG_8  },  // 31    VBAT_AFBK_V
  { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_3,   ADC_Channel_9,  ADC_G_VSW_AFBK_V,     ADC_CH_TYPE_AVG_8  },  // 32    VSW_AFBK_V

  //{ 0,                      NULL,   0,            ADC_Channel_16, ADC_G_INTERNAL_TEMP,  ADC_CH_TYPE_AVG_8  },  // 33    INTERNAL_TEMP
};

/// ADC Mux Configuration
static adcMux_config_t const adcMux_config[] =
{// Port Clock              Port    Select 0      Select 1      Select 2
  { RCC_AHB1Periph_GPIOG,   GPIOG,  GPIO_Pin_8,   GPIO_Pin_10,  GPIO_Pin_11 },  // MUX1
  { RCC_AHB1Periph_GPIOG,   GPIOG,  GPIO_Pin_12,  GPIO_Pin_13,  GPIO_Pin_15 },  // MUX2
};

/// ADC Peripheral Configuration
static adc_config_t const adc_config[] =
{// ADC   DMA Stream    DMA Channel     DMA IRQ             DMA IRQ Flags   DMA irqHandler        Mux Config
  { ADC1, DMA2_Stream0, DMA_Channel_0,  DMA2_Stream0_IRQn,  DMA_FLAG_TCIF0, adc1_dma_irqHandler,  NULL              },
  { ADC2, DMA2_Stream2, DMA_Channel_1,  DMA2_Stream2_IRQn,  DMA_FLAG_TCIF2, adc2_dma_irqHandler,  &adcMux_config[0] },
  { ADC3, DMA2_Stream1, DMA_Channel_2,  DMA2_Stream1_IRQn,  DMA_FLAG_TCIF1, adc3_dma_irqHandler,  &adcMux_config[1] },
};

/// ADC Data and Buffers
static adc_data_t adc_data[BSP_ARRAY_LEN(adc_config)];

//******************************************************************************
// Global Variables
//******************************************************************************


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_adc_init(void)
{
  ADC_DEBUG_INIT();

  initADCData();
  initMuxIO();
  initDMAs();
  initADCs();
  initTimer();
}

//******************************************************************************
void bsp_adc_initCh(bsp_adc_t ch)
{
  if ((uint32_t)ch < BSP_ARRAY_LEN(adcCh_config))
  {
    if (adcCh_config[ch].port != NULL)
    {
      GPIO_InitTypeDef GPIO_InitStructure;

      /* Enable GPIO Clock */
      RCC_AHB1PeriphClockCmd(adcCh_config[ch].clock, ENABLE);

      GPIO_StructInit(&GPIO_InitStructure);
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

      GPIO_InitStructure.GPIO_Pin = adcCh_config[ch].pin;

      GPIO_Init(adcCh_config[ch].port, &GPIO_InitStructure);
    }
  }
}

//******************************************************************************
void bsp_adc_deinitCh(bsp_adc_t ch)
{
  // Nothing to do
}

//******************************************************************************
uint16_t bsp_adc_GetValue(bsp_adc_t ch)
{
  uint32_t retVal = 0;

  if ((uint32_t)ch < BSP_ARRAY_LEN(adcCh_config))
  {
    uint8_t adcIndex = ADC_GROUP_TO_ADCINDEX(adcCh_config[ch].adcGroup);
    uint8_t adcGroupIndex = ADC_GROUP_TO_GROUPINDEX(adcCh_config[ch].adcGroup);
    uint32_t shiftCount = 0;
    uint8_t sampleIndex;

    NVIC_DisableIRQ(adc_config[adcIndex].dmaIrq);

    // sampleIndex points at the next sample so decremet it before using
    sampleIndex = adc_data[adcIndex].sampleCounter & ADC_SAMPLE_INDEX_MASK;

    switch (adcCh_config[ch].chType)
    {
    case ADC_CH_TYPE_AVG_8:
      retVal += adc_data[adcIndex].sampleBuffer[--sampleIndex & ADC_SAMPLE_INDEX_MASK][adcGroupIndex];
      retVal += adc_data[adcIndex].sampleBuffer[--sampleIndex & ADC_SAMPLE_INDEX_MASK][adcGroupIndex];
      retVal += adc_data[adcIndex].sampleBuffer[--sampleIndex & ADC_SAMPLE_INDEX_MASK][adcGroupIndex];
      retVal += adc_data[adcIndex].sampleBuffer[--sampleIndex & ADC_SAMPLE_INDEX_MASK][adcGroupIndex];
      shiftCount++;
      // Drop through
    case ADC_CH_TYPE_AVG_4:
      retVal += adc_data[adcIndex].sampleBuffer[--sampleIndex & ADC_SAMPLE_INDEX_MASK][adcGroupIndex];
      retVal += adc_data[adcIndex].sampleBuffer[--sampleIndex & ADC_SAMPLE_INDEX_MASK][adcGroupIndex];
      shiftCount++;
      // Drop through
    case ADC_CH_TYPE_AVG_2:
      retVal += adc_data[adcIndex].sampleBuffer[--sampleIndex & ADC_SAMPLE_INDEX_MASK][adcGroupIndex];
      shiftCount++;
      // Drop through
    case ADC_CH_TYPE_NORMAL:
      retVal += adc_data[adcIndex].sampleBuffer[--sampleIndex & ADC_SAMPLE_INDEX_MASK][adcGroupIndex];
      retVal >>= shiftCount;
      break;

    case ADC_CH_TYPE_MUX_1:
    case ADC_CH_TYPE_MUX_2:
    case ADC_CH_TYPE_MUX_3:
    case ADC_CH_TYPE_MUX_4:
    case ADC_CH_TYPE_MUX_5:
    case ADC_CH_TYPE_MUX_6:
    case ADC_CH_TYPE_MUX_7:
    case ADC_CH_TYPE_MUX_8:
      // The muxed inputs use the same buffer as the averaging inputs,
      // each element of the buffer contains a different channel
      sampleIndex = (uint8_t)(adcCh_config[ch].chType - ADC_CH_TYPE_MUX_1);
      retVal = adc_data[adcIndex].sampleBuffer[sampleIndex][adcGroupIndex];
      break;

    case ADC_CH_TYPE_WC_SYNCED:
      retVal = adc_data[adcIndex].sampleBuffer[ADC_SAMPLE_WC_SYNC][adcGroupIndex];
      break;

    default:
      break;
    }

    NVIC_EnableIRQ(adc_config[adcIndex].dmaIrq);
  }

  return (uint16_t)retVal;
}


//******************************************************************************
// Static Function Definitions
//******************************************************************************

//******************************************************************************
/**
 * Initialize the ADC Data buffers and populate the ADC Groups
 *
 * \return void
 *******************************************************************************/
static void initADCData(void)
{
  uint32_t i;
  uint_fast8_t adcIndex;
  uint_fast8_t adcGroupIndex;
  uint_fast8_t tempLength;

  memset(adc_data, 0, sizeof(adc_data));

  for (i = 0; i < BSP_ARRAY_LEN(adcCh_config); i++)
  {
    adcIndex = ADC_GROUP_TO_ADCINDEX(adcCh_config[i].adcGroup);
    adcGroupIndex = ADC_GROUP_TO_GROUPINDEX(adcCh_config[i].adcGroup);
    tempLength = adcGroupIndex + 1;

    if (adcGroupIndex < ADC_GROUP_SIZE_MAX)
    {
      adc_data[adcIndex].chGroup[adcGroupIndex] = adcCh_config[i].adcBaseChannel;

      // Find the max group index
      if (adc_data[adcIndex].groupLength < tempLength)
      {
        adc_data[adcIndex].groupLength = tempLength;
      }
    }
  }
}

//******************************************************************************
/**
 * Initialize the DMA peripherals
 *
 * \return void
 *******************************************************************************/
static void initDMAs(void)
{
  uint_fast16_t i;
  DMA_InitTypeDef DMA_InitStructure;

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // Enable Clocks
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // Common DMA config
  DMA_StructInit(&DMA_InitStructure);

  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;

  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;

  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;

  DMA_InitStructure.DMA_Priority = DMA_Priority_High;

  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;

  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // ADC specific DMA config
  for (i = 0; i < BSP_ARRAY_LEN(adc_config); i++)
  {
    DMA_InitStructure.DMA_BufferSize = adc_data[i].groupLength;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)adc_data[i].dmaBuffer;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&adc_config[i].adc->DR;

    DMA_InitStructure.DMA_Channel = adc_config[i].dmaChannel;

    DMA_Init(adc_config[i].dmaStrream, &DMA_InitStructure);

    DMA_ClearITPendingBit(adc_config[i].dmaStrream, adc_config[i].dmaIrqFlags);

    // Enable Transfer Complete interrupt
    DMA_ITConfig(adc_config[i].dmaStrream, DMA_IT_TC, ENABLE);

    vectors_setRamVector(adc_config[i].dmaIrq,  adc_config[i].irqHandler);
    NVIC_EnableIRQ(adc_config[i].dmaIrq);

    DMA_Cmd(adc_config[i].dmaStrream, ENABLE);
  }
}

//******************************************************************************
/**
 * Initialize the ADC Peripherals
 *
 * \return void
 *******************************************************************************/
static void initADCs(void)
{
  uint_fast16_t i, ch;
  ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // Enable Clocks
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // ADC common config
  ADC_DeInit();

  ADC_CommonStructInit(&ADC_CommonInitStructure);
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_PRESCALER;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInit(&ADC_CommonInitStructure);

  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;

  ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // ADC specific config
  for (i = 0; i < BSP_ARRAY_LEN(adc_config); i++)
  {
    ADC_InitStructure.ADC_NbrOfConversion = adc_data[i].groupLength;
    ADC_Init(adc_config[i].adc, &ADC_InitStructure);

    for (ch = 0; ch < adc_data[i].groupLength; ch++)
    {
      ADC_RegularChannelConfig(adc_config[i].adc,
                               adc_data[i].chGroup[ch],
                               (ch + 1),
                               ADC_SAMPLE_TIME);
    }

    ADC_Cmd(adc_config[i].adc, ENABLE);

    ADC_EOCOnEachRegularChannelCmd(adc_config[i].adc, ENABLE);

    ADC_DMARequestAfterLastTransferCmd(adc_config[i].adc, ENABLE);
    ADC_DMACmd(adc_config[i].adc, ENABLE);
  }
}

//******************************************************************************
/**
 * Initialize the Mux Select I/O pins
 *
 * \return void
 *******************************************************************************/
static void initMuxIO(void)
{
  uint_fast16_t i;
  GPIO_InitTypeDef GPIO_InitStructure;


  GPIO_StructInit(&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  for (i = 0; i < BSP_ARRAY_LEN(adcMux_config); i++)
  {
    RCC_AHB1PeriphClockCmd(adcMux_config[i].portClock, ENABLE);

    GPIO_InitStructure.GPIO_Pin = adcMux_config[i].selectPin0
                                  | adcMux_config[i].selectPin1
                                  | adcMux_config[i].selectPin2;

    GPIO_ResetBits(adcMux_config[i].port, GPIO_InitStructure.GPIO_Pin);

    GPIO_Init(adcMux_config[i].port, &GPIO_InitStructure);

    GPIO_ResetBits(adcMux_config[i].port, GPIO_InitStructure.GPIO_Pin);
  }
}

//******************************************************************************
/**
 * Initialize the ADC trigger timer
 *
 * \return void
 *******************************************************************************/
static void initTimer(void)
{
/// 100% Duty Cuylce
#define ADC_100_DC  (100)

  // Update Interrupt:
  //  - Enabled every 8 ADC samples for WC Pulse rising edges
  // CC1 Interrupt:
  //  - Enabled every 8 ADC samples for WC Pulse falling edges
  // CC2 Interrupt
  // - Always enabled for ADC and DIN sampling

  uint32_t timerPeriod;

  ADC_TIMER_CLOCK_EN_FUNC(ADC_TIMER_CLOCK,  ENABLE);

  stf4_timer_setFreq16(ADC_TIMER,  ADC_TIMER_FREQ);
  timerPeriod = stf4_timer_getPeriod(ADC_TIMER);

  // Force Initial Timer update
  ADC_TIMER->EGR = TIM_PSCReloadMode_Immediate;

  // Enable CC2 Interrupt generation, for ADC samples
  ADC_TIMER->DIER |= TIM_DIER_CC2IE;

  // TODO - Enalbe CC1 for 56% (7% * 8) DC
  ADC_TIMER->CCR1 = (timerPeriod * ADC_TIMER_WC_DC) / ADC_100_DC;
  // TODO - Enable CC2 for < 56% DC
  ADC_TIMER->CCR2 = (timerPeriod * ADC_TIMER_SAMPLE_DC) / ADC_100_DC;

  // Setup NVIC for Timer Interrupt
  vectors_setRamVector(ADC_TIMER_IRQN, timer_irqHandler);
  NVIC_EnableIRQ(ADC_TIMER_IRQN);

  // Start the Timer
  ADC_TIMER->CR1 |= TIM_CR1_CEN;
}

//******************************************************************************
// ISR Definitions
//******************************************************************************

//******************************************************************************
/**
 * Set the Mux select outputs
 *
 * \param muxConfig Pointer to mux config structure
 * \param sampleCount Value to output (only the 3 LSBits will be used)
 *
 * \return void
 *******************************************************************************/
static inline void setMuxSelects(adcMux_config_t const *muxConfig, uint32_t sampleCount)
{
  uint16_t lowPins = 0;
  uint16_t highPins = 0;

  lowPins |= (sampleCount & GPIO_Pin_0) ? 0 : muxConfig->selectPin0;
  lowPins |= (sampleCount & GPIO_Pin_1) ? 0 : muxConfig->selectPin1;
  lowPins |= (sampleCount & GPIO_Pin_2) ? 0 : muxConfig->selectPin2;

  highPins |= (sampleCount & GPIO_Pin_0) ? muxConfig->selectPin0 : 0;
  highPins |= (sampleCount & GPIO_Pin_1) ? muxConfig->selectPin1 : 0;
  highPins |= (sampleCount & GPIO_Pin_2) ? muxConfig->selectPin2 : 0;

  // Reset Low Pins
  muxConfig->port->BSRRH = lowPins;

  // Set High Pins
  muxConfig->port->BSRRL = highPins;
}

//******************************************************************************
/**
 * Service the DMA end of transfer interrupt
 *
 * \param adcIndex index of ADC peripheral wich is serviced by this DMA Stream
 *
 * \return void
 *******************************************************************************/
static inline void dma_irqHandler(uint32_t adcIndex)
{
  uint32_t i = 0;
  adc_config_t const *adcConfig = &adc_config[adcIndex];
  adc_data_t *adcData = &adc_data[adcIndex];
  uint32_t sampleIndex = adcData->sampleCounter++ & ADC_SAMPLE_INDEX_MASK;
  uint16_t *sampleBuffer = &adcData->sampleBuffer[sampleIndex][0];
  uint16_t *dmaBuffer = adcData->dmaBuffer;

  while (i++ < ADC_GROUP_SIZE_MAX)
  {
    // Add ADC_BIAS_VALUE to each sample
    *sampleBuffer++ = (*dmaBuffer++ | ADC_BIAS_VALUE);
  }

  if (adcConfig->muxConfig != NULL)
  {
    setMuxSelects(adcConfig->muxConfig, adcData->sampleCounter);
  }

  DMA_ClearITPendingBit(adcConfig->dmaStrream, adcConfig->dmaIrqFlags);
}

//******************************************************************************
/**
 * Service the  ADC1 DMA end of transfer interrupt
 *
 * \return void
 *******************************************************************************/
static void adc1_dma_irqHandler(void)
{
  ADC_DEBUG1_HIGH();
  dma_irqHandler(ADC1_INDEX);
  ADC_DEBUG1_LOW();
}

//******************************************************************************
/**
 * Service the  ADC2 DMA end of transfer interrupt
 *
 * \return void
 *******************************************************************************/
static void adc2_dma_irqHandler(void)
{
  ADC_DEBUG1_HIGH();
  dma_irqHandler(ADC2_INDEX);
  ADC_DEBUG1_LOW();
}

//******************************************************************************
/**
 * Service the  ADC3 DMA end of transfer interrupt
 *
 * \return void
 *******************************************************************************/
static void adc3_dma_irqHandler(void)
{
  ADC_DEBUG1_HIGH();
  dma_irqHandler(ADC3_INDEX);
  ADC_DEBUG1_LOW();
}

//******************************************************************************
/**
 * Service the  ADC Trigger Timer reload interrupt
 *
 * \return void
 *******************************************************************************/
static void timer_irqHandler(void)
{
  ADC_DEBUG1_HIGH();

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // Timer Update Interrupt
  if (ADC_TIMER->SR & TIM_SR_UIF) // Active
  {
    if (ADC_TIMER->DIER & TIM_DIER_UIE) // Enabled
    {
      // Wetting Pulse High
      bsp_dout_setWCState(true);
      ADC_DEBUG3_HIGH();

      // Enable CC1 interrupt to clear WC pulse
      ADC_TIMER->DIER |= TIM_DIER_CC1IE;
    }

    // Disable this interrupt
    ADC_TIMER->DIER &= ~TIM_DIER_UIE;
    // Clear this interrupt
    ADC_TIMER->SR &= ~TIM_SR_UIF;

    // Clear CC1 interrupt
    ADC_TIMER->SR &= ~TIM_SR_CC1IF;
  }

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // Timer Compare 1 Interrupt
  if (ADC_TIMER->SR & TIM_SR_CC1IF)  // Active
  {
    if (ADC_TIMER->DIER & TIM_DIER_CC1IE) // Enabled
    {
      // Wetting Pulse Low
      bsp_dout_setWCState(false);
      ADC_DEBUG3_LOW();
    }

    // Disable and clear this interrupt
    ADC_TIMER->DIER &= ~TIM_DIER_CC1IE;
    ADC_TIMER->SR &= ~TIM_SR_CC1IF;
  }

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // Timer Compare 2 Interrupt
  if (ADC_TIMER->SR & TIM_SR_CC2IF)
  {
    //ADC_DEBUG2_HIGH();

    // Start all ADCs
    ADC1->CR2 |= ADC_CR2_SWSTART;
    ADC2->CR2 |= ADC_CR2_SWSTART;
    ADC3->CR2 |= ADC_CR2_SWSTART;

    switch (adc_data[0].sampleCounter & ADC_SAMPLE_INDEX_MASK)
    {
    case ADC_SAMPLE_WC_SYNC:
      // This is the wetting current synced ADC sample, also sample DINs.
      ADC_DEBUG2_HIGH();
      bsp_din_sample();
      ADC_DEBUG2_LOW();
      break;

    case ADC_SAMPLE_INDEX_MASK:
      // Enable Update Interrupt to generate WC pulse for next ADC sample
      ADC_TIMER->DIER |= TIM_DIER_UIE;
      break;

    default:
      break;
    }

    // Clear this Interrupt Flag
    ADC_TIMER->SR &=  ~TIM_SR_CC2IF;

    //ADC_DEBUG2_LOW();
  }

  ADC_DEBUG1_LOW();
}



// 1 of 8 AIN samples must be synced with WC pulse
//  - add new ain type for wc synced sample
//  - use same timer to generate wc syncs and
//  - allow each wc output to be driven as digtal ouput as well
//
// 100hz (10ms) wetting current freq
// ~7% duty cycle
// sample durring wetting current active


