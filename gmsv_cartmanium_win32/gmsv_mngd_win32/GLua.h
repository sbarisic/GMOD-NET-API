#pragma once

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}
#include <LuaExtended.h>
#define RESOURCE_H
#include "resource.h"
#undef RESOURCE_H

#include <Windows.h>
#include <vgui\ISurface.h>
#include <Color.h>

#include "gISurface.h"
#include "gSteamAPI.h"
#include <vgui\IVGui.h>

#using <System.dll>

#define Surface vgui::ISurface
#define rcast reinterpret_cast

using namespace System::Runtime::InteropServices;
using namespace System::Net;

namespace GarrysMod {
	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	public delegate int GFunc(lua_State *L);

	namespace Lua {
		public enum class Index : int {
			REGISTRY = -10000,
			ENVIRONMENT = -10001,
			GLOBAL = -10002
		};
	}

	public ref class ManagedWrapper {
	public:
		static initonly System::String ^VERSION = gcnew System::String(__VERSION);
		static initonly int MAJOR = __MAJOR;
		static initonly int MINOR = __MINOR;
		static initonly int REVISION = __REVISION;
		static initonly int BUILD = __BUILD;
	};

	public ref class Source {
	private:
		typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

	public:
		 template <typename T> static T* GetInterface(LPCWSTR DllName, const char* IName) {
			auto MHandle = GetModuleHandle(DllName);
			auto CInt = rcast<CreateInterfaceFn>(GetProcAddress(MHandle, "CreateInterface"));
			return rcast<T*>(CInt(IName, nullptr));
		}
	};
}

#define CSTR(N) const char* N = (const char*)(void*)Marshal::StringToHGlobalAnsi( STR_##N )
//#define DSTR(N) Marshal::FreeHGlobal(System::IntPtr((void*) N ))
#define DSTR(N) free((void*) N )
#define RSTR(N) gcnew System::String( N )