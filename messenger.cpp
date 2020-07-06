#include <string.h>

#include "messenger.h"

sem_t Messenger::new_msg[MAX_NUM_TOPICS][MAX_NUM_MODULES];
pthread_once_t Messenger::new_msg_initialized = PTHREAD_ONCE_INIT;
pthread_mutex_t Messenger::mutex = PTHREAD_MUTEX_INITIALIZER;
Msg Messenger::msg_buffer[MAX_NUM_TOPICS][MSG_BUFFER_SIZE];
int Messenger::write_index[MAX_NUM_TOPICS];
int Messenger::read_index[MAX_NUM_TOPICS][MAX_NUM_MODULES];

Messenger::Messenger(int module) :
    module(module)
{
}

void Messenger::send(int topic, const Msg* msg)
{
    pthread_mutex_lock(&mutex);
    msg_buffer[topic][write_index[topic]] = *msg;
    inc_index(write_index[topic]);
    pthread_mutex_unlock(&mutex);

    int modules_waiting;
    pthread_once(&new_msg_initialized, new_msg_init);
    for (int module = 0; module < MAX_NUM_MODULES; module++) {
        sem_post(&new_msg[topic][module]);
    }
}

void Messenger::recv(int topic, Msg* msg)
{
    wait_for_msg(topic);

    pthread_mutex_lock(&mutex);
    *msg = msg_buffer[topic][read_index[topic][module]];
    inc_index(read_index[topic][module]);
    pthread_mutex_unlock(&mutex);
}

bool Messenger::try_recv(int topic, Msg* msg)
{
    if (get_unread(topic) == 0) {
        return false;
    }

    recv(topic, msg);
    return true;
}

int Messenger::inc_index(int& index)
{
    index = (index + 1) % MSG_BUFFER_SIZE;
}

void Messenger::wait_for_msg(int topic)
{
    while (get_unread(topic) == 0) {
        pthread_once(&new_msg_initialized, new_msg_init);
        sem_wait(&new_msg[topic][module]);
    }
}

int Messenger::get_unread(int topic)
{
    pthread_mutex_lock(&mutex);
    int read = read_index[topic][module];
    int write = write_index[topic];
    pthread_mutex_unlock(&mutex);

    int unread;
    if (read == write) {
        unread = 0;
    } else if (read < write) {
        unread = write - read;
    } else {
        unread = MSG_BUFFER_SIZE - read + write;
    }
    return unread;
}

void Messenger::new_msg_init()
{
    for (int topic = 0; topic < MAX_NUM_TOPICS; topic++) {
        for (int module = 0; module < MAX_NUM_MODULES; module++) {
            sem_init(&new_msg[topic][module], 0, 0);
        }
    }
}
