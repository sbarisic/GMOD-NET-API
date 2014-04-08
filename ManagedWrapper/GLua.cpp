#include "stdafx.h"

namespace GarrysMod {
	wchar_t* Source::CharToLPCWSTR(const char* charArray) {
		wchar_t* wString = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
		return wString;
	}

	generic<typename T> T Source::GetInterfaceInDll(System::String^ STR_DllName, System::String^ STR_InterfaceName) {
		CSTR(InterfaceName);
		auto wDllName = StrToTchar(STR_DllName);

		auto MHandle = GetModuleHandle(wDllName);
		auto CInt = rcast<CreateInterfaceFn>(GetProcAddress(MHandle, "CreateInterface"));
		T Interf;

		try {
			Interf = rcast<T>(CInt(InterfaceName, nullptr));
		} catch(...) {
		}

		DSTR(InterfaceName);
		DSTR(wDllName);
		return Interf;
	}

	const tchar* Source::StrToTchar(System::String ^STR_S){
		CSTR(S);
		auto Str = CharToLPCWSTR(S);
#ifdef _UNICODE
		DSTR(S);
		return Str;
#else
		return S;
#endif
	}
}