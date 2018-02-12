#include <math.h>
#include <string.h>
#include "systems.h"

#ifdef __cplusplus
#include <lua5.3/lua.hpp>
extern "C"
#else
#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lualib.h>
#endif

void post_string (void *mbus, const char *str)
{
    char *s = (char *)malloc (sizeof(char) * 64);
    strncpy (s, str, sizeof(char) * 64);

    Systems::Msg *m = new Systems::Msg (Systems::log, (void *)s);

    ((Systems::MessageBus *)mbus)->postMessage (m);
}

static int l_sin (lua_State *L)
{
    //double d = lua_tonumber (L, 1);
    double d = luaL_checknumber (L, 1); /*this is more professional*/
    lua_pushnumber (L, sin(d));

    return 1; /*return # of results*/
}

static int l_post_hello (lua_State *L)
{
    void *msgBus = NULL;

    if (lua_isuserdata (L, 1)) {
        msgBus = lua_touserdata (L, 1);
    } else {
        return 0;
    }

    post_string (msgBus, "Hello World!");

    return 0;
}

void print_error(lua_State* state) {
  // The error message is on top of the stack.
  // Fetch it, print it and then pop it off the stack.
  const char* message = lua_tostring(state, -1);
  puts(message);
  lua_pop(state, 1);
}

void execute(lua_State *state, const char* filename)
{
  // Make standard libraries available in the Lua object
  luaL_openlibs(state);

  int result;

  // Load the program; this supports both source code and bytecode files.
  result = luaL_loadfile(state, filename);

  if ( result != LUA_OK ) {
    print_error(state);
    return;
  }

  // Finally, execute the program by calling into it.
  // Change the arguments if you're not running vanilla Lua code.

  result = lua_pcall(state, 0, LUA_MULTRET, 0);

  if ( result != LUA_OK ) {
    print_error(state);
    return;
  }
}

int luaopen_mylib (lua_State *L) {
    #ifdef _LUA_5_1_
    static const struct luaL_reg mylib [] = {
    #else
    static const struct luaL_Reg mylib [] = {
    #endif
        {"l_sin", l_sin},
        {NULL, NULL}
    };

    #ifdef _LUA_5_1_
    luaL_openlib(L, "mylib", mylib, 0);
    #else
    lua_newtable(L);
    luaL_setfuncs(L, mylib, 0);
    #endif
    return 1;
}

int main (int argc, char **argv) {

    #ifdef _LUA_5_1_
    lua_State *l = lua_open();
    #else
    lua_State *l = luaL_newstate ();
    #endif

    if (argc != 2) {
        printf ("usage: test [lua file name]\n");
        return 1;
    }
    static const struct luaL_Reg mylib [] = {
        {"l_sin", l_sin},
        {NULL, NULL}
    };

    luaL_newlib(l, mylib);
    lua_setglobal (l, "mylib");

    execute (l, argv[1]);

    lua_close (l);

    return 0;
}
