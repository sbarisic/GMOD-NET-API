#ifndef LUA_SHARED_H
#define LUA_SHARED_H

#define LUA_API __declspec(dllimport)
#define LUA GarrysMod::lua_State *L

// TODO: Place all the lua_shared.dll function imports here?

//LUA_API int luaL_loadstring(LUA, const char *s);
//LUA_API void lua_call(LUA, int nargs, int nresults);

#endif