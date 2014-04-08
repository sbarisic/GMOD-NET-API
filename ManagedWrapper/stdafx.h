#pragma once

#define STDAFX_H

// Managed dlls
#using <System.dll>
#using <mscorlib.dll>
#using <System.Windows.Forms.dll>

// Libs
#pragma comment(lib, "lua_shared.lib")
#pragma comment(lib, "lua51.lib")
#pragma comment(lib, "tier0.lib")
#pragma comment(lib, "vstdlib.lib")
#pragma comment(lib, "steam_api.lib")

// Source SDK headers
#include <tier0\dbg.h>
#include <vstdlib\vstdlib.h>
#include <vgui\ISurface.h>
#include <Color.h>
#include <vgui\IVGui.h>
#include <steam\steam_api.h>

#include <Windows.h>

// Headers
#include "ManagedWrapper.h"
#include "GISurface.h"
#include "GSteamAPI.h"
#include "gColor.h"
#include "GLua.h"

// Lua
extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}
#include <LuaExtended.h>

// Definitions
#define or ||
#define and &&
#define not !
#define params ...

#define CSTR(N) const char* N = (const char*)(void*)Marshal::StringToHGlobalAnsi( STR_##N )
//#define DSTR(N) Marshal::FreeHGlobal(System::IntPtr((void*) N ))
#define DSTR(N) free((void*) N )
#define RSTR(N) gcnew String( N )
#define ToLuaState(LL) ((lua_State*)LL.ToPointer())
#define ToLuaStateExt(LL) ((ILuaExtended*)ToLuaState(LL)->luabase)

#undef STDAFX_H