//graphics.h

#pragma once

#include "systems.h"
#include "framework.h"

class Graphics : public Systems::System {
    public:
        Graphics(Systems::MessageBus *mbus, int height, int width);
        ~Graphics();
        void start_system() override;
        void processMsg(Msg *msg) override;
        void eventHandler();
        void setInputHandler(Framework::WindowObserver *wo);
    private:
        Framework::Window *win;
        Framework::WindowObserver *winObserver;
        std::thread event_poller;
        using Systems::System::System;
        typedef System super;
};
