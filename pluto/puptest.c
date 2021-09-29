#include <stdio.h>
#include <stdlib.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "pluto.h"

static int LUAF_checkludata(lua_State *L)
{
	lua_pushboolean(L, lua_touserdata(L, -1) == (void*)321);
	return 1;
}

static int LUAF_unboxinteger(lua_State *L)
{
	lua_pushnumber(L, *((int*)lua_touserdata(L, -1)));
	return 1;
}

static int LUAF_unboxboolean(lua_State *L)
{
					/* udata */
	lua_pushboolean(L, *(char*)lua_touserdata(L, 1));
					/* udata bool */
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

	lua_register(L, "checkludata", LUAF_checkludata);
	lua_register(L, "unboxinteger", LUAF_unboxinteger);
	lua_register(L, "boxboolean", LUAF_boxboolean);
	lua_register(L, "unboxboolean", LUAF_unboxboolean);

	lua_dofile(L, "puptest.lua");

	lua_close(L);

	return 0;
}
