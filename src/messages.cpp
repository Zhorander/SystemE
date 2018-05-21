#include "messages.h"

//-----MSG-----
Msg::Msg (msg_type t, void *val)
{
    message_type = t;
    value = val;
    p = normal; // if no priority given, treat a normal
}

Msg::Msg (msg_type t, void *val, priority pr)
{
    message_type = t;
    value = val;
    p = pr;
}

Msg::~Msg ()
{
    if (value) {
        free (value);
        value = NULL;
    }
}

msg_type Msg::getMsgType ()
{
    return message_type;
}

void *Msg::getValue ()
{
    return value;
}

std::string Msg::asString ()
{
    return std::string ("generic message");
}
