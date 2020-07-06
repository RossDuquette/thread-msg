#include <assert.h>
#include <string.h>

#include "msg.h"

Msg::Msg() :
    len(0)
{
    memset(data, 0, MAX_MSG_LEN);
}

Msg::Msg(void* msg_data, int msg_len) :
    len(msg_len)
{
    memcpy(data, msg_data, msg_len);
}

void Msg::operator=(const Msg& other)
{
    assert(other.len <= MAX_MSG_LEN);
    memcpy(data, other.data, MAX_MSG_LEN);
    len = other.len;
}
