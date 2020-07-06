#ifndef THREAD_MSG_MESSENGER_H_
#define THREAD_MSG_MESSENGER_H_

#include <atomic>
#include <pthread.h>
#include <semaphore.h>

#include "conf.h"
#include "msg.h"

class Messenger {
    public:
        Messenger(int module);

        void send(int topic, const Msg* msg);
        void recv(int topic, Msg* msg);
        bool try_recv(int topic, Msg* msg);

    private:
        int module;

        int inc_index(int& index);
        void wait_for_msg(int topic);
        int get_unread(int topic);

        static void new_msg_init();

        static sem_t new_msg[MAX_NUM_TOPICS][MAX_NUM_MODULES];
        static pthread_once_t new_msg_initialized;
        static pthread_mutex_t mutex;
        static Msg msg_buffer[MAX_NUM_TOPICS][MSG_BUFFER_SIZE];
        static int write_index[MAX_NUM_TOPICS];
        static int read_index[MAX_NUM_TOPICS][MAX_NUM_MODULES];
};

#endif
