//script_reader.cpp

#include "script_reader.h"

ScriptReader::ScriptReader(std::string path)
{
#ifdef USING_LILY
    lily_config lconf;
    lily_config_init(&lconf);
    interp = lily_new_state(&lconf);
    lily_parse_file(interp, path.c_str());
#else
#ifdef _LUA_5_3
    interp = luaL_newstate();
#else
    interp = lua_open();
#endif
    luaL_openlibs(interp);
    luaL_dofile(interp, path.c_str());
#endif
}

ScriptReader::~ScriptReader()
{
#ifdef USING_LILY
    lily_free_state(interp);
#else
    lua_close(interp);
#endif
}

void ScriptReader::init()
{
#ifdef USING_LILY
    lily_parse_string(interp, "scriptReadder", "init()");
#else
    lua_getglobal(interp, "init");
    //call init with 0 args and 0 results
    lua_call(interp, 0, 0);
#endif
}

void ScriptReader::draw()
{
#ifdef USING_LILY
    lily_parse_string(interp, "scriptReadder", "draw()");
#else
    lua_getglobal(interp, "draw");
    //call draw with 0 args and 0 results
    lua_call(interp, 0, 0);
#endif
}

void ScriptReader::update(double dt)
{
#ifdef USING_LILY
    std::string u = "update(";
    u = u + dt + std::string(")");
    lily_parse_string(interp, "scriptReadder", u.c_str());
#else
    lua_getglobal(interp, "update");
    lua_pushnumber(interp, dt);
    //call draw with 1 arg and 0 results
    lua_call(interp, 1, 0);
#endif
}

