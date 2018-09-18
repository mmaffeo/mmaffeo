/***************************************************************
* Project Name: GWPZ20283 - Small Loader Electronics
*
* Copyright 2005 Bobcat Company as an unpublished work.
* All Rights Reserved.
*
* The information contained herein is confidential
* property of Bobcat Company. The use, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Bobcat Company.
*
* First written on 6 October, 2016 by Boston Zachmann
*
* Module Description:
* Routines for interaction with the 7" deluxe panel.
***************************************************************/

#ifndef ap_deluxeG55_h
#define ap_deluxeG55_h

//******************************************************************************
// INCLUDES
//******************************************************************************

#include "hw_can.h"
#include "stdint.h"

//******************************************************************************
// DEFINES
//******************************************************************************
#define G55_AUX_RELEASE_MASK            0xC0

#define G55_AUTO_IDLE_ENGAGED_OFF       0x00
#define G55_AUTO_IDLE_ENGAGED_ON        0x01
#define G55_AUTO_IDLE_ERROR             0x02
#define G55_AUTO_IDLE_NA                0x03

#define G55_ECO_MODE_NA_BITS            0x30
#define G55_ECO_MODE_ON_BIT             0x10


//Vital Message
typedef enum
{
  G55_VITAL_ICON_RPM=10,
  G55_VITAL_ICON_EOP=20,
  G55_VITAL_ICON_ECT=30,
  G55_VITAL_ICON_BATTERY=40,
  G55_VITAL_ICON_HCP=50,
  G55_VITAL_ICON_HOT=60,
  G55_VITAL_ICON_FUEL_USAGE=70,
  G55_VITAL_ICON_DPF_HOUR=80,
  G55_VITAL_ICON_EOT=90
} vital_icons_G55;

typedef enum
{
  G55_ICON_DEFAULT,
  G55_ICON_YELLOW,
  G55_ICON_RED
} icon_color_G55;

typedef enum
{
  G55_SCALE_ZERO,
  G55_SCALE_ONE,
  G55_SCALE_TWO,
} scale_type_G55;

enum phone_states
{
    PHONE_NOT_CONNECTED,
    PHONE_CONNECTED,
    PHONE_CONNECTED_IN_CALL,
    PHONE_LOCKED,
    PHONE_NA = 15
};

//******************************************************************************
// GLOBAL VARIBLES
//******************************************************************************

//******************************************************************************
// FUNCTION PROTOTYPE
//******************************************************************************
void ap_DeluxeG55_initialize(void);
void ap_DeluxeG55_update(void);


#endif