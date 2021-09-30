//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// SLUApersist
// 
// Implementation
//-------------------------------------------------------

#include "SLUApersist.h"

#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

#include <lua/lua.hpp>

static const char* SLUAshowType(lua_State* L, int i){
   switch (lua_type(L, i)){
   case LUA_TNIL: return "nil"; break;
   case LUA_TSTRING: return "string"; break;
   case LUA_TFUNCTION: return "function"; break; 
   default:
      return "unmapped type";
   }
}


static void SLUAshow(lua_State* L, int i){
   BAS_FUNCTION(SLUAshow);
   switch (lua_type(L, i)){
   case LUA_TNIL: BAS_TRC("nil"); break;
   case LUA_TSTRING: BAS_TRC("String" << lua_tostring(L, i)); break;
   case LUA_TFUNCTION: BAS_TRC("Function"); break; 
   default:
      BAS_TRC("Unknown type.");
   }
}

static void SLUAtableIterate(lua_State* L){
   BAS_FUNCTION(SLUAtableIterate);
   lua_pushnil(L);  /* first key */
   while (lua_next(L, 1) != 0) {
      BAS_VAR2(SLUAshowType(L, -2), SLUAshowType(L, -1));
      SLUAshow(L, -2);
      SLUAshow(L, -1);
      /* removes 'value'; keeps 'key' for next iteration */
      lua_pop(L, 1);
   }
}

void SLUApersist(lua_State* L, BASstring* pString){
   BAS_FUNCTION(SLUApersist);
   BAS_VAR(L);
   lua_pushglobaltable(L);
   BAS_VAR(lua_type(L, -1));
   BAS_VAR(lua_istable(L, -1));
   SLUAtableIterate(L);
}

