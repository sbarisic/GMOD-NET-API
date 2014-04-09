#include "stdafx.h"

typedef void (*NewSpewOutFunc)(SpewType_t T, const tchar* S, int R, int G, int B, int A);
static DWORD SpewThreadID;
static SpewOutputFunc_t OldSpewOutputFunc = NULL;
static NewSpewOutFunc NewSpewOutputFunc = NULL;
static int InsideSpew = 0;

//int glua_dump_writer_native(lua_State *L, const void* p, size_t sz, void* ud);

namespace GarrysMod {
	public enum class DumpResult : int {
		EXCEPTION_OCCURED = -2,
		NO_DUMP_FUNCTION = -1,
		OKAY = 0,
		FAILURE = 1
	};
}

