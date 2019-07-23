#include "lstate.h"
#include "lua.h"
#include "llimits.h"
#include "lobject.h"
#include "ldebug.h"
#include "ldo.h"

#include "stdio.h"

LUA_API lua_State *lua_forkthread (lua_State *L, lua_State *from) {
    lua_State *to;
    lua_lock(L);
    /* printf("%d,%d\n",(from->status == LUA_YIELD), */
    /*         (from->status == 0 && from->ci == &from->base_ci)); */
    if (!((from->status == LUA_YIELD) || 
            (from->status == 0 && from->ci == &from->base_ci)))
        luaG_runerror(L,"attempt to fork unforkable coroutine");
    lua_unlock(L);
    to = lua_newthread(L);
    lua_lock(to);
    { // Copy stack slots
        printf("Copy stack\n");
        TValue *f, *t;
        luaD_reallocstack(to, from->stacksize);
        for (f = from->stack, t = to->stack; f < from->top; f++, t++)
            setobjs2s(to, t, f);
        to->top = t;
        for (; f < from->ci->top; f++, t++)
            setnilvalue(t);
    }
    { // Copy frames
        printf("Copy frame\n");
        CallInfo *ci, *nci;
        for (ci = &from->base_ci; ci != from->ci; ci = ci->next) {
            nci = luaE_extendCI(to);
            // nci := ci
            nci->func = (ci->func - from->stack) + to->stack;
            nci->top = (ci->top - from->stack) + to->stack;
            nci->nresults = ci->nresults;
            /* t->u.c.k = f->u.c.k; */
            /* t->u.c.old_errfunc = f->u.c.errfunc; */
            /* t->u.c.ctx = f->u.c.ctx; */
            /* t->u.l.savedpc = f->u.l.savedpc; */
            /* t->u.l.trap = f->u.l.trap; */
            /* t->u.l.nextraargs = f->u.l.nextraargs; */
            nci->u = ci->u;
            nci->extra = ci->extra;
            /* nci->u2 = ci->u2; */
            nci->callstatus = ci->callstatus;
        }
        // to->ci = nci;
        to->ci = from->ci;
    }
    { // Copy misc
        printf("Copy misc status is %d,%d\n",from->status,to->status);
        to->nny = from->nny;
        to->status = from->status;
        to->oldpc = from->oldpc;
    }
    lua_unlock(to);
    return to;
}

