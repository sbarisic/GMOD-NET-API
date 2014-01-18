extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}
#include <LuaExtended.h>

using namespace System::Runtime::InteropServices;

namespace GarrysMod {
	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	public delegate int GFunc(lua_State* L);
}

#define or ||
#define and &&