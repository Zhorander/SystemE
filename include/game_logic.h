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

