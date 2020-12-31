#ifndef THREAD_MSG_MSG_H_
#define THREAD_MSG_MSG_H_

#include <stdint.h>

#include "conf.h"

class Msg {
    public:
        Msg();
        Msg(void* msg_data, int msg_len);

        void copy_from(const Msg& other);

    protected:
        uint8_t data[MAX_MSG_LEN];
};

#endif
