//******************************************************************************
/**
 * \file    ap_schd.h
 * \author  Chad Swenson
 * \date    May 2013
 * \brief   Applicaction Task Scheduler Header
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
#ifndef AP_SCHD_H
#define AP_SCHD_H

#include <stdint.h>
#include "bsp_clock.h"


/// Statistics Structure
typedef struct ap_schd_stats_s
{
  uint32_t count;                       ///< Number of times Statistics have been calculated
  uint32_t lastStartTime;               ///< Time the last event was started in us
  uint32_t runTimeAccum;                ///< Accumulator used for calculating average run time

  uint32_t runTimeMax;                  ///< Maximum event run time in us
  uint32_t runTime;                     ///< Last event run time in us
  uint32_t runTimeAvg;                  ///< Average event run time in us
  uint32_t runTimeMin;                  ///< Minumum event run time in us

  uint32_t periodMax;                   ///< Maximum event period in us
  uint32_t period;                      ///< Last event period in us
  uint32_t periodMin;                   ///< Minimum event period in us
} ap_schd_stats_t;

/// Task Confiuration Structure
typedef struct ap_schd_taskConfig_s
{
  void (*initFunc)(void);               ///< Pointer to Task Initialization Function
  void (*runFunc)(void);                ///< Pointer to Task Run / Update Function
  uint16_t rate;                        ///< Rate at wich runFunc will be called, in ms
  uint16_t offset;                      ///< Run function call offset in ms
} ap_schd_taskConfig_t;

/// Task Structure
typedef struct ap_schd_task_s
{
  ap_schd_taskConfig_t const *config;   ///< Task Configuration Structure
  ap_schd_stats_t *stats;               ///< Task Statistics
  uint16_t runTimer;                    ///< Milliseconds remaining until next task run call

  // Linked List Pointer
  struct ap_schd_task_s *next;          ///< Pointer to the next task structure in a linked list
} ap_schd_task_t;

/// Scheduler Structure
typedef struct ap_schd_s
{
  ap_schd_task_t *taskList;             ///< Linked list of task structures
  ap_schd_stats_t *stats;               ///< scheduler statistics

  uint16_t timer;                       ///< Used to schedule tasks

  uint32_t lastStartTime;               ///< Used for calculating Scheduler statistics
  uint32_t lastStopTime;                ///< Used for calculating Scheduler statistics
} ap_schd_t;


//******************************************************************************
/**
 * Initialize a scheduler structure
 *
 * \param schd
 * \param schdStats   pointer to structure to hold Scheduler Stats, can be NULL
 *
 * \return void
 *******************************************************************************/
void ap_schd_init(ap_schd_t *schd, ap_schd_stats_t *stats);

//******************************************************************************
/**
 * Register a task to a scheduler
 *
 * \param schd
 * \param task
 * \param taskConfig
 * \param taskStats   pointer to structure to hold Scheduler Stats, can be NULL
 *
 * \return void
 *******************************************************************************/
void ap_schd_regTask(ap_schd_t *schd,
                     ap_schd_task_t *task,
                     ap_schd_taskConfig_t const *taskConfig,
                     ap_schd_stats_t *taskStats);

//******************************************************************************
/**
 * Call the initialize function for all tasks register to a scheduler
 *
 * \param schd
 *
 * \return void
 *******************************************************************************/
void ap_schd_initTasks(ap_schd_t *schd);

//******************************************************************************
/**
 * Execute the scheduler.
 *
 * \note Call at the system tick rate
 *
 * \param schd
 *
 * \return void
 *******************************************************************************/
void ap_schd_run(ap_schd_t *schd);


#endif /* AP_SCHD_H */

