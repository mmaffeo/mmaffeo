
#ifndef ap_hwt_h
#define ap_hwt_h

#include "stdint.h"

extern const uint16_t hwt_support_level;
extern const uint16_t hwt_base_address ;

void ap_hwt_initialize(void);
void ap_hwt_update    (void);


#endif
