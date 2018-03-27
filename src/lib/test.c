#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"


static int luax_test(lua_State *L) {
    printf("test func\n");
    return lua_yield(L,0);
}

static luaL_Reg funcs[] = {
    { "test", luax_test },
    { NULL, NULL }
};

int luaopen_test(lua_State *L) {
    luaL_checkversion(L);
    printf("load test\n");
    luaL_newlib(L,funcs);
    return 1;
}

