//script_reader.h

#pragma once

#include <thread>

#ifdef USING_LILY
extern "C" {
#include <lily/lily.h>
}
typedef lily_state *interpreter;
#else
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
typedef lua_State *interpreter;
#endif

class ScriptReader {
    public:
        ScriptReader(std::string path);
        ~ScriptReader();
        void init();
        void draw();
        void update(double dt);
    private:
        interpreter interp;
        std::thread updater;
};

