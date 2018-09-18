//******************************************************************************
/**
 * \file    ap.h
 * \author  Chad Swenson
 * \date    May 2013
 * \brief   Applicaction Header
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
#ifndef AP_H
#define AP_H

#include <stdint.h>


//******************************************************************************
/**
 *  Initialize the Application
 *
 * \return void
 *******************************************************************************/
void ap_init(void);

//******************************************************************************
/**
 *  Run the Application
 *
 * \note Call at the system tick rate
 *
 * \return void
 *******************************************************************************/
void ap_run(void);


#endif /* AP_H */

