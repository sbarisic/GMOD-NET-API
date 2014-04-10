#include "stdafx.h"

#ifdef WRAPPERS_INCLUDE

__static void gluaL_register(LuaStateType LPtr, System::String ^STR_libname, const luaL_Reg *l) {
	CSTR(libname);
	luaL_register(ToLuaState(LPtr), libname, l);
	DSTR(libname);
}

#define GLUAOPEN_E(N) __static void gluaopen_##N (LuaStateType LPtr){ luaopen_##N (ToLuaState(LPtr)); }
#define GLUAOPEN(M) GLUAOPEN_E(M)

GLUAOPEN(base)
GLUAOPEN(debug)
//GLUAOPEN(io)		// Y U NO EXIST
GLUAOPEN(math)
GLUAOPEN(os)
GLUAOPEN(package)
GLUAOPEN(string)
GLUAOPEN(table)

__static int gluaL_getmetafield(LuaStateType LPtr, int obj, System::String ^STR_e) {
	CSTR(e);
	auto RET = luaL_getmetafield(ToLuaState(LPtr), obj, e);
	DSTR(e);
	return RET;
}

__static int gluaL_callmeta(LuaStateType LPtr, int obj, System::String ^STR_e) {
	CSTR(e);
	auto RET = luaL_callmeta(ToLuaState(LPtr), obj, e);
	DSTR(e);
	return RET;
}

__static int gluaL_typerror(LuaStateType LPtr, int narg, System::String ^STR_tname) {
	CSTR(tname);
	auto RET = luaL_typerror(ToLuaState(LPtr), narg, tname);
	DSTR(tname);
	return RET;
}

__static int gluaL_argerror(LuaStateType LPtr, int numarg, System::String ^STR_extramsg) {
	CSTR(extramsg);
	auto RET = luaL_argerror(ToLuaState(LPtr), numarg, extramsg);
	DSTR(extramsg);
	return RET;
}

__static System::String ^gluaL_checklstring(LuaStateType LPtr, int numArg, size_t *l) {
	return RSTR(luaL_checklstring(ToLuaState(LPtr), numArg, l));
}

__static System::String ^gluaL_optlstring(LuaStateType LPtr, int numArg, System::String ^STR_def, size_t *l) {
	CSTR(def);
	const char* RET = luaL_optlstring(ToLuaState(LPtr), numArg, def, l);
	DSTR(def);
	return RSTR(RET);
}

__static lua_Number gluaL_checknumber(LuaStateType LPtr, int numArg) {
	return luaL_checknumber(ToLuaState(LPtr), numArg);
}

__static lua_Number gluaL_optnumber(LuaStateType LPtr, int nArg, lua_Number def) {
	return luaL_optnumber(ToLuaState(LPtr), nArg, def);
}

__static lua_Integer gluaL_checkinteger(LuaStateType LPtr, int numArg) {
	return luaL_checkinteger(ToLuaState(LPtr), numArg);
}

__static lua_Integer gluaL_optinteger(LuaStateType LPtr, int nArg, lua_Integer def) {
	return luaL_optinteger(ToLuaState(LPtr), nArg, def);
}

__static void gluaL_checkstack(LuaStateType LPtr, int sz, System::String ^STR_msg) {
	CSTR(msg);
	luaL_checkstack(ToLuaState(LPtr), sz, msg);
	DSTR(msg);
}

__static void gluaL_checktype(LuaStateType LPtr, int narg, int t) {
	return luaL_checktype(ToLuaState(LPtr), narg, t);
}

__static void gluaL_checkany(LuaStateType LPtr, int narg) {
	return luaL_checkany(ToLuaState(LPtr), narg);
}

__static int gluaL_newmetatable(LuaStateType LPtr, System::String ^STR_tname) {
	CSTR(tname);
	auto RET = luaL_newmetatable(ToLuaState(LPtr), tname);
	DSTR(tname);
	return RET;
}

__static void *gluaL_checkudata(LuaStateType LPtr, int ud, System::String ^STR_tname) {
	CSTR(tname);
	void* RET = luaL_checkudata(ToLuaState(LPtr), ud, tname);
	DSTR(tname);
	return RET;
}

__static void gluaL_where(LuaStateType LPtr, int lvl) {
	return luaL_where(ToLuaState(LPtr), lvl);
}

__static int gluaL_error(LuaStateType LPtr, System::String ^STR_str) {
	CSTR(str);
	int R = luaL_error(ToLuaState(LPtr), "%s", str);
	return R;
}

// FUNCTION gluaL_checkoption EXPUNGED

__static int gluaL_ref(LuaStateType LPtr, int t) {
	return luaL_ref(ToLuaState(LPtr), t);
}

__static void gluaL_unref(LuaStateType LPtr, int t, int ref) {
	return luaL_unref(ToLuaState(LPtr), t, ref);
}

__static int gluaL_loadfile(LuaStateType LPtr, System::String ^STR_filename) {
	CSTR(filename);
	auto RET = luaL_loadfile(ToLuaState(LPtr), filename);
	DSTR(filename);
	return RET;
}

__static int gluaL_loadbuffer(LuaStateType LPtr, System::String ^STR_buff, size_t sz, System::String ^STR_name) {
	CSTR(buff); CSTR(name);
	auto RET = luaL_loadbuffer(ToLuaState(LPtr), buff, sz, name);
	DSTR(buff); DSTR(name);
	return RET;
}

__static int gluaL_loadstring(LuaStateType LPtr, System::String ^STR_s) {
	CSTR(s);
	auto RET = luaL_loadstring(ToLuaState(LPtr), s);
	DSTR(s);
	return RET;
}

__static lua_State* gluaL_newstate() {
	return luaL_newstate();
}

__static System::String ^gluaL_gsub(LuaStateType LPtr, System::String ^STR_s, System::String ^STR_p, System::String ^STR_r) {
	CSTR(s); CSTR(p); CSTR(r);
	const char* RET = luaL_gsub(ToLuaState(LPtr), s, p, r);
	DSTR(s); DSTR(p); DSTR(r);
	return RSTR(RET);
}

__static System::String ^gluaL_findtable(LuaStateType LPtr, int idx, System::String ^STR_fname, int szhint) {
	CSTR(fname);
	const char* RET =  luaL_findtable(ToLuaState(LPtr), idx, fname, szhint);
	DSTR(fname);
	return RSTR(RET);
}

__static void gluaL_buffinit(LuaStateType LPtr, luaL_Buffer *B) {
	return luaL_buffinit(ToLuaState(LPtr), B);
}

__static char *gluaL_prepbuffer(luaL_Buffer *B) {
	return luaL_prepbuffer(B);
}

__static void gluaL_addlstring(luaL_Buffer *B, System::String ^STR_s, size_t l) {
	CSTR(s);
	luaL_addlstring(B, s, l);
	DSTR(s);
}

__static void gluaL_addstring(luaL_Buffer *B, System::String ^STR_s) {
	CSTR(s);
	luaL_addstring(B, s);
	DSTR(s);
}

__static void gluaL_addvalue(luaL_Buffer *B) {
	return luaL_addvalue(B);
}

__static void gluaL_pushresult(luaL_Buffer *B) {
	return luaL_pushresult(B);
}

__static lua_State* glua_newstate(lua_Alloc f, void *ud) {
	return lua_newstate(f, ud);
}

__static void glua_close(LuaStateType LPtr) {
	return lua_close(ToLuaState(LPtr));
}

__static lua_State* glua_newthread(LuaStateType LPtr) {
	return lua_newthread(ToLuaState(LPtr));
}

__static lua_CFunction glua_atpanic(LuaStateType LPtr, lua_CFunction panicf) {
	return lua_atpanic(ToLuaState(LPtr), panicf);
}

__static int glua_gettop(LuaStateType LPtr) {
	return lua_gettop(ToLuaState(LPtr));
}

__static void glua_settop(LuaStateType LPtr, int idx) {
	return lua_settop(ToLuaState(LPtr), idx);
}

__static void glua_pushvalue(LuaStateType LPtr, int idx) {
	return lua_pushvalue(ToLuaState(LPtr), idx);
}

__static void glua_remove(LuaStateType LPtr, int idx) {
	return lua_remove(ToLuaState(LPtr), idx);
}

__static void glua_insert(LuaStateType LPtr, int idx) {
	return lua_insert(ToLuaState(LPtr), idx);
}

__static void glua_replace(LuaStateType LPtr, int idx) {
	return lua_replace(ToLuaState(LPtr), idx);
}

__static int glua_checkstack(LuaStateType LPtr, int sz) {
	return lua_checkstack(ToLuaState(LPtr), sz);
}

__static void glua_xmove(lua_State* from, lua_State* to, int n) {
	return lua_xmove(from, to, n);
}

__static int glua_isnumber(LuaStateType LPtr, int idx) {
	return lua_isnumber(ToLuaState(LPtr), idx);
}

__static int glua_isstring(LuaStateType LPtr, int idx) {
	return lua_isstring(ToLuaState(LPtr), idx);
}

__static int glua_iscfunction(LuaStateType LPtr, int idx) {
	return lua_iscfunction(ToLuaState(LPtr), idx);
}

__static int glua_isuserdata(LuaStateType LPtr, int idx) {
	return lua_isuserdata(ToLuaState(LPtr), idx);
}

__static int glua_type(LuaStateType LPtr, int idx) {
	return lua_type(ToLuaState(LPtr), idx);
}

__static System::String ^glua_typename(LuaStateType LPtr, int tp) {
	return RSTR(lua_typename(ToLuaState(LPtr), tp));
}

__static int glua_equal(LuaStateType LPtr, int idx1, int idx2) {
	return lua_equal(ToLuaState(LPtr), idx1, idx2);
}

__static int glua_rawequal(LuaStateType LPtr, int idx1, int idx2) {
	return lua_rawequal(ToLuaState(LPtr), idx1, idx2);
}

__static int glua_lessthan(LuaStateType LPtr, int idx1, int idx2) {
	return lua_lessthan(ToLuaState(LPtr), idx1, idx2);
}

__static lua_Number glua_tonumber(LuaStateType LPtr, int idx) {
	return lua_tonumber(ToLuaState(LPtr), idx);
}

__static System::String ^glua_tostring(LuaStateType LPtr, int idx) {
	return RSTR(lua_tostring(ToLuaState(LPtr), idx));
}

__static lua_Integer glua_tointeger(LuaStateType LPtr, int idx) {
	return lua_tointeger(ToLuaState(LPtr), idx);
}

__static int glua_toboolean(LuaStateType LPtr, int idx) {
	return lua_toboolean(ToLuaState(LPtr), idx);
}

__static System::String ^glua_tolstring(LuaStateType LPtr, int idx, size_t *len) {
	return RSTR(lua_tolstring(ToLuaState(LPtr), idx, len));
}

__static size_t glua_objlen(LuaStateType LPtr, int idx) {
	return lua_objlen(ToLuaState(LPtr), idx);
}

__static lua_CFunction glua_tocfunction(LuaStateType LPtr, int idx) {
	return lua_tocfunction(ToLuaState(LPtr), idx);
}

__static void *glua_touserdata(LuaStateType LPtr, int idx) {
	return lua_touserdata(ToLuaState(LPtr), idx);
}

__static lua_State* glua_tothread(LuaStateType LPtr, int idx) {
	return lua_tothread(ToLuaState(LPtr), idx);
}

__static const void *glua_topointer(LuaStateType LPtr, int idx) {
	return lua_topointer(ToLuaState(LPtr), idx);
}

__static void glua_pushnil(LuaStateType LPtr) {
	return lua_pushnil(ToLuaState(LPtr));
}

__static void glua_pushnumber(LuaStateType LPtr, lua_Number n) {
	return lua_pushnumber(ToLuaState(LPtr), n);
}

__static void glua_pushinteger(LuaStateType LPtr, lua_Integer n) {
	return lua_pushinteger(ToLuaState(LPtr), n);
}

__static void glua_pushlstring(LuaStateType LPtr, System::String ^STR_s, size_t l) {
	CSTR(s);
	lua_pushlstring(ToLuaState(LPtr), s, l);
	DSTR(s);
}

__static void glua_pushstring(LuaStateType LPtr, System::String ^STR_s) {
	CSTR(s);
	lua_pushstring(ToLuaState(LPtr), s);
	DSTR(s);
}

__static System::String ^glua_pushvfstring(LuaStateType LPtr, System::String ^STR_fmt, va_list argp) {
	CSTR(fmt);
	auto RET = lua_pushvfstring(ToLuaState(LPtr), fmt, argp);
	DSTR(fmt);
	return RSTR(RET);
}

__static void glua_pushfstring(LuaStateType LPtr, System::String ^STR_fmt, params array<System::Object^> ^Args) {
	System::String ^STR_format = System::String::Format(STR_fmt, Args);
	CSTR(format);
	lua_pushstring(ToLuaState(LPtr), format);
	DSTR(format);
}

__static void glua_pushcclosure(LuaStateType LPtr, lua_CFunction fn, int n) {
	return lua_pushcclosure(ToLuaState(LPtr), fn, n);
}

__static void glua_pushboolean(LuaStateType LPtr, int b) {
	return lua_pushboolean(ToLuaState(LPtr), b);
}

__static void glua_pushlightuserdata(LuaStateType LPtr, void *p) {
	return lua_pushlightuserdata(ToLuaState(LPtr), p);
}

__static int glua_pushthread(LuaStateType LPtr) {
	return lua_pushthread(ToLuaState(LPtr));
}

__static void glua_gettable(LuaStateType LPtr, int idx) {
	return lua_gettable(ToLuaState(LPtr), idx);
}

__static void glua_getfield(LuaStateType LPtr, int idx, System::String ^STR_k) {
	CSTR(k);
	lua_getfield(ToLuaState(LPtr), idx, k);
	DSTR(k);
}

__static void glua_rawget(LuaStateType LPtr, int idx) {
	return lua_rawget(ToLuaState(LPtr), idx);
}

__static void glua_rawgeti(LuaStateType LPtr, int idx, int n) {
	return lua_rawgeti(ToLuaState(LPtr), idx, n);
}

__static void glua_createtable(LuaStateType LPtr, int narr, int nrec) {
	return lua_createtable(ToLuaState(LPtr), narr, nrec);
}

__static void *glua_newuserdata(LuaStateType LPtr, size_t sz) {
	return lua_newuserdata(ToLuaState(LPtr), sz);
}

__static int glua_getmetatable(LuaStateType LPtr, int objindex) {
	return lua_getmetatable(ToLuaState(LPtr), objindex);
}

__static void glua_getfenv(LuaStateType LPtr, int idx) {
	return lua_getfenv(ToLuaState(LPtr), idx);
}

__static void glua_settable(LuaStateType LPtr, int idx) {
	return lua_settable(ToLuaState(LPtr), idx);
}

__static void glua_setfield(LuaStateType LPtr, int idx, System::String ^STR_k) {
	CSTR(k);
	lua_setfield(ToLuaState(LPtr), idx, k);
	DSTR(k);
}

__static void glua_rawset(LuaStateType LPtr, int idx) {
	return lua_rawset(ToLuaState(LPtr), idx);
}

__static void glua_rawseti(LuaStateType LPtr, int idx, int n) {
	return lua_rawseti(ToLuaState(LPtr), idx, n);
}

__static int glua_setmetatable(LuaStateType LPtr, int objindex) {
	return lua_setmetatable(ToLuaState(LPtr), objindex);
}

__static int glua_setfenv(LuaStateType LPtr, int idx) {
	return lua_setfenv(ToLuaState(LPtr), idx);
}

__static void glua_call(LuaStateType LPtr, int nargs, int nresults) {
	return lua_call(ToLuaState(LPtr), nargs, nresults);
}

__static int glua_pcall(LuaStateType LPtr, int nargs, int nresults, int errfunc) {
	return lua_pcall(ToLuaState(LPtr), nargs, nresults, errfunc);
}

__static int glua_cpcall(LuaStateType LPtr, lua_CFunction func, void *ud) {
	return lua_cpcall(ToLuaState(LPtr), func, ud);
}

__static int glua_load(LuaStateType LPtr, lua_Reader reader, void *dt, System::String ^STR_chunkname) {
	CSTR(chunkname);
	auto RET = lua_load(ToLuaState(LPtr), reader, dt, chunkname);
	DSTR(chunkname);
	return RET;
}

__static int glua_dump(LuaStateType LPtr, lua_Writer writer, void *data) {
	return lua_dump(ToLuaState(LPtr), writer, data);
}

__static int glua_yield(LuaStateType LPtr, int nresults) {
	return lua_yield(ToLuaState(LPtr), nresults);
}

/* // FUNCTION glua_resume EXPUNGED
__static int glua_resume(LuaStateType LPtr, int narg) {
	return lua_resume(ToLuaState(LPtr), narg);
}
*/

__static int glua_status(LuaStateType LPtr) {
	return lua_status(ToLuaState(LPtr));
}

__static int glua_gc(LuaStateType LPtr, int what, int data) {
	return lua_gc(ToLuaState(LPtr), what, data);
}

__static int glua_error(LuaStateType LPtr) {
	return lua_error(ToLuaState(LPtr));
}

__static int glua_next(LuaStateType LPtr, int idx) {
	return lua_next(ToLuaState(LPtr), idx);
}

__static void glua_concat(LuaStateType LPtr, int n) {
	return lua_concat(ToLuaState(LPtr), n);
}

__static lua_Alloc glua_getallocf(LuaStateType LPtr, void **ud) {
	return lua_getallocf(ToLuaState(LPtr), ud);
}

__static void glua_setallocf(LuaStateType LPtr, lua_Alloc f, void *ud) {
	return lua_setallocf(ToLuaState(LPtr), f, ud);
}

/* // FUNCTION glua_setlevel EXPUNGED
__static void glua_setlevel(lua_State* from, lua_State* to) {
	return lua_setlevel(from, to);
}
*/

__static int glua_getstack(LuaStateType LPtr, int level, lua_Debug *ar) {
	return lua_getstack(ToLuaState(LPtr), level, ar);
}

__static int glua_getinfo(LuaStateType LPtr, System::String ^STR_what, lua_Debug *ar) {
	CSTR(what);
	auto RET = lua_getinfo(ToLuaState(LPtr), what, ar);
	DSTR(what);
	return RET;
}

__static System::String ^glua_getlocal(LuaStateType LPtr, const lua_Debug *ar, int n) {
	return RSTR(lua_getlocal(ToLuaState(LPtr), ar, n));
}

__static System::String ^glua_setlocal(LuaStateType LPtr, const lua_Debug *ar, int n) {
	return RSTR(lua_setlocal(ToLuaState(LPtr), ar, n));
}

__static System::String ^glua_getupvalue(LuaStateType LPtr, int funcindex, int n) {
	return RSTR(lua_getupvalue(ToLuaState(LPtr), funcindex, n));
}

__static System::String ^glua_setupvalue(LuaStateType LPtr, int funcindex, int n) {
	return RSTR(lua_setupvalue(ToLuaState(LPtr), funcindex, n));
}

__static int glua_sethook(LuaStateType LPtr, lua_Hook func, int mask, int count) {
	return lua_sethook(ToLuaState(LPtr), func, mask, count);
}

__static lua_Hook glua_gethook(LuaStateType LPtr) {
	return lua_gethook(ToLuaState(LPtr));
}

__static int glua_gethookmask(LuaStateType LPtr) {
	return lua_gethookmask(ToLuaState(LPtr));
}

__static int glua_gethookcount(LuaStateType LPtr) {
	return lua_gethookcount(ToLuaState(LPtr));
}

#endif