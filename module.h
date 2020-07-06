#ifndef THREAD_MSG_MODULE_H_
#define THREAD_MSG_MODULE_H_

#include <pthread.h>

#include "conf.h"
#include "messenger.h"

class Module {
    public:
        Module(int id);
        virtual ~Module();

        void start();
        virtual void main() = 0;

    protected:
        Messenger msgr;
        pthread_t thread;

    private:
        static bool module_running[MAX_NUM_MODULES];
};

#endif
