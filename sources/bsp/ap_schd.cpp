//******************************************************************************
/**
 * \file    ap_schd.c
 * \author  Chad Swenson
 * \date    May 2013
 * \brief   Applicaction Task Scheduler
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
#include "ap_schd.h"
#include <stddef.h>
#include <stdint.h>

#include "bsp_clock.h"
#include "bsp_mcu.h"

#define SCHD_INITIAL_DELAY      (0)


//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void checkTask(ap_schd_task_t *task, uint16_t elpasedTime, uint32_t taskIndex);
static void initStats(ap_schd_stats_t *stats);
static void updateStats(ap_schd_stats_t *stats, uint32_t startTime, uint32_t stopTime);

//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void ap_schd_init(ap_schd_t *schd, ap_schd_stats_t *stats)
{
  uint32_t initTime_mS = bsp_clock_ms();
  uint32_t initTime_uS = bsp_clock_us();

  if (schd != NULL)
  {
    schd->taskList = NULL;
    schd->stats = stats;

    schd->timer = (uint16_t)initTime_mS;

    schd->lastStartTime = initTime_uS;
    schd->lastStopTime = initTime_uS;

    initStats(stats);
  }
}

//******************************************************************************
void ap_schd_regTask(ap_schd_t *schd,
                     ap_schd_task_t *task,
                     ap_schd_taskConfig_t const *taskConfig,
                     ap_schd_stats_t *taskStats)
{
  ap_schd_task_t *tempTask = NULL;

  if (schd != NULL)
  {
    tempTask = schd->taskList;
  }

  if ((task != NULL) && (taskConfig != NULL))
  {
    task->config = taskConfig;
    task->stats = taskStats;

    if (tempTask == NULL)
    {
      // Fist task, start the list
      schd->taskList = task;

    }
    else
    {
      // Place the new task at the end of the list
      while (tempTask->next != NULL)
      {
        tempTask = tempTask->next;
      }

      tempTask->next = task;
    }

    // Wait at least SCHD_INITIAL_DELAY ms before running the first task
    task->runTimer = SCHD_INITIAL_DELAY + taskConfig->offset;

    // Make sure last task points to NULL
    task->next = NULL;
  }
}

//******************************************************************************
void ap_schd_initTasks(ap_schd_t *schd)
{
  ap_schd_taskConfig_t const *taskConfig;
  ap_schd_task_t *task = NULL;

  if (schd != NULL)
  {
    task = schd->taskList;

    while (task != NULL)
    {
      taskConfig = task->config;

      if (taskConfig != NULL)
      {
        if (taskConfig->initFunc != NULL)
        {
          taskConfig->initFunc();
        }
      }

      initStats(task->stats);

      task = task->next;
    }

    schd->timer = bsp_clock_ms();
  }
}

//******************************************************************************
void ap_schd_run(ap_schd_t *schd)
{
  uint32_t startTime = bsp_clock_us();
  uint32_t time = bsp_clock_ms();
  uint32_t elapsedTime = time;
  uint32_t taskIndex = 0;
  ap_schd_task_t *task = NULL;

  if (schd != NULL)
  {
    elapsedTime -= schd->timer;
    schd->timer = time;

    task = schd->taskList;

    while (task != NULL)
    {
      checkTask(task, elapsedTime, taskIndex++);
      task = task->next;
    }

    if (schd->stats != NULL)
    {
      // Update the scheduler stats for the last call
      updateStats(schd->stats, schd->lastStartTime, schd->lastStopTime);

      // Prepare stat samples to be calculated next call
      schd->lastStartTime = startTime;
      schd->lastStopTime = bsp_clock_us();
    }
  }
}

//******************************************************************************
// Static Function Definitions
//******************************************************************************

//******************************************************************************
/**
 * Call the task run function if its timer has expired
 *
 * \param task
 * \param elpasedTime   Number of ms since last check
 * \param taskIndex     Position of task in linked list
 *
 * \return void
 *******************************************************************************/
static void checkTask(ap_schd_task_t *task, uint16_t elpasedTime, uint32_t taskIndex)
{
  ap_schd_taskConfig_t const *taskConfig = task->config;

  if (taskConfig != NULL)
  {
    if ((task->runTimer < elpasedTime) && (taskConfig->runFunc != NULL))
    {
      uint32_t taskStartTime;
      uint32_t taskStopTime;

      taskStartTime = bsp_clock_us();
      if (taskConfig->runFunc)
      {
        bsp_mcu_kickTaskWatchdog(taskIndex);
        taskConfig->runFunc();
      }
      taskStopTime = bsp_clock_us();

      updateStats(task->stats, taskStartTime, taskStopTime);

      task->runTimer  += taskConfig->rate;
    }

    task->runTimer -= elpasedTime;
    task->runTimer %= taskConfig->rate;
  }
}

//******************************************************************************
/**
 * Initialize a Statistics Structure
 *
 * \param stats
 *
 * \return void
 *******************************************************************************/
static void initStats(ap_schd_stats_t *stats)
{
  if (stats != NULL)
  {
    stats->count = 0;

    stats->lastStartTime = 0;
    stats->runTime = 0;
    stats->period = 0;

    stats->runTimeAccum = 0;
    stats->runTimeAvg = 0;

    stats->runTimeMin= 0;
    stats->runTimeMax= 0;

    stats->periodMin = 0;
    stats->periodMax = 0;
  }
}

//******************************************************************************
/**
 * Update a Statistics Structure
 *
 * \param task
 * \param startTime
 * \param stopTime
 *
 * \return void
 *******************************************************************************/
static void updateStats(ap_schd_stats_t *stats, uint32_t startTime, uint32_t stopTime)
{
// Increase this number to slow down the average
#define AP_SCHD_STAT_AVG_DIV  (100)

  uint32_t tempUsTime;

  if (stats != NULL)
  {
    // Calc last run time
    tempUsTime = stopTime;
    tempUsTime -= startTime;
    stats->runTime = tempUsTime;

    // Calc last period
    tempUsTime = startTime;
    tempUsTime -= stats->lastStartTime;
    stats->period = tempUsTime;

    stats->lastStartTime = startTime;

    // Ignore the first period
    if (stats->count != 0)
    {
      // Update Min and Max RunTimes
      if (stats->runTime > stats->runTimeMax)
      {
        stats->runTimeMax = stats->runTime;
      }

      if ((stats->runTime < stats->runTimeMin) || (stats->runTimeMin == 0))
      {
        stats->runTimeMin = stats->runTime;
      }

      // Update Min and Max Periods
      if (stats->period > stats->periodMax)
      {
        stats->periodMax = stats->period;
      }

      if ((stats->period < stats->periodMin) || (stats->periodMin == 0))
      {
        stats->periodMin = stats->period;
      }
    }

    // Calculate the average Run Time
    stats->runTimeAccum += stats->runTime;
    stats->runTimeAccum -= stats->runTimeAvg;
    stats->runTimeAvg = stats->runTimeAccum / AP_SCHD_STAT_AVG_DIV;

    stats->count++;
  }
}

