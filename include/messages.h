/*messages.h*/

#include <string>

#pragma once

enum msg_type {
    kb_event = 0, //keyboard event
    js_event, //joystick event
    error,
    warning,
    quit,
    block_input,
    unblock_input,
    shutdown,
    audio_set,
    audio_play,
    audio_pause,
    audio_stop,
    nil_msg, //mark end of enum
};

enum priority {
    low = 0,
    normal,
    high
};

class Msg {
    public:
        Msg (msg_type t, void *val);
        Msg (msg_type t, void *val, priority pr);
        virtual ~Msg ();

        msg_type getMsgType ();
        void *getValue ();
        virtual std::string asString();

        //judge msg priority
        bool operator < (Msg *y)
        {
            return this->p < y->p;
        }

    private:
        msg_type message_type;
        void *value;
        priority p;
};

