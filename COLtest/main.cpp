#include <stdio.h>
#include <lua/lua.hpp>  // using C++ header file for C linkage

#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Open lua
  lua_State *L = luaL_newstate();
  // Load the libraries
  luaL_openlibs(L);

  // Execution of a lua string
  luaL_dostring(L, "print \"The answer to life and universe and everything is Lua.\"");
  // Close lua
  lua_close (L);

  return 0;
}
