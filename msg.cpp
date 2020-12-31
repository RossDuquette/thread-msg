#include <assert.h>
#include <string.h>

#include "msg.h"

Msg::Msg()
{
    memset(data, 0, MAX_MSG_LEN);
}

Msg::Msg(void* msg_data, int msg_len)
{
    memcpy(data, msg_data, msg_len);
}

void Msg::copy_from(const Msg& other)
{
    memcpy(data, other.data, MAX_MSG_LEN);
}
