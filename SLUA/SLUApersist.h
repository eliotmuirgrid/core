#ifndef _SLUA_PERSIST_H_
#define _SLUA_PERSIST_H_
//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// SLUApersist
// 
// Start of routine to persist a lua instance.
//-------------------------------------------------------

struct lua_State;

class BASstring;

void SLUApersist(lua_State* L, BASstring* pString);

#endif
