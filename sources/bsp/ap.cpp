//******************************************************************************
/**
 * \file    ap.c
 * \author  Chad Swenson
 * \date    May 2013
 * \brief   Applicaction
 *
 * Copyright 2013 Bobcat Company as an unpublished work.
 * All Rights Reserved.
 *
 * The information contained herein is confidential
 * property of Bobcat Company. The use, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Bobcat Company.
 *
 *******************************************************************************/
#include "ap.h"
#include <stddef.h>
#include <stdint.h>

#include "ap_schd.h"
#include "ap_eeprom.h"

#include "ap_tasks.h"

#include "ap_bsp.h"
#include "bsp_common.h"
#include "bsp_sdata.h"
#include "bsp_clock.h"

#include "hw_io.h"


//******************************************************************************
// Defines
//******************************************************************************
#if 0
# warning "AP Debug code enabled!"
# include "bsp_dout.h"
# define AP_DEBUG_INIT()    do{ bsp_dout_initCh(BSP_DOUT_DEBUG1, false);   \
                                bsp_dout_initCh(BSP_DOUT_DEBUG2, false);   }while(0)
# define AP_DEBUG1_HIGH()   do{ bsp_dout_SetValue(BSP_DOUT_DEBUG1, true);  }while(0)
# define AP_DEBUG1_LOW()    do{ bsp_dout_SetValue(BSP_DOUT_DEBUG1, false); }while(0)
# define AP_DEBUG2_HIGH()   do{ bsp_dout_SetValue(BSP_DOUT_DEBUG2, true);  }while(0)
# define AP_DEBUG2_LOW()    do{ bsp_dout_SetValue(BSP_DOUT_DEBUG2, false); }while(0)
#else
# define AP_DEBUG_INIT()    ((void)0)   ///< Initialize ROM debug output
# define AP_DEBUG1_HIGH()   ((void)0)   ///< Set ROM debug 1 output high
# define AP_DEBUG1_LOW()    ((void)0)   ///< Set ROM debug 1 output low
# define AP_DEBUG2_HIGH()   ((void)0)   ///< Set ROM debug 2 output high
# define AP_DEBUG2_LOW()    ((void)0)   ///< Set ROM debug 2 output low
#endif

//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void ap_eeprom_task(void);


//******************************************************************************
// Static Variables
//******************************************************************************
static ap_schd_taskConfig_t const bsp_taskConfig[] =
{
  //  Init Function               Run Function              Rate(ms)  Offset(ms)
  {   NULL,                       ap_eeprom_task,           1,        0       },
  {   NULL,                       hw_can_update_fast,       1,        0       },
  {   bsp_taskInit,               bsp_taskRun,              10,       0       },
};

static ap_schd_t schd;
static ap_schd_stats_t schdStats;

static ap_schd_task_t bsp_task[BSP_ARRAY_LEN(bsp_taskConfig)];
static ap_schd_stats_t bsp_taskStats[BSP_ARRAY_LEN(bsp_taskConfig)];

static ap_schd_taskConfig_t ap_taskConfig[BSP_ARRAY_LEN(ap_tasks)];
static ap_schd_task_t ap_task[BSP_ARRAY_LEN(ap_tasks)];
static ap_schd_stats_t ap_taskStats[BSP_ARRAY_LEN(ap_tasks)];


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void ap_init(void)
{
  uint_fast16_t i;
  uint8_t run_mask = 0x01;
  uint8_t apMode= bsp_sdata_getAppMode();

  ap_schd_init(&schd, &schdStats);

  AP_DEBUG_INIT();
  AP_DEBUG1_HIGH();

  if (ap_smode <= 7)
  {
    run_mask <<= apMode;
  }

  for (i = 0; i < BSP_ARRAY_LEN(bsp_taskConfig); i++)
  {
    ap_schd_regTask(&schd, &bsp_task[i], &bsp_taskConfig[i], &bsp_taskStats[i]);
  }

  for (i = 0; i < BSP_ARRAY_LEN(ap_tasks); i++)
  {
    // Only schedule enabled tasks
    if (ap_tasks[i].active_modes & run_mask)
    {
      ap_taskConfig[i].initFunc = ap_tasks[i].initialize;
      ap_taskConfig[i].runFunc = ap_tasks[i].update;
      ap_taskConfig[i].rate = 10;
      ap_taskConfig[i].offset = 0;

      ap_schd_regTask(&schd, &ap_task[i], &ap_taskConfig[i], &ap_taskStats[i]);
    }
  }

  ap_schd_initTasks(&schd);
  AP_DEBUG1_LOW();
}

//******************************************************************************
void ap_run(void)
{
  AP_DEBUG1_HIGH();
  ap_schd_run(&schd);
  AP_DEBUG1_LOW();
}


//******************************************************************************
// Static Function Definitions
//******************************************************************************
static void ap_eeprom_task(void)
{
  AP_DEBUG2_HIGH();
  eeServiceEEPROM();
  eeServiceEEPROM();
  eeServiceEEPROM();
  eeServiceEEPROM();
  AP_DEBUG2_LOW();
}


