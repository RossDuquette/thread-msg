#ifndef THREAD_MSG_SLEEP_RT_H_
#define THREAD_MSG_SLEEP_RT_H_

#include "sleep-base.h"

class FreqSleeperRT : public FreqSleeperBase {
    public:
        FreqSleeperRT(float hz, uint64_t runtime_usecs);

        void sleep() override;

    private:
};

#endif
