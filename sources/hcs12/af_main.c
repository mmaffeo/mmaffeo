
#include "af_main.h"
#include "ap_tasks.h"


#include "hw_io.h"
#include "ap_bservice.h"

#include "hw_clock.h"

#include "defines.h"
#include "global.h"
#include "ap_eeprom.h"
#include "MX_Gtwy_Control.h"
#include "ap_bservice_dv.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
// Task execution time statistics
typedef struct
{
    uint16_t min_time_uS;
    uint16_t     time_uS;
    uint16_t max_time_uS;
    uint32_t max_time_cycle_num;
    uint16_t start_time_uS;
    uint16_t init_time_uS;
}task_stat_t;

// Index AP_TASK_QTY is used for idle time calculations
task_stat_t task_stats[AP_TASK_QTY + 1];
uint32_t cycle_num = 0;


static void task_stats_init(void)
{
    for (uint8_t i=0; i < (AP_TASK_QTY + 1); ++i)
    {
        task_stats[i].min_time_uS = 0xFFFFu;
        task_stats[i].max_time_uS = 0;
        task_stats[i].max_time_cycle_num = 0;
        task_stats[i].init_time_uS = 0;
    }
}

static void task_stat_start(task_stat_t *ts)
{
    ts->start_time_uS = hw_clock_uS();
}

static void task_stat_stop(task_stat_t *ts)
{
    ts->time_uS = hw_clock_uS() - ts->start_time_uS;

    if (ts->time_uS > ts->max_time_uS )
    {
        ts->max_time_uS = ts->time_uS;
        ts->max_time_cycle_num = cycle_num;
    }

    if (ts->time_uS < ts->min_time_uS)
    {
        ts->min_time_uS = ts->time_uS;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

dv_table_block  ts_dv_block;

uint16_t ts_info_read(uint16_t i)
{
    uint16_t rvalue=0;
    switch (i)
    {
        case 0:
            rvalue=0;
            break;
        case 1:
            rvalue = hw_reset_max_stack();
            break;
        case 2:
            rvalue = cycle_num & 0xFFFF;
            break;
        case 3:
            rvalue = cycle_num >> 16;
            break;
        case 4:
            rvalue = AP_TASK_QTY;
            break;
        default:
            if ( i <= ( 4 + (AP_TASK_QTY+1) * 3))
            {
                uint8_t ts_ei = i-5;
                uint8_t task   = (uint8_t) (ts_ei / 3);
                uint8_t offset = (uint8_t) (ts_ei % 3);

                switch (offset)
                {
                    case 0: rvalue = (uint16_t) task_stats[task].min_time_uS;  break;
                    case 1: rvalue = (uint16_t) task_stats[task].    time_uS;  break;
                    case 2: rvalue = (uint16_t) task_stats[task].max_time_uS;  break;
                }
            }
            break;
    }

    return rvalue;
}


void ts_info_initialize(void)
{
    uint8_t ts_block_id = ts_base_address >> 8;
    ts_dv_block.initialize     (ts_block_id);
    ts_dv_block.set_read_word_f( ts_info_read);
    dv_list.add_block          (&ts_dv_block );
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// task scheduler routine.

void af_main(uint8_t mode)
{
    static uint8_t tasks_initialized = 0;
    static uint8_t run_mask;

    if (mode > 7)
    {
        run_mask = 0x01;
    }
    else
    {
        run_mask = 0x01 << mode;
    }


    task_stats_init();
    ts_info_initialize();

    uint32_t start_ticks  = 0;
    uint32_t SAMPLE_TICKS = hw_clock_convert_uS_to_clockticks(10000);

    cnt_TryAgain = 0;

    for(;;)   // endless loop
    {
        if ( (hw_clock() - start_ticks) >= SAMPLE_TICKS)
        {
          cycle_num++;
            start_ticks += SAMPLE_TICKS;

            task_stat_start(&task_stats[AP_TASK_QTY]);  // Start timer for all tasks

            // execute the "tasks"
            for (uint8_t af_task_num=0; af_task_num < AP_TASK_QTY; ++af_task_num)
            {
                if ( run_mask & ap_tasks[af_task_num].active_modes)
                {
                    task_stat_start(&task_stats[af_task_num]);  // Start timer for individual tasks
                    if (tasks_initialized)
                    {
                        ap_tasks[af_task_num].update();  // execute the "application" tasks.
                    }
                    else
                    {
                        ap_tasks[af_task_num].initialize();
                    }


                    task_stat_stop(&task_stats[af_task_num]);   // Stop timer for individual tasks
                    if (!tasks_initialized) // Save the initialization time
                    {
                        task_stats[af_task_num].init_time_uS = task_stats[af_task_num].max_time_uS;
                        task_stats[af_task_num].max_time_uS = 0;
                    }
                }
            }
            task_stat_stop(&task_stats[AP_TASK_QTY]);   // Stop timer for all tasks
            if (!tasks_initialized)
            {
                task_stats[AP_TASK_QTY].init_time_uS = task_stats[AP_TASK_QTY].max_time_uS;
                task_stats[AP_TASK_QTY].max_time_uS = 0;
                tasks_initialized = 1;
            }
      }

      if((eeMode != EE_IDLE) && (state_Engine != ENGINE_CRANKING))
      {
        eeServiceEEPROM();
      }
    }
}
