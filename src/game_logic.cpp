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

#include "game_logic.h"

/** assembleScriptReader
 * Factory method for creating an appropriate script reader for the given
 * script(i.e a lua reader for a lua script)
 * CURRENTLY WE ONLY SUPPORT LUA
 * but thinking about adding game monkey script and a few others
 */
ScriptReader *GameLogic::assembleScriptReader(std::string path)
{
	std::string filename(path);
    std::string::size_type idx;

    idx = filename.rfind('.');

    if(idx != std::string::npos)
    {
        std::string extension = filename.substr(idx+1);

        if (extension == "lua") {
            return new LuaReader(path);
        }
    }

    return NULL;
}

GameLogic::GameLogic(Systems::MessageBus *mbus, std::string path) : super(mbus)
{
    sReader = assembleScriptReader(path);
    if (sReader == NULL) {
        std::cerr << "Error: unable to read script" << std::endl;
    } else {
        sReader->loadScript();
    }

    start_system();
}

GameLogic::~GameLogic()
{
    if (sReader)
        delete sReader;

    msg_handler.join();
}

void GameLogic::start_system()
{
    msg_handler = std::thread(&System::messageHandler, this);
}

void GameLogic::processMsg(Msg msg)
{
}

