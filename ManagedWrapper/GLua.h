#include "stdafx.h"
#include "Resource.h"

#define Surface vgui::ISurface
#define rcast reinterpret_cast

using namespace System::Runtime::InteropServices;
using namespace System::Net;
using namespace System;

namespace GarrysMod {
#define ToCFunc(GF) ((lua_CFunction)Marshal::GetFunctionPointerForDelegate(GF).ToPointer())

	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	public delegate int GFunc(IntPtr L);

	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	public delegate void GSpewOutputFunc(int T, String^ Str, int R, int G, int B, int A);

	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	public delegate int GLuaWriter(IntPtr L, IntPtr Ptr, size_t Size, IntPtr Userdata);

	namespace Lua {
		public enum class Index : int {
			REGISTRY = -10000,
			ENVIRONMENT = -10001,
			GLOBAL = -10002
		};
	}

	public ref class ManagedWrapper {
	public:
		static initonly String ^VERSION = gcnew String(__VERSION);
		static initonly int MAJOR = __MAJOR;
		static initonly int MINOR = __MINOR;
		static initonly int REVISION = __REVISION;
		static initonly int BUILD = __BUILD;
	};

	public ref class Source {
	public:
		typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

		static wchar_t* CharToLPCWSTR(const char* charArray);

		template <typename T> static T* GetInterface(LPCSTR DllName, const char* IName) {
			auto MHandle = GetModuleHandleA(DllName);
			auto CInt = rcast<CreateInterfaceFn>(GetProcAddress(MHandle, "CreateInterface"));
			return rcast<T*>(CInt(IName, nullptr));
		}

		generic<typename T> static T GetInterfaceInDll(String^ STR_DllName, String^ STR_InterfaceName);
		static const tchar* StrToTchar(String ^STR_S);
	};
}