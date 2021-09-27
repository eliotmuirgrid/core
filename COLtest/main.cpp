#include <stdio.h>

extern "C" {
   #include <lua/lua.h>
   #include <lua/lualib.h>
   #include <lua/lauxlib.h>
}

#include <stdlib.h>

static void* l_alloc (void* ud, void* ptr, size_t osize, size_t nsize) {
    (void)ud;  (void)osize;  /* not used */
    if (nsize == 0) {
      free(ptr);
      return NULL;
    }
    else return realloc(ptr, nsize);
}

int main(int argc, char *argv[]) {
  // Open lua
  lua_State *L = lua_newstate(&l_alloc, NULL);

  // Load the libraries
  luaL_openlibs(L);

  // Execution of a lua string
  luaL_dostring(L, "print \"The answer to life and universe and everything is Lua.\"");
  // Close lua
  lua_close (L);

  return 0;
}
