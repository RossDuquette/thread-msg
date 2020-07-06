#ifndef THREAD_MSG_MSG_H_
#define THREAD_MSG_MSG_H_

#include <stdint.h>

#include "conf.h"

class Msg {
    public:
        Msg();
        Msg(void* msg_data, int msg_len);

        void operator=(const Msg& other);

        uint8_t data[MAX_MSG_LEN];
        int len;
};

#endif
