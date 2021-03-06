#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "uv.h"

int ftop_default_loop(lua_State *L) {
    /* return lua_yield(); */
    return 0;
}

int luaopen_ftop(lua_State *L) {
    luaL_checkversion(L);
    luaL_Reg funcs[] = {
        { "defaultLoop", ftop_default_loop },
        { NULL, NULL }
    };
    luaL_newlib(L,funcs);
    return 1;
}

