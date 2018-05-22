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

#include <iostream>

extern "C" {
#ifdef USING_LILY
#include <lily/lily.h>
#endif
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

class ScriptReader;
class LuaReader;
class LilyReader;
//class JavaScriptReader;

class ScriptReader {
    public:
        void setScript(std::string path);
        virtual void loadScript();
        virtual void init();
        virtual void draw();
        virtual void update(double dt);
    protected:
        std::string path;
};

class LuaReader : public ScriptReader {
    public:
        LuaReader(std::string path);
        ~LuaReader();
        void loadScript() override;
        void init() override;
        void draw() override;
        void update(double dt) override;
    private:
        lua_State *interpreter;
};

#ifdef USING_LILY
class LilyReader : public ScriptReader {
    public:
        LilyReader(std::string path);
        ~LilyReader();
        void loadScript() override;
        void init() override;
        void draw() override;
        void update(double dt) override;
    private:
        lily_state *interpreter;
};
#endif

