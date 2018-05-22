//script_reader.h

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
        void init() override;
        void draw() override;
        void update(double dt) override;
    private:
        lily_state *interpreter;
};
#endif

