//******************************************************************************
/**
 * \file    main.c
 * \author  Al Liebel, Chad Swenson
 * \date    May 2013
 * \brief   main
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
#include "ap_bsp.h"
#include "ap.h"


//******************************************************************************
/**
 * Main
 *
 * \return void
 *******************************************************************************/
void main(void)
{
  bsp_init();
  ap_init();

  for (;;)
  {
    bsp_sleep();
    ap_run();
    bsp_run();
  }
}


