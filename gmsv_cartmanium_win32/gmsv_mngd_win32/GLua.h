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
	public ref class LuaState {
	public:
		LuaState(lua_State* L);
		LuaState(IntPtr ^IPtr);
		lua_State* ToLuaState();
	};

	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	public delegate int GFunc(LuaState^ L);

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
		 static wchar_t* CharToLPCWSTR(const char* charArray) {
			wchar_t* wString = new wchar_t[4096];
			MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
			return wString;
		}

	public:
		typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

		 template <typename T> static T* GetInterface(LPCWSTR DllName, const char* IName) {
			auto MHandle = GetModuleHandle(DllName);
			auto CInt = rcast<CreateInterfaceFn>(GetProcAddress(MHandle, "CreateInterface"));
			return rcast<T*>(CInt(IName, nullptr));
		}

#define CSTR(N) const char* N = (const char*)(void*)Marshal::StringToHGlobalAnsi( STR_##N )
//#define DSTR(N) Marshal::FreeHGlobal(System::IntPtr((void*) N ))
#define DSTR(N) free((void*) N )
#define RSTR(N) gcnew System::String( N )
#define params ...

		generic<typename T> static T GetInterfaceInDll(System::String^ STR_DllName, System::String^ STR_InterfaceName) {
			CSTR(DllName);
			CSTR(InterfaceName);
			LPCWSTR wDllName = CharToLPCWSTR(DllName);

			auto MHandle = GetModuleHandle(wDllName);
			auto CInt = rcast<CreateInterfaceFn>(GetProcAddress(MHandle, "CreateInterface"));
			T Interf;

			try {
				Interf = rcast<T>(CInt(InterfaceName, nullptr));
			} catch(...) {
			}

			DSTR(DllName);
			DSTR(InterfaceName);
			DSTR(wDllName);
			return Interf;
		}
	};
}