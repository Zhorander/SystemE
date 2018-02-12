//script_manager.h

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

