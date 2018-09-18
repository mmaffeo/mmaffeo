
/*
    This module provides some timer functionality
*/


#include "hw_timer.h"
#include "hw_clock.h"

#include "hw_mcu.h"


void hw_timer::Reset(void)
{
    state = RUNNING;
    start_mS += period_mS;
}

hw_timer::state_t hw_timer::GetState(void)
{
    if (state == RUNNING)
    {
        uint16_t delta = mS_count() - start_mS;

        if (delta >= period_mS)
        {
            state = EXPIRED;
        }
    }

    return state;
}

void hw_timer::SetPeriod_mS(uint16_t _period_mS)
{
    start_mS  = mS_count();
    period_mS = _period_mS;
}

uint16_t hw_timer::GetTime_mS  (void)
{
    return mS_count()-start_mS;
}

uint16_t hw_timer::mS_count(void)
{
    return hw_clock_mS();
}

