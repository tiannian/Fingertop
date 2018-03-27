#include "stdio.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "uv.h"

int main(int argc, char *argv[]) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    if ( luaL_loadfile(L,argv[argc-1])) {
        const char *error = lua_tostring(L,-1);
        /* fprintf(stderr,"%s\n",error); */
    } 
    lua_resume(L, NULL,0);
    uv_run(uv_default_loop(),UV_RUN_DEFAULT);
    /* lua_resume(L, NULL,0); */
    return 0;
}

