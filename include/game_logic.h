//game_logic.h

#pragma once

#include "systems.h"
#include "framework.h"
#include "script_reader.h"

class GameLogic : public Systems::System {
    public:
        GameLogic(Systems::MessageBus *mbus, std::string path);
        ~GameLogic();
        void start_system() override;
        void processMsg(Msg *msg) override;
    private:
        ScriptReader *assembleScriptReader(std::string path);
        ScriptReader *sReader;
        using Systems::System::System;
        typedef System super;
};

