#ifndef THREAD_MSG_SLEEP_BASE_H_
#define THREAD_MSG_SLEEP_BASE_H_

#define USECS_PER_SEC 1000000

class FreqSleeperBase {
    public:
        virtual void sleep() = 0;
};

#endif
