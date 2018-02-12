// console.h

#pragma once

#include "systems.h"

using namespace Systems;

class Console : public Systems::System {
    public:
        Console (MessageBus *mbus);
        void inputListener ();
        void start_system () override;
        void processMsg (Systems::Msg *msg) override;
        void print_logo ();
        void process_cmd (std::string s);
        ~Console ();
    private:
        using System::System;
        typedef System super;
        std::thread in_handler;
        bool console_support;

        std::string cmd_list[nil_msg + 1] = {
        "kb_event",
        "js_event",
        "error",
        "warning",
        "quit",
        "block_input",
        "unblock_input",
        "shutdown",
        "pause_audio",
        "resume_audio",
        "stop_audio",
        "play_audio",
        "set_audio",
        "nil_msg"
        };
};


