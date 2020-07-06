#include <assert.h>
#include <linux/sched.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#include "sleep-rt.h"

struct sched_attr {
    uint32_t size;
    uint32_t sched_policy;
    uint64_t sched_flags;
    int32_t sched_nice;
    uint32_t sched_priority;
    uint64_t sched_runtime;
    uint64_t sched_deadline;
    uint64_t sched_period;
};

FreqSleeperRT::FreqSleeperRT(float hz, uint64_t runtime_usecs)
{
    uint64_t runtime_nsecs = runtime_usecs * 1000;
    uint64_t period_nsecs = USECS_PER_SEC * 1000 / hz;
    struct sched_attr attr = {
        .size = sizeof(attr),
        .sched_policy = SCHED_DEADLINE,
        .sched_flags = 0,
        .sched_nice = 0,
        .sched_priority = 0,
        .sched_runtime = runtime_nsecs,
        .sched_deadline = period_nsecs,
        .sched_period = period_nsecs
    };

    pid_t tid = syscall(SYS_gettid);

    assert(syscall(__NR_sched_setattr, tid, &attr, 0) == 0
           && "FreqSleeperRT must be run as root");
}

void FreqSleeperRT::sleep()
{
    sched_yield();
}
