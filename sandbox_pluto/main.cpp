#include <stdio.h>
#include <lua5032/lua.hpp>  // using C++ header file for C linkage

extern "C" {
  #include <pluto/pluto.h>
};

#include <stdlib.h>

#include <BAS/BASstring.h>

extern "C" int print(lua_State* L){
  const char* pString = lua_tostring (L, -1);
  printf("%s", pString);
  return 0;
}


int APPwriter(lua_State *L, const void* p, size_t sz, void* ud){
  BASstring String((char*)p, (int)sz);
  printf("Chunk %lu: %s\n", sz, String.data());
  return sz;
}


int main(int argc, char *argv[]) {
  // Open lua
  lua_State *L = lua_open();
  // Load the libraries
  //luaL_openlibs(L);

  lua_pushcfunction(L, print);
  lua_setglobal(L, "print");

  // Execution of a lua string
  lua_dostring(L, "function Logo(X) return 'Life'..X end");
  lua_dostring(L, "local X = 42; print(Logo(' is interesting'));");
  lua_newtable(L);
  lua_getglobal(L, "Logo");
  pluto_persist(L, APPwriter, NULL);
  printf("***DONE\n");
  
// Close lua
  
  lua_close (L);

  return 0;
}
