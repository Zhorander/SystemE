//input.h

#pragma once

#define INPUT_OFF 0
#define INPUT_ON 1

#include "systems.h"
#include "framework.h"
#include <SFML/Window/Keyboard.hpp>

using namespace Systems;

class Input : public Systems::System, public Framework::WindowObserver {
    public:
        Input (Systems::MessageBus *mbus);
        ~Input ();
        void notify(Framework::event e) override;
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
        const char *key_to_string ();

        std::string key_table[sf::Keyboard::KeyCount] {
        "unknown",
        };
};
