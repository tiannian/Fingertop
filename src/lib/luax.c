#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "uv.h"

int luax_default_loop(lua_State *L) {
    lua_pushlightuserdata(L,uv_default_loop());
    return 1;
}

int luaopen_luax(lua_State *L) {
    luaL_checkversion(L);
    luaL_Reg funcs[] = {
        { "defaultLoop", luax_default_loop },
        { NULL, NULL }
    };
    luaL_newlib(L,funcs);
    return 1;
}

