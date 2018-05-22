/*
 *  System E is a general use 2D game engine mostly built for learning
 *  Copyright (C) 2018  Elias Flores
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  contact information: elias_50@live.com
 */

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

