#include <stdio.h>
#include <lua5032/lua.hpp>  // using C++ header file for C linkage

extern "C" {
  #include <pluto/pluto.h>
};

#include <stdlib.h>

#include <BAS/BASargParser.h>
#include <BAS/BASsinkString.h>
#include <BAS/BASstring.h>
#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

extern "C" int print(lua_State* L){
   BAS_FUNCTION(print);
   BAS_VAR(lua_gettop(L));
   if (lua_isnil(L, -1)){
      BASout << "<nil>" << newline << flush;
   } 
   else if (lua_isstring(L, -1)){
      const char* pString = lua_tostring (L, -1);
      BAS_VAR(pString);
      BASout << pString << newline << flush;
   } else {
      BASout << "Unsupported type." << newline << flush;
   }
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
   BAS_FUNCTION(APPrestoreLua);
   lua_State *L = lua_open();
   lua_pushcfunction(L, print);
   lua_setglobal(L, "print");
   lua_newtable(L);  // create table of 'permanent objects'
   BAS_TRC("About to unpersist.");
   pluto_unpersist(L, APPread, (void*)&Data);
   BAS_TRC("About to print.");   
   lua_dostring(L, "print(A);");
   BAS_TRC("Done!");
   lua_close(L);
}


int main(int argc, const char** argv) {
   BASargParser Parser;
   if (!Parser.parse(argc, argv)){
      Parser.showUsage(BASout);
      return 0;
   }
   BAS_FUNCTION(main);
   // Open lua
   lua_State *L = lua_open();
   // Load the libraries
   //luaL_openlibs(L);

   BAS_TRC("Register trace statement.");
   lua_pushcfunction(L, print);
   lua_setglobal(L, "print");
   BAS_TRC("Set variable.");
   // Execution of a lua string
   lua_dostring(L, "A = 'Hello world!';");
   lua_dostring(L, "print(A);");
   BAS_VAR(lua_gettop(L));
   lua_newtable(L);
   lua_getglobal(L, "A");
   BAS_VAR(lua_gettop(L));
   BAS_TRC("Entering pluto_persist");
   BASstring Data;
   BASsinkString Sink(&Data);
   pluto_persist(L, APPwriter, &Sink);
   BAS_VAR(Data.size());
   BAS_TRC("Exiting pluto persist and closing Lua");
   lua_close (L);
   APPrestoreLua(Data);
   BASout << newline;
   return 0;
}
