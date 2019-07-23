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
        fprintf(stderr,"%s\n",error);
    } 
    lua_resume(L, NULL,0);
    /* uv_run(uv_default_loop(),UV_RUN_DEFAULT); */
    /* printf("%x\n",L); */
    lua_State *L1 = lua_newthread (L);
    printf("%d\n",L1->stacksize);
    printf("%d\n",L->stacksize);
    lua_resume(L, L1,0);
        /* const char *error = lua_tostring(L,-1); */
        /* fprintf(stderr,"%s\n",error); */
    /* lua_State *L2 = lua_newthread (L); */
    /* lua_resume(L2, L,0); */
    return 0;
}

