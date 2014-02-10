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

#using <System.dll>

#define Surface vgui::ISurface

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
		static initonly System::String ^BINARY_LINK = gcnew System::String("https://github.com/cartman300/GMOD-NET-API/raw/master/bin/ManagedWrapper.dll");
		static initonly System::String ^VERSION_LINK = gcnew System::String("https://github.com/cartman300/GMOD-NET-API/raw/master/bin/Version.txt");
		static initonly System::String ^VERSION = gcnew System::String(__VERSION);
		static initonly int MAJOR = __MAJOR;
		static initonly int MINOR = __MINOR;
		static initonly int REVISION = __REVISION;
		static initonly int BUILD = __BUILD;
	};

	public ref class Source {
	private:
		static HMODULE SurfaceDll;
		static CreateInterfaceFn _CreateInterface;

		static HMODULE GetSurfaceDll() {
			return GetModuleHandle(L"vguimatsurface.dll");
		}

		typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

		static CreateInterfaceFn GetCreateInterface() {
			return reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetSurfaceDll(), "CreateInterface"));
		}
	public:
		static gISurface ^GetSurface() {
			return gcnew gISurface(reinterpret_cast<Surface*>(GetCreateInterface()(VGUI_SURFACE_INTERFACE_VERSION, nullptr)));
		}
	};
}

#define CSTR(N) const char* N = (const char*)(void*)Marshal::StringToHGlobalAnsi( STR_##N )
#define DSTR(N) Marshal::FreeHGlobal(System::IntPtr((void*) N ))
#define RSTR(N) gcnew System::String( N )