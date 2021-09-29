#include <stdio.h>
#include <stdlib.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "pluto.h"

static int LUAF_createludata(lua_State *L)
{
	lua_pushlightuserdata(L, (void*)321);
	return 1;
}

/* A userdata that may be literally persisted */
static int LUAF_boxinteger(lua_State *L)
{
					/* num */
	int* ptr = lua_newuserdata(L, sizeof(int));
					/* num udata */
	*ptr = luaL_checkint(L, 1);
	lua_newtable(L);
					/* num udata mt */
	lua_pushstring(L, "__persist");
					/* num udata mt "__persist" */
	lua_pushboolean(L, 1);
					/* num udata mt "__persist" true */
	lua_rawset(L, 3);
					/* num udata mt */
	lua_setmetatable(L, 2);
					/* num udata */
	return 1;
}

static int LUAF_boxboolean(lua_State *L)
{
					/* bool */
	char* ptr = lua_newuserdata(L, sizeof(char));
					/* bool udata */
	*ptr = lua_toboolean(L, 1);
	lua_newtable(L);
					/* num udata mt */
	lua_pushstring(L, "__persist");
					/* num udata mt "__persist" */
	lua_getglobal(L, "booleanpersist");
					/* num udata mt "__persist" booleanpersist */
	lua_rawset(L, 3);
					/* num udata mt */
	lua_setmetatable(L, 2);
					/* num udata */
	return 1;
}

static int LUAF_unboxboolean(lua_State *L)
{
					/* udata */
	lua_pushboolean(L, *(char*)lua_touserdata(L, 1));
					/* udata bool */
	return 1;
}

int main()
{
	lua_State* L = lua_open();

	luaopen_base(L);
	luaopen_table(L);
	luaopen_string(L);
	luaopen_math(L);
	luaopen_io(L);
	luaopen_debug(L);
	pluto_open(L);
	lua_settop(L, 0);

	lua_register(L, "createludata", LUAF_createludata);
	lua_register(L, "boxinteger", LUAF_boxinteger);
	lua_register(L, "boxboolean", LUAF_boxboolean);
	lua_register(L, "unboxboolean", LUAF_unboxboolean);

	lua_dofile(L, "pptest.lua");

	lua_close(L);

	return 0;
}
