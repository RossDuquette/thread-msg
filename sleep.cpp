#include <math.h>
#include <unistd.h>

#include "sleep.h"

FreqSleeper::FreqSleeper(float hz) :
    period_usecs(USECS_PER_SEC / hz)
{
    prev_time = clock();
}

void FreqSleeper::sleep()
{
    uint32_t delay_usecs = calc_delay_usecs();
    usleep(delay_usecs);
}

uint32_t FreqSleeper::calc_delay_usecs()
{
    uint32_t exec_time_usecs = time_diff_usecs();
    uint32_t delay_usecs = period_usecs - exec_time_usecs;
    return delay_usecs;
}

uint32_t FreqSleeper::time_diff_usecs()
{
    clock_t curr_time = clock();
    double time_diff_secs = (double) (curr_time - prev_time) / CLOCKS_PER_SEC;
    uint32_t time_diff_usecs = (uint32_t) ceil(time_diff_secs * USECS_PER_SEC);
    prev_time = curr_time;
    return time_diff_usecs;
}
