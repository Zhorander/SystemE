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

