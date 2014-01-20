extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}
#include <LuaExtended.h>

using namespace System::Runtime::InteropServices;

namespace GarrysMod {
	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	public delegate int GFunc(lua_State *L);
}

#define CSTR(N) const char* N = (const char*)(void*)Marshal::StringToHGlobalAnsi( STR_##N )
#define DSTR(N) Marshal::FreeHGlobal(System::IntPtr((void*) N ))
#define RSTR(N) gcnew System::String( N )