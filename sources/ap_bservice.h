/* 
    Interface to the bobcat service tool protocol.
 */

#ifndef ap_bservice_h
#define ap_bservice_h

#include "stdint.h"
#include "stdbool.h"


extern bool CAN01_tx_enable;

extern const uint16_t ts_base_address;
extern const uint16_t hwt_base_address;


enum ap_bservice_pending_reset_t 
{
    NONE, 
    TO_BB_SMODE_CAPTURED
} ;

extern ap_bservice_pending_reset_t ap_bservice_pending_reset;
extern uint8_t                     ap_bservice_pending_reset_countdown;


extern uint8_t bservice_dv_read_byte(uint16_t i);

void ap_bservice_initialize(void);
void ap_bservice_update    (void);


#endif
