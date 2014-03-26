// This file has been generated by Cartman300's WrapperGenerator

static void gluaL_register(LuaState^ LS, System::String ^STR_libname, const luaL_Reg *LS->ToLuaState()) {
	CSTR(libname);
	luaL_register(LS->ToLuaState(), libname, LS->ToLuaState());
	DSTR(libname);
}

static int gluaL_getmetafield(LuaState^ LS, int obj, System::String ^STR_e) {
	CSTR(e);
	auto RET = luaL_getmetafield(LS->ToLuaState(), obj, e);
	DSTR(e);
	return RET;
}

static int gluaL_callmeta(LuaState^ LS, int obj, System::String ^STR_e) {
	CSTR(e);
	auto RET = luaL_callmeta(LS->ToLuaState(), obj, e);
	DSTR(e);
	return RET;
}

static int gluaL_typerror(LuaState^ LS, int narg, System::String ^STR_tname) {
	CSTR(tname);
	auto RET = luaL_typerror(LS->ToLuaState(), narg, tname);
	DSTR(tname);
	return RET;
}

static int gluaL_argerror(LuaState^ LS, int numarg, System::String ^STR_extramsg) {
	CSTR(extramsg);
	auto RET = luaL_argerror(LS->ToLuaState(), numarg, extramsg);
	DSTR(extramsg);
	return RET;
}

static System::String ^gluaL_checklstring(LuaState^ LS, int numArg, size_t *LS->ToLuaState()) {
	return RSTR(luaL_checklstring(LS->ToLuaState(), numArg, LS->ToLuaState()));
}

static System::String ^gluaL_optlstring(LuaState^ LS, int numArg, System::String ^STR_def, size_t *LS->ToLuaState()) {
	CSTR(def);
	const char* RET = luaL_optlstring(LS->ToLuaState(), numArg, def, LS->ToLuaState());
	DSTR(def);
	return RSTR(RET);
}

static lua_Number gluaL_checknumber(LuaState^ LS, int numArg) {
	return luaL_checknumber(LS->ToLuaState(), numArg);
}

static lua_Number gluaL_optnumber(LuaState^ LS, int nArg, lua_Number def) {
	return luaL_optnumber(LS->ToLuaState(), nArg, def);
}

static lua_Integer gluaL_checkinteger(LuaState^ LS, int numArg) {
	return luaL_checkinteger(LS->ToLuaState(), numArg);
}

static lua_Integer gluaL_optinteger(LuaState^ LS, int nArg, lua_Integer def) {
	return luaL_optinteger(LS->ToLuaState(), nArg, def);
}

static void gluaL_checkstack(LuaState^ LS, int sz, System::String ^STR_msg) {
	CSTR(msg);
	luaL_checkstack(LS->ToLuaState(), sz, msg);
	DSTR(msg);
}

static void gluaL_checktype(LuaState^ LS, int narg, int t) {
	return luaL_checktype(LS->ToLuaState(), narg, t);
}

static void gluaL_checkany(LuaState^ LS, int narg) {
	return luaL_checkany(LS->ToLuaState(), narg);
}

static int gluaL_newmetatable(LuaState^ LS, System::String ^STR_tname) {
	CSTR(tname);
	auto RET = luaL_newmetatable(LS->ToLuaState(), tname);
	DSTR(tname);
	return RET;
}

static void *gluaL_checkudata(LuaState^ LS, int ud, System::String ^STR_tname) {
	CSTR(tname);
	void* RET = luaL_checkudata(LS->ToLuaState(), ud, tname);
	DSTR(tname);
	return RET;
}

static void gluaL_where(LuaState^ LS, int lvl) {
	return luaL_where(LS->ToLuaState(), lvl);
}

static int gluaL_error(LuaState^ LS, System::String ^STR_str) {
	CSTR(str);
	int R = luaL_error(LS->ToLuaState(), "%s", str);
	return R;
}

// FUNCTION gluaL_checkoption EXPUNGED

static int gluaL_ref(LuaState^ LS, int t) {
	return luaL_ref(LS->ToLuaState(), t);
}

static void gluaL_unref(LuaState^ LS, int t, int ref) {
	return luaL_unref(LS->ToLuaState(), t, ref);
}

static int gluaL_loadfile(LuaState^ LS, System::String ^STR_filename) {
	CSTR(filename);
	auto RET = luaL_loadfile(LS->ToLuaState(), filename);
	DSTR(filename);
	return RET;
}

static int gluaL_loadbuffer(LuaState^ LS, System::String ^STR_buff, size_t sz, System::String ^STR_name) {
	CSTR(buff); CSTR(name);
	auto RET = luaL_loadbuffer(LS->ToLuaState(), buff, sz, name);
	DSTR(buff); DSTR(name);
	return RET;
}

static int gluaL_loadstring(LuaState^ LS, System::String ^STR_s) {
	CSTR(s);
	auto RET = luaL_loadstring(LS->ToLuaState(), s);
	DSTR(s);
	return RET;
}

static LuaState^ gluaL_newstate() {
	return luaL_newstate();
}

static System::String ^gluaL_gsub(LuaState^ LS, System::String ^STR_s, System::String ^STR_p, System::String ^STR_r) {
	CSTR(s); CSTR(p); CSTR(r);
	const char* RET = luaL_gsub(LS->ToLuaState(), s, p, r);
	DSTR(s); DSTR(p); DSTR(r);
	return RSTR(RET);
}

static System::String ^gluaL_findtable(LuaState^ LS, int idx, System::String ^STR_fname, int szhint) {
	CSTR(fname);
	const char* RET =  luaL_findtable(LS->ToLuaState(), idx, fname, szhint);
	DSTR(fname);
	return RSTR(RET);
}

static void gluaL_buffinit(LuaState^ LS, luaL_Buffer *B) {
	return luaL_buffinit(LS->ToLuaState(), B);
}

static char *gluaL_prepbuffer(luaL_Buffer *B) {
	return luaL_prepbuffer(B);
}

static void gluaL_addlstring(luaL_Buffer *B, System::String ^STR_s, size_t LS->ToLuaState()) {
	CSTR(s);
	luaL_addlstring(B, s, LS->ToLuaState());
	DSTR(s);
}

static void gluaL_addstring(luaL_Buffer *B, System::String ^STR_s) {
	CSTR(s);
	luaL_addstring(B, s);
	DSTR(s);
}

static void gluaL_addvalue(luaL_Buffer *B) {
	return luaL_addvalue(B);
}

static void gluaL_pushresult(luaL_Buffer *B) {
	return luaL_pushresult(B);
}

static LuaState^ glua_newstate(lua_Alloc f, void *ud) {
	return lua_newstate(f, ud);
}

static void glua_close(LuaState^ LS) {
	return lua_close(LS->ToLuaState());
}

static LuaState^ glua_newthread(LuaState^ LS) {
	return lua_newthread(LS->ToLuaState());
}

static lua_CFunction glua_atpanic(LuaState^ LS, lua_CFunction panicf) {
	return lua_atpanic(LS->ToLuaState(), panicf);
}

static int glua_gettop(LuaState^ LS) {
	return lua_gettop(LS->ToLuaState());
}

static void glua_settop(LuaState^ LS, int idx) {
	return lua_settop(LS->ToLuaState(), idx);
}

static void glua_pushvalue(LuaState^ LS, int idx) {
	return lua_pushvalue(LS->ToLuaState(), idx);
}

static void glua_remove(LuaState^ LS, int idx) {
	return lua_remove(LS->ToLuaState(), idx);
}

static void glua_insert(LuaState^ LS, int idx) {
	return lua_insert(LS->ToLuaState(), idx);
}

static void glua_replace(LuaState^ LS, int idx) {
	return lua_replace(LS->ToLuaState(), idx);
}

static int glua_checkstack(LuaState^ LS, int sz) {
	return lua_checkstack(LS->ToLuaState(), sz);
}

static void glua_xmove(LuaState^ from, LuaState^ to, int n) {
	return lua_xmove(from, to, n);
}

static int glua_isnumber(LuaState^ LS, int idx) {
	return lua_isnumber(LS->ToLuaState(), idx);
}

static int glua_isstring(LuaState^ LS, int idx) {
	return lua_isstring(LS->ToLuaState(), idx);
}

static int glua_iscfunction(LuaState^ LS, int idx) {
	return lua_iscfunction(LS->ToLuaState(), idx);
}

static int glua_isuserdata(LuaState^ LS, int idx) {
	return lua_isuserdata(LS->ToLuaState(), idx);
}

static int glua_type(LuaState^ LS, int idx) {
	return lua_type(LS->ToLuaState(), idx);
}

static System::String ^glua_typename(LuaState^ LS, int tp) {
	return RSTR(lua_typename(LS->ToLuaState(), tp));
}

static int glua_equal(LuaState^ LS, int idx1, int idx2) {
	return lua_equal(LS->ToLuaState(), idx1, idx2);
}

static int glua_rawequal(LuaState^ LS, int idx1, int idx2) {
	return lua_rawequal(LS->ToLuaState(), idx1, idx2);
}

static int glua_lessthan(LuaState^ LS, int idx1, int idx2) {
	return lua_lessthan(LS->ToLuaState(), idx1, idx2);
}

static lua_Number glua_tonumber(LuaState^ LS, int idx) {
	return lua_tonumber(LS->ToLuaState(), idx);
}

static System::String ^glua_tostring(lua_State* LS->ToLuaState(), int idx) {
	return RSTR(lua_tostring(LS->ToLuaState(), idx));
}

static lua_Integer glua_tointeger(LuaState^ LS, int idx) {
	return lua_tointeger(LS->ToLuaState(), idx);
}

static int glua_toboolean(LuaState^ LS, int idx) {
	return lua_toboolean(LS->ToLuaState(), idx);
}

static System::String ^glua_tolstring(LuaState^ LS, int idx, size_t *len) {
	return RSTR(lua_tolstring(LS->ToLuaState(), idx, len));
}

static size_t glua_objlen(LuaState^ LS, int idx) {
	return lua_objlen(LS->ToLuaState(), idx);
}

static lua_CFunction glua_tocfunction(LuaState^ LS, int idx) {
	return lua_tocfunction(LS->ToLuaState(), idx);
}

static void *glua_touserdata(LuaState^ LS, int idx) {
	return lua_touserdata(LS->ToLuaState(), idx);
}

static LuaState^ glua_tothread(LuaState^ LS, int idx) {
	return lua_tothread(LS->ToLuaState(), idx);
}

static const void *glua_topointer(LuaState^ LS, int idx) {
	return lua_topointer(LS->ToLuaState(), idx);
}

static void glua_pushnil(LuaState^ LS) {
	return lua_pushnil(LS->ToLuaState());
}

static void glua_pushnumber(LuaState^ LS, lua_Number n) {
	return lua_pushnumber(LS->ToLuaState(), n);
}

static void glua_pushinteger(LuaState^ LS, lua_Integer n) {
	return lua_pushinteger(LS->ToLuaState(), n);
}

static void glua_pushlstring(LuaState^ LS, System::String ^STR_s, size_t LS->ToLuaState()) {
	CSTR(s);
	lua_pushlstring(LS->ToLuaState(), s, LS->ToLuaState());
	DSTR(s);
}

static void glua_pushstring(LuaState^ LS, System::String ^STR_s) {
	CSTR(s);
	lua_pushstring(LS->ToLuaState(), s);
	DSTR(s);
}

static System::String ^glua_pushvfstring(LuaState^ LS, System::String ^STR_fmt, va_list argp) {
	CSTR(fmt);
	auto RET = lua_pushvfstring(LS->ToLuaState(), fmt, argp);
	DSTR(fmt);
	return RSTR(RET);
}

static void glua_pushfstring(LuaState^ LS, System::String ^STR_fmt, params array<System::Object^> ^Args) {
	System::String ^STR_format = System::String::Format(STR_fmt, Args);
	CSTR(format);
	lua_pushstring(LS->ToLuaState(), format);
	DSTR(format);
}

static void glua_pushcclosure(LuaState^ LS, lua_CFunction fn, int n) {
	return lua_pushcclosure(LS->ToLuaState(), fn, n);
}

static void glua_pushboolean(LuaState^ LS, int b) {
	return lua_pushboolean(LS->ToLuaState(), b);
}

static void glua_pushlightuserdata(LuaState^ LS, void *p) {
	return lua_pushlightuserdata(LS->ToLuaState(), p);
}

static int glua_pushthread(LuaState^ LS) {
	return lua_pushthread(LS->ToLuaState());
}

static void glua_gettable(LuaState^ LS, int idx) {
	return lua_gettable(LS->ToLuaState(), idx);
}

static void glua_getfield(LuaState^ LS, int idx, System::String ^STR_k) {
	CSTR(k);
	lua_getfield(LS->ToLuaState(), idx, k);
	DSTR(k);
}

static void glua_rawget(LuaState^ LS, int idx) {
	return lua_rawget(LS->ToLuaState(), idx);
}

static void glua_rawgeti(LuaState^ LS, int idx, int n) {
	return lua_rawgeti(LS->ToLuaState(), idx, n);
}

static void glua_createtable(LuaState^ LS, int narr, int nrec) {
	return lua_createtable(LS->ToLuaState(), narr, nrec);
}

static void *glua_newuserdata(LuaState^ LS, size_t sz) {
	return lua_newuserdata(LS->ToLuaState(), sz);
}

static int glua_getmetatable(LuaState^ LS, int objindex) {
	return lua_getmetatable(LS->ToLuaState(), objindex);
}

static void glua_getfenv(LuaState^ LS, int idx) {
	return lua_getfenv(LS->ToLuaState(), idx);
}

static void glua_settable(LuaState^ LS, int idx) {
	return lua_settable(LS->ToLuaState(), idx);
}

static void glua_setfield(LuaState^ LS, int idx, System::String ^STR_k) {
	CSTR(k);
	lua_setfield(LS->ToLuaState(), idx, k);
	DSTR(k);
}

static void glua_rawset(LuaState^ LS, int idx) {
	return lua_rawset(LS->ToLuaState(), idx);
}

static void glua_rawseti(LuaState^ LS, int idx, int n) {
	return lua_rawseti(LS->ToLuaState(), idx, n);
}

static int glua_setmetatable(LuaState^ LS, int objindex) {
	return lua_setmetatable(LS->ToLuaState(), objindex);
}

static int glua_setfenv(LuaState^ LS, int idx) {
	return lua_setfenv(LS->ToLuaState(), idx);
}

static void glua_call(LuaState^ LS, int nargs, int nresults) {
	return lua_call(LS->ToLuaState(), nargs, nresults);
}

static int glua_pcall(LuaState^ LS, int nargs, int nresults, int errfunc) {
	return lua_pcall(LS->ToLuaState(), nargs, nresults, errfunc);
}

static int glua_cpcall(LuaState^ LS, lua_CFunction func, void *ud) {
	return lua_cpcall(LS->ToLuaState(), func, ud);
}

static int glua_load(LuaState^ LS, lua_Reader reader, void *dt, System::String ^STR_chunkname) {
	CSTR(chunkname);
	auto RET = lua_load(LS->ToLuaState(), reader, dt, chunkname);
	DSTR(chunkname);
	return RET;
}

static int glua_dump(LuaState^ LS, lua_Writer writer, void *data) {
	return lua_dump(LS->ToLuaState(), writer, data);
}

static int glua_yield(LuaState^ LS, int nresults) {
	return lua_yield(LS->ToLuaState(), nresults);
}

/* // FUNCTION glua_resume EXPUNGED
static int glua_resume(LuaState^ LS, int narg) {
	return lua_resume(LS->ToLuaState(), narg);
}
*/

static int glua_status(LuaState^ LS) {
	return lua_status(LS->ToLuaState());
}

static int glua_gc(LuaState^ LS, int what, int data) {
	return lua_gc(LS->ToLuaState(), what, data);
}

static int glua_error(LuaState^ LS) {
	return lua_error(LS->ToLuaState());
}

static int glua_next(LuaState^ LS, int idx) {
	return lua_next(LS->ToLuaState(), idx);
}

static void glua_concat(LuaState^ LS, int n) {
	return lua_concat(LS->ToLuaState(), n);
}

static lua_Alloc glua_getallocf(LuaState^ LS, void **ud) {
	return lua_getallocf(LS->ToLuaState(), ud);
}

static void glua_setallocf(LuaState^ LS, lua_Alloc f, void *ud) {
	return lua_setallocf(LS->ToLuaState(), f, ud);
}

/* // FUNCTION glua_setlevel EXPUNGED
static void glua_setlevel(LuaState^ from, LuaState^ to) {
	return lua_setlevel(from, to);
}
*/

static int glua_getstack(LuaState^ LS, int level, lua_Debug *ar) {
	return lua_getstack(LS->ToLuaState(), level, ar);
}

static int glua_getinfo(LuaState^ LS, System::String ^STR_what, lua_Debug *ar) {
	CSTR(what);
	auto RET = lua_getinfo(LS->ToLuaState(), what, ar);
	DSTR(what);
	return RET;
}

static System::String ^glua_getlocal(LuaState^ LS, const lua_Debug *ar, int n) {
	return RSTR(lua_getlocal(LS->ToLuaState(), ar, n));
}

static System::String ^glua_setlocal(LuaState^ LS, const lua_Debug *ar, int n) {
	return RSTR(lua_setlocal(LS->ToLuaState(), ar, n));
}

static System::String ^glua_getupvalue(LuaState^ LS, int funcindex, int n) {
	return RSTR(lua_getupvalue(LS->ToLuaState(), funcindex, n));
}

static System::String ^glua_setupvalue(LuaState^ LS, int funcindex, int n) {
	return RSTR(lua_setupvalue(LS->ToLuaState(), funcindex, n));
}

static int glua_sethook(LuaState^ LS, lua_Hook func, int mask, int count) {
	return lua_sethook(LS->ToLuaState(), func, mask, count);
}

static lua_Hook glua_gethook(LuaState^ LS) {
	return lua_gethook(LS->ToLuaState());
}

static int glua_gethookmask(LuaState^ LS) {
	return lua_gethookmask(LS->ToLuaState());
}

static int glua_gethookcount(LuaState^ LS) {
	return lua_gethookcount(LS->ToLuaState());
}