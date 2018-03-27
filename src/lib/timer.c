#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "uv.h"

#define TIMER_MOD_TYPE "luax_timer_t"

static int timer_close(lua_State *L) {
    uv_timer_t *timer = (uv_timer_t *)luaL_checkudata(L,1,TIMER_MOD_TYPE);
    uv_timer_stop(timer);
    return 0;
}

static void timer_cb(uv_timer_t* handle) {
    lua_State *L = uv_handle_get_data((uv_handle_t *)handle);
    if (lua_status(L) == LUA_YIELD) {
        lua_resume(L,NULL,0);
    }
}

static int timer_sleep(lua_State *L) {
    uv_timer_t *timer = (uv_timer_t *)luaL_checkudata(L,1,TIMER_MOD_TYPE);
    int timeout = luaL_checkinteger(L,2);
    uv_handle_set_data((uv_handle_t *)timer,L);
    uv_timer_start(timer,timer_cb,timeout,0);
    return lua_yield(L,0);
}

/* static int timer_interval(lua_State *L) { */
/*     uv_timer_t *timer = (uv_timer_t *)luaL_checkudata(L,1,TIMER_MOD_TYPE); */
/*     int timeout = luaL_checkinteger(L,2); */
/*     int again = luaL_checkinteger(L,3); */
/*     uv_handle_set_data((uv_handle_t *)timer,L); */
/*     uv_timer_start(timer,timer_cb,timeout,again); */
/*     return lua_yield(L,0); */
/* } */

static int timer_new(lua_State *L) {
    uv_timer_t *timer = (uv_timer_t *)lua_newuserdata(L,sizeof(uv_timer_t));
    if (luaL_newmetatable(L,TIMER_MOD_TYPE)) {
        // add some keys
        lua_pushcfunction(L,timer_close);
        lua_setfield(L,2,"__gc");
        lua_pushcfunction(L,timer_sleep);
        lua_setfield(L,2,"sleep");
        /* lua_pushcfunction(L,timer_interval); */
        /* lua_setfield(L,2,"interval"); */
        lua_setfield(L,2,"__index");
    }
    uv_timer_init(uv_default_loop(),timer);
    luaL_setmetatable(L,TIMER_MOD_TYPE);
    return 1;
}


int luaopen_timer(lua_State *L) {
    luaL_checkversion(L);
    luaL_Reg funcs[] = {
        { "new",   timer_new },
        { NULL, NULL }
    };
    luaL_newlib(L,funcs);
    return 1;
}

