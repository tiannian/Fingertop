#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "llimits.h"
#include "lstate.h"

LUA_API lua_State *lua_clonethread(lua_State *L, lua_State *from) {
   lua_State *to;
   lua_lock(L);
   if (!(from->status == LUA_YIELD || (from->status == 0 && from->ci == from->base_ci)))
      luaG_runerror(L, "attempt to clone uncloneable coroutine");
   lua_unlock(L);
   to = lua_newthread(L);
   lua_lock(to);
   luaD_reallocstack(to, from->stacksize - EXTRA_STACK - 1);
   luaD_reallocCI(to, from->size_ci);

   {  /* Copy stack slots. */
      TValue *f, *t;

      for (f = from->stack, t = to->stack; f < from->top; f++, t++)
         setobjs2s(to, t, f);

      to->top = t;
      for (; f < from->ci->top; f++, t++)
         setnilvalue(t);
         to->base = (from->base - from->stack) + to->stack;
   }

   {  /* Copy frames. */
      CallInfo *f, *t;
      for (f = from->base_ci, t = to->base_ci; f <= from->ci; f++, t++) {
         t->base = (f->base - from->stack) + to->stack;
         t->func = (f->func - from->stack) + to->stack;
         t->top = (f->top - from->stack) + to->stack;
         t->nresults = f->nresults;
         t->savedpc = f->savedpc;
         t->tailcalls = f->tailcalls;   
      }

      to->ci = (from->ci - from->base_ci) + to->base_ci;
   }

   /* Copy misc fields. Hooks are deliberately not copied. */
   to->status = from->status;
   to->savedpc = from->savedpc;
   lua_unlock(to);
   setobj2n(L, gt(to), gt(from));
   return to;
}
