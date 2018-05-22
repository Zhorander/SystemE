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

//Lua includes
#ifdef __cplusplus
#include <lua5.3/lua.hpp>
extern "C"
#else
#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lualib.h>
#endif

//Lily includes
#include <lily/lily.h>

using namespace Systems;

typedef union interpreter_t {
    lua_State *l;
}interpreter;

enum script_type {
    LUA,
    LILY,
    JAVASCRIPT, //stretch goal
    CHAISCRIPT //stretch goal
};

class Script {
    public:
        Script ();
        ~Script ();
        void execute ();
    private:
};

class ScriptInterface : public Systems::System {
    public:
        ScriptInterface (const char *script, script_type type);
        ~ScriptInterface ();
    private:
        script_type t; //show should the system interpret the script
        using Systems::System::System;
        typedef System super;
};

