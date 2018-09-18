
#ifndef hw_timer_h
#define hw_timer_h

#include "stdint.h"
#include "stdbool.h"

uint32_t hw_timer_mS_count(void);
uint32_t hw_timer_uS_count(void);

////////////////////////////////////////////////////////////////////////////////////////////////////
// "hw_timer" class to implement a time-base and various types of timeouts.
//  Example usage:
//
//  <<<< initialization >>>>
//      hw_timer sample_loop;
//
//      .....
//
//      sample_loop.SetPeriod_mS(10);
//
//
//  <<<< somewhere in a periodic update function >>>>
//
//      if ( sample_loop.Expired() )
//      {
//          sample_loop.Reset();
//
//          ....  // sample the inputs.
//      }

class hw_timer
{
public:
    void Reset(void);

    enum state_t
    {
        RUNNING, EXPIRED
    };
    enum state_t  GetState(void);

    bool Expired(void) { return GetState() == EXPIRED; }
    bool Running(void) { return GetState() == RUNNING; }

    void     SetPeriod_mS(uint16_t _period_mS);

    uint16_t GetTime_mS  (void);


    static uint16_t mS_count(void);  // Returns: A 32-bit value representing the
                                     //          number of mS since the last reset
                                     //          overflows at ~49.71 days.

private:
    uint16_t start_mS;
    uint16_t period_mS;
    state_t state;
};



////////////////////////////////////////////////////////////////////////////////////////////////////
// "hw_stimer" class which implments a simple count-down timer functionality.
//  Example usage:
//
//  <<<< initialization >>>>
//      hw_stimer VBATT_too_high_timer;
//
//      .....
//
//      VBATT_too_high_timer.set_rate(50);  // times out in 50 iterations
//
//
//  <<<< somewhere in a periodic update function >>>>
//      VBATT_too_high_timer.update();
//
//      .....
//
//      if ( /* NOT "battery voltage too high" */ )
//          VBATT_too_high_timer.reset();
//
//      ......
//
//      if ( VBATT_too_high_timer.expired() )
//          /* the battery voltage has been "too high" for 50 iterations */
//

class hw_stimer
{
public:
    enum
    {
        OFF_CNT=0xFF
    };

    bool expired(void)   const { return rate_cnt==0;       }
    bool off    (void)   const { return rate_cnt==OFF_CNT; }

    void set     (uint8_t rate_)  { rate_cnt = rate_; }

    void set_rate(uint8_t rate_)  { rate_cnt = DEFAULT_RATE = rate_; }

    void reset   (void)       { rate_cnt = DEFAULT_RATE;   }

    void update  (void)       { if (rate_cnt != OFF_CNT && rate_cnt > 0)
                                        --rate_cnt;
                                  }

private:
    uint8_t rate_cnt;
    uint8_t DEFAULT_RATE;
};

#endif

