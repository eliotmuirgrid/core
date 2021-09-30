#include <stdio.h>
#include <lua/lua.hpp>  // using C++ header file for C linkage


#include <stdlib.h>

#include <SLUA/SLUApersist.h>

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

int main(int argc, const char** argv) {
   BASargParser Parser;
   if (!Parser.parse(argc, argv)){
      Parser.showUsage(BASout);
      return 0;
   }
   BAS_FUNCTION(main);
   // Open lua
   lua_State *L = luaL_newstate();
   // Load the libraries
   //luaL_openlibs(L);

   BAS_TRC("Register trace statement.");
   lua_pushcfunction(L, print);
   lua_setglobal(L, "print");
   BAS_TRC("Set variable.");
   // Execution of a lua string
   luaL_dostring(L, "A = 'Hello world!';");
   luaL_dostring(L, "print(A);");

   BASstring Dump;   
   SLUApersist(L, &Dump);
   BAS_TRC("Closing Lua");

   lua_close (L);
   BASout << newline;
   return 0;
}
