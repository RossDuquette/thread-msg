#ifndef THREAD_MSG_SLEEP_H_
#define THREAD_MSG_SLEEP_H_

#include <stdint.h>
#include <time.h>

#include "sleep-base.h"

class FreqSleeper : public FreqSleeperBase {
    public:
        FreqSleeper(float hz);

        void sleep() override;

    private:
        uint32_t period_usecs;
        clock_t prev_time;

        uint32_t calc_delay_usecs();
        uint32_t time_diff_usecs();
};

#endif
