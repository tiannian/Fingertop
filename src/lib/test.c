#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "uv.h"

int ftop_test(lua_State *L) {
    /* printf("%x\n",L); */
    return lua_yield(L,0);
}

int luaopen_test(lua_State *L) {
    luaL_checkversion(L);
    luaL_Reg funcs[] = {
        { "test", ftop_test },
        { NULL, NULL }
    };
    printf("load test\n");
    luaL_newlib(L,funcs);
    return 1;
}

