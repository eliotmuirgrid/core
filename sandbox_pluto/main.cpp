#include <stdio.h>
#include <lua5032/lua.hpp>  // using C++ header file for C linkage

extern "C" {
  #include <pluto/pluto.h>
};

#include <stdlib.h>

#include <BAS/BASsinkString.h>
#include <BAS/BASstring.h>
#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

extern "C" int print(lua_State* L){
  const char* pString = lua_tostring (L, -1);
  printf("%s", pString);
  return 0;
}


int APPwriter(lua_State *L, const void* p, size_t sz, void* ud){
  BAS_FUNCTION(APPwriter);
  BASstring String((char*)p, (int)sz);
  BAS_VAR2(sz, String.data());
  BAS_HEX("CHUNK:", p, sz);
  BASsink* pSink = (BASsink*)ud;
  pSink->write((const char*)p, sz);
  return sz;
}


const char* APPread(lua_State* L, void* ud, size_t* pSize){
   BAS_FUNCTION(APPread);
   BAS_VAR2(ud, *pSize);
   BASstring* pString = (BASstring*)ud;
   *pSize = pString->size();
   BAS_VAR(*pSize);
   return pString->data(); 
}

void APPrestoreLua(const BASstring& Data){
   lua_State *L = lua_open();
   lua_pushcfunction(L, print);
   lua_setglobal(L, "print");
   pluto_unpersist(L, APPread, (void*)&Data);    
   lua_close(L);
}


int main(int argc, char *argv[]) {
  BASsetTracePattern("pluto* main");
  BAS_FUNCTION(main);
  // Open lua
  lua_State *L = lua_open();
  // Load the libraries
  //luaL_openlibs(L);

  lua_pushcfunction(L, print);
  lua_setglobal(L, "print");

  // Execution of a lua string
  lua_dostring(L, "function Logo(X) return 'Life'..X end");
  //lua_dostring(L, "local X = 42; print(Logo(' is interesting'));");
  BAS_VAR(lua_gettop(L));
  lua_newtable(L);
  lua_getglobal(L, "Logo");
  BAS_VAR(lua_gettop(L));
  BAS_TRC("Entering pluto_persist");
  BASstring Data;
  BASsinkString Sink(&Data);
  pluto_persist(L, APPwriter, &Sink);
  BAS_VAR(Data.size());
  BAS_TRC("Exiting pluto persist");
// Close lua
  lua_close (L);

  APPrestoreLua(Data);

  BASout << newline;

  return 0;
}
