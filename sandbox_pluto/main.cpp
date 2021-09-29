#include <stdio.h>
#include <lua5032/lua.hpp>  // using C++ header file for C linkage

#include <stdlib.h>

extern "C" int print(lua_State* L){
  const char* pString = lua_tostring (L, -1);
  printf("%s", pString);
  return 0;
}

int main(int argc, char *argv[]) {
  // Open lua
  lua_State *L = lua_open();
  // Load the libraries
  //luaL_openlibs(L);

  lua_pushcfunction(L, print);
  lua_setglobal(L, "print");

  // Execution of a lua string
  lua_dostring(L, "local X = 42; print('The answer to life and universe and everything is '..X..'\n');");
  // Close lua



  lua_close (L);

  return 0;
}
