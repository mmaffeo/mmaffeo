
#include "ap_tasks.h"
#include "hw_io.h"
#include "ap_bservice.h"
#include "ap_hwt.h"
#include "ap_main.h"


#define RUN_MASK(b7,b6,b5,b4,b3,b2,b1,b0) (unsigned char) (((b7)?0x80:0) |  ((b6)?0x40:0) |  \
                                                           ((b5)?0x20:0) |  ((b4)?0x10:0) |  \
                                                           ((b3)?0x08:0) |  ((b2)?0x04:0) |  \
                                                           ((b1)?0x02:0) |  ((b0)?0x01:0)    )


const af_task_t ap_tasks[AP_TASK_QTY] =
{
    { &hw_io_initialize,       &hw_io_update        , RUN_MASK(1,1,1,1,1,1,1,1)},
    { &ap_bservice_initialize, &ap_bservice_update  , RUN_MASK(1,1,1,1,1,1,1,1)},
    { &ap_hwt_initialize,      &ap_hwt_update       , RUN_MASK(1,1,1,1,1,1,1,1)},
    { &ap_main_initialize,     &ap_main_update      , RUN_MASK(1,1,1,1,1,1,0,1)}
};

