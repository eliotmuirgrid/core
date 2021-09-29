#include <stdio.h>
#include <lua/lua.hpp>  // using C++ header file for C linkage

#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Open lua
  lua_State *L = luaL_newstate();
  // Load the libraries
  luaL_openlibs(L);

  if ( luaL_loadfile(L, "main.lua") == 0 ) {
      if( lua_pcall(L, 0, LUA_MULTRET, 0) != 0){ printf("%s",lua_tostring(L, -1)); }
  }

  // Close lua
  lua_close (L);

  return 0;
}
