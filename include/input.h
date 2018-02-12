//input.h

#pragma once

#define INPUT_OFF 0
#define INPUT_BY_CHAR 1
#define INPUT_BY_STRING 2

#include "systems.h"
#include "framework.h"

using namespace Systems;

class Input : public Systems::System {
    public:
        Input (Systems::MessageBus *mbus);
        ~Input ();
        void inputListener ();
        void start_system () override;
        void blockInput ();
        void unblockInput ();
        bool isBlocked ();
        void setStringMode ();
        void setCharMode ();
    private:
        int input_type;
        using Systems::System::System;
        typedef System super;
        std::thread input_listener;
        const char *key_to_string (Framework::KB_Key k);
};
