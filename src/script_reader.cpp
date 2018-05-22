//script_reader.cpp

#include "script_reader.h"

//------------------SCRIPTREADER---------------------------

void ScriptReader::setScript(std::string path)
{
    this->path = path;
}

void ScriptReader::loadScript() {}
void ScriptReader::init() {}
void ScriptReader::draw() {}
void ScriptReader::update(double dt) {}

//-------------------LUAREADER-----------------------------
LuaReader::LuaReader(std::string path)
{
    setScript(path);

#ifdef _LUA_5_3
    interpreter = luaL_newstate();
#else
    interpreter = lua_open();
#endif
    luaL_openlibs(interpreter);
}

LuaReader::~LuaReader()
{
    lua_close(interpreter);
}

void LuaReader::loadScript()
{
    luaL_dofile(interpreter, path.c_str());
}

void LuaReader::init()
{
    lua_getglobal(interpreter, "init");

    //call init with 0 args and 0 results
    lua_call(interpreter, 0, 0);
}

void LuaReader::draw()
{
    lua_getglobal(interpreter, "draw");

    //call draw with 0 args and 0 results
    lua_call(interpreter, 0, 0);
}

void LuaReader::update(double dt)
{
    lua_getglobal(interpreter, "update");
    lua_pushnumber(interpreter, dt);

    //call draw with 1 arg and 0 results
    lua_call(interpreter, 1, 0);

}

//----------------LILYREADER------------------------

#ifdef USING_LILY
LilyReader::LilyReader(std::string path)
{
    setScript(path);

    lily_config lconf;
    lily_config_init(&lconf);
    interpreter = lily_new_state(&lconf);
}

LilyReader::~LilyReader()
{
    lily_free_state(interpreter);
}

void LilyReader::loadScript()
{
    lily_parse_file(interpreter, path.c_str());
}

void LilyReader::init()
{
    lily_parse_string(interpreter, "scriptReadder", "init()");
}

void LilyReader::draw()
{
    lily_parse_string(interpreter, "scriptReadder", "draw()");
}

void LilyReader::update(double dt)
{
    std::string u = "update(";
    u = u + dt + std::string(")");
    lily_parse_string(interpreter, "scriptReadder", u.c_str());
}
#endif

