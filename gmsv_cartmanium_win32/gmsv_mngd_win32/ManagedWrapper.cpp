#pragma comment(lib, "lua_shared.lib")

#include "GLua.h"

#using <mscorlib.dll>

#define or ||
#define PRINT(P) Console::WriteLine(P)

#define MWRAPPER
#ifdef MWRAPPER

using namespace System;
using namespace GarrysMod::Lua;
using namespace System::Collections::Generic;

namespace GarrysMod {
	public ref class GLua {
	private:
		static bool SkipMetamethods = false; // Ugly hack

	public:
		ref class Utils {
		public:
			static bool PrintToConsole = true;

			static void print(IntPtr L, System::String ^S) {
				GLua::PushSpecial(L, GarrysMod::SPECIAL::GLOB);
				GLua::PushString(L, "print");
				GLua::GetTable(L, -2);
				GLua::PushString(L, S);
				GLua::Call(L, 1, 0);
				if (Utils::PrintToConsole)
					System::Console::WriteLine(S);

			}

			static void print(IntPtr L, System::String ^S, System::Boolean ToConsole) {
				auto oPTC = Utils::PrintToConsole; Utils::PrintToConsole = ToConsole;
				Utils::print(L, S);
				Utils::PrintToConsole = oPTC;
			}

			static void print(IntPtr L, System::String ^S, params array<Object^>^ VArgs) {
				Utils::print(L, System::String::Format(S, VArgs));
			}

			static int DoString(IntPtr L, System::String ^STR_S) {
				CSTR(S);
				int R = luaL_dostring(ToLuaState(L), S);
				DSTR(S);
				return R;
			}

			static ILuaExtended* ToExtended(ILuaBase* B) {
				return (ILuaExtended*)B;
			}

			static ILuaExtended* ToExtended(IntPtr L) {
				return (ILuaExtended*)ToLuaState(L)->luabase;
			}
		};

		ref class Keepalive {
		private:
			static Dictionary<System::String^, System::Object^> ^KADict = gcnew Dictionary<System::String^, System::Object^>();

			static void CheckName(System::String^ Name) {
				if (Keepalive::KADict->ContainsKey(Name))
					throw gcnew System::Exception(System::String::Format("Keepalive {0} exists!", Name));
			}
		public:
			static void Remove(System::String^ Name) {
				if (!Keepalive::KADict->ContainsKey(Name))
					throw gcnew System::Exception(System::String::Format("Keepalive {0} does not exist!", Name));
				Keepalive::KADict->Remove(Name);
			}

			static void AddList(System::String^ Name, List<GFunc^>^ GFuncList) {
				Keepalive::CheckName(Name);
				Keepalive::KADict->Add(Name, GFuncList);
			}

			static void AddObject(System::String^ Name, System::Object^ Obj) {
				Keepalive::CheckName(Name);
				Keepalive::KADict->Add(Name, Obj);
			}
		};

		static System::String ^GetTypeName(IntPtr B){
			return GLua::GetTypeName(B, GLua::GetType(B, 1));
		}

		static List<GFunc^> ^CreateLib(IntPtr L, System::Type ^Lib) {
			return CreateLib(L, Lib, true);
		}

		static List<GFunc^> ^CreateLib(IntPtr L, System::Type ^Lib, bool Keepalive) {
			auto RetL = gcnew List<GFunc^>();
			auto Methods = Lib->GetMethods();
			System::String ^TableName = Lib->Name;
			GLua::CreateGlobalTable(L, TableName);
			auto GFuncType = (gcnew GFunc(GLua::EmptyGFunc))->GetType();
			for each (auto MInfo in Methods) {
				if (MInfo->ReturnType == (1).GetType()) {
					auto Params = MInfo->GetParameters();
					if (Params->Length == 1 && Params[0]->ParameterType->FullName == "IntPtr") {
						GFunc ^Func = (GFunc^)System::Delegate::CreateDelegate(GFuncType, MInfo);
						RetL->Add(Func);
						if (SkipMetamethods && MInfo->Name->StartsWith("__")) {
							PushSpecial(L, GarrysMod::SPECIAL::GLOB);
							PushString(L, Lib->Name);
							GetTable(L, -2);
							if (glua_getmetatable(L, -1) == 0)
								glua_createtable(L, 0, 0);
							PushGFunction(L, Func);
							glua_setfield(L, -2, MInfo->Name);
							glua_setmetatable(L, -2);
							GLua::Pop(L, 1);
							continue;
						} 
						GLua::SetGlobalTableGFunc(L, TableName, MInfo->Name, Func);
					}
				}
			}

			if (Keepalive)
				GLua::Keepalive::AddList(Lib->Name, RetL);

			return RetL;
		}

		// Ugly hack begin.
		static List<GFunc^> ^CreateType(IntPtr L, System::Type ^Typ) {
			return CreateType(L, Typ, true);
		}

		static List<GFunc^> ^CreateType(IntPtr L, System::Type ^Typ, bool Keepalive) {
			SkipMetamethods = true;
			List<GFunc^> ^GFL = CreateLib(L, Typ, Keepalive);
			SkipMetamethods = false;
			return GFL;
		}
		// Ugly hack end.

#include "Wrappers.h"

		static bool IsClient(IntPtr L) {
			return Utils::ToExtended(L)->IsClient();
		}

		static bool IsServer(IntPtr L) {
			return Utils::ToExtended(L)->IsServer();
		}

		static bool IsMenu(IntPtr L) {
			ILuaExtended* Le = (ILuaExtended*)ToLuaState(L);
			lua_getfield(ToLuaState(L), LUA_GLOBALSINDEX, "render");
			bool Render = lua_type(ToLuaState(L), -1) == (int)Lua::Type::NIL;
			lua_getfield(ToLuaState(L), LUA_GLOBALSINDEX, "chat");
			bool Chat = lua_type(ToLuaState(L), -1) == (int)Lua::Type::NIL;
			lua_getfield(ToLuaState(L), LUA_GLOBALSINDEX, "cam");
			bool Cam = lua_type(ToLuaState(L), -1) == (int)Lua::Type::NIL;
			if ((GLua::IsClient(L) || GLua::IsServer(L)) && (Render || Chat || Cam))
				return true;
			return false;
		}

		static void Openlibs(IntPtr L) {
			luaL_openlibs(ToLuaState(L));
		}

		static void Shutdown(IntPtr L) {
			Utils::ToExtended(L)->Shutdown();
		}

		static void PushCFunction(IntPtr L, void* F) {
			ToLuaState(L)->luabase->PushCFunction((CFunc)F);
		}

		static void PushGFunction(IntPtr L, GFunc ^F) {
			GLua::PushCFunction(L, Marshal::GetFunctionPointerForDelegate(F).ToPointer());
		}
		
		static void CreateGlobalTable(IntPtr L, System::String ^S) {
			GLua::PushSpecial(L, GarrysMod::SPECIAL::GLOB);
			GLua::PushString(L, S);
			GLua::CreateTable(L);
			GLua::SetTable(L, -3);
		}

		static void SetGlobalTableGFunc(IntPtr L, System::String ^TableName, System::String ^FunctionName, GFunc ^F) {
			GLua::PushSpecial(L, GarrysMod::SPECIAL::GLOB);
			GLua::PushString(L, TableName);
			GLua::GetTable(L, -2);
			GLua::PushString(L, FunctionName);
			GLua::PushGFunction(L, F);
			GLua::SetTable(L, -3);
		}

		static int Top(IntPtr L) {
			return ToLuaState(L)->luabase->Top();
		}

		static void Push(IntPtr L, int StackPos) {
			ToLuaState(L)->luabase->Push(StackPos);
		}

		static void Pop(IntPtr L, int Amount) {
			ToLuaState(L)->luabase->Pop(Amount);
		}

		static void GetTable(IntPtr L, int StackPos) {
			ToLuaState(L)->luabase->GetTable(StackPos);
		}

		static void GetField(IntPtr L, int iStackPos, System::String ^strName) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			ToLuaState(L)->luabase->GetField(iStackPos, str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void SetField(IntPtr L, int iStackPos, System::String ^strName) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			ToLuaState(L)->luabase->SetField(iStackPos, str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void CreateTable(IntPtr L) {
			ToLuaState(L)->luabase->CreateTable();
		}

		static void GetTableVal(IntPtr L, params array<System::String^> ^TableNames) {
			PushSpecial(L, GarrysMod::SPECIAL::GLOB);
			for each (System::String ^Name in TableNames)
				GetField(L, -1, Name);
		}

		static void SetTable(IntPtr L, int i) {
			ToLuaState(L)->luabase->SetTable(i);
		}

		static void SetMetaTable(IntPtr L, int i) {
			ToLuaState(L)->luabase->SetMetaTable(i);
		}

		static bool GetMetaTable(IntPtr L, int i) {
			return ToLuaState(L)->luabase->GetMetaTable(i);
		}

		static void Call(IntPtr L, int iArgs, int iResults) {
			ToLuaState(L)->luabase->Call(iArgs, iResults);
		}

		static int PCall(IntPtr L, int iArgs, int iResults, int iErrorFunc) {
			return ToLuaState(L)->luabase->PCall(iArgs, iResults, iErrorFunc);
		}

		static int Equal(IntPtr L, int iA, int iB) {
			return ToLuaState(L)->luabase->Equal(iA, iB);
		}

		static int RawEqual(IntPtr L, int iA, int iB) {
			return ToLuaState(L)->luabase->RawEqual(iA, iB);
		}

		static void Insert(IntPtr L, int iStackPos) {
			ToLuaState(L)->luabase->Insert(iStackPos);
		}

		static void Remove(IntPtr L, int iStackPos) {
			ToLuaState(L)->luabase->Remove(iStackPos);
		}

		static int Next(IntPtr L, int iStackPos) {
			return ToLuaState(L)->luabase->Next(iStackPos);
		}

		static void* NewUserdata(IntPtr L, unsigned int iSize) {
			return ToLuaState(L)->luabase->NewUserdata(iSize);
		}

		static void ThrowError(IntPtr L, System::String ^strError) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strError);
			ToLuaState(L)->luabase->ThrowError(str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void CheckType(IntPtr L, int iStackPos, int iType) {
			ToLuaState(L)->luabase->CheckType(iStackPos, iType);
		}

		static void ArgError(IntPtr L, int iArgNum, System::String ^strMessage) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strMessage);
			ToLuaState(L)->luabase->ArgError(iArgNum, str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void RawGet(IntPtr L, int iStackPos) {
			ToLuaState(L)->luabase->RawGet(iStackPos);
		}

		static void RawSet(IntPtr L, int iStackPos) {
			ToLuaState(L)->luabase->RawSet(iStackPos);
		}

		static System::String^ GetString(IntPtr L, int iStackPos, unsigned int* iOutLen) {
			return gcnew System::String(ToLuaState(L)->luabase->GetString(iStackPos, iOutLen));
		}

		static double GetNumber(IntPtr L, int iStackPos) {
			return ToLuaState(L)->luabase->GetNumber(iStackPos);
		}

		static bool GetBool(IntPtr L, int iStackPos) {
			return ToLuaState(L)->luabase->GetBool(iStackPos);
		}

		static void* GetCFunction(IntPtr L, int iStackPos) {
			return ToLuaState(L)->luabase->GetCFunction(iStackPos);
		}

		static void* GetUserdata(IntPtr L, int iStackPos) {
			return ToLuaState(L)->luabase->GetUserdata(iStackPos);
		}

		static void PushNil(IntPtr L) {
			ToLuaState(L)->luabase->PushNil();
		}

		static void PushString(IntPtr L, System::String ^val, unsigned int iLen) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(val);
			ToLuaState(L)->luabase->PushString(str, iLen);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void PushString(IntPtr L, System::String ^val) {
			GLua::PushString(L, val, 0);
		}
		
		static void PushNumber(IntPtr L, double val) {
			ToLuaState(L)->luabase->PushNumber(val);
		}

		static void PushBool(IntPtr L, bool val) {
			ToLuaState(L)->luabase->PushBool(val);
		}

		static void PushCClosure(IntPtr L, void* val, int iVars) {
			ToLuaState(L)->luabase->PushCClosure((CFunc)val, iVars);
		}

		static void PushUserdata(IntPtr L, void* UData) {
			ToLuaState(L)->luabase->PushUserdata(UData);
		}

		static int ReferenceCreate(IntPtr L) {
			return ToLuaState(L)->luabase->ReferenceCreate();
		}

		static void ReferenceFree(IntPtr L, int i) {
			ToLuaState(L)->luabase->ReferenceFree(i);
		}

		static void ReferencePush(IntPtr L, int i) {
			ToLuaState(L)->luabase->ReferencePush(i);
		}

		static void PushSpecial(IntPtr L, GarrysMod::SPECIAL iType) {
			ToLuaState(L)->luabase->PushSpecial((int)iType);
		}

		static bool IsType(IntPtr L, int iStackPos, int iType) {
			return ToLuaState(L)->luabase->IsType(iStackPos, iType);
		}

		static int GetType(IntPtr L, int iStackPos) {
			return ToLuaState(L)->luabase->GetType(iStackPos);
		}

		static System::String ^GetTypeName(IntPtr L, int iType) {
			return gcnew System::String(ToLuaState(L)->luabase->GetTypeName(iType));
		}

		static void CreateMetaTableType(IntPtr L, System::String ^strName, int iType) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			ToLuaState(L)->luabase->CreateMetaTableType(str, iType);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static System::String ^CheckString(IntPtr L, int iStackPos) {
			return gcnew System::String(ToLuaState(L)->luabase->CheckString(iStackPos));
		}

		static double CheckNumber(IntPtr L, int iStackPos) {
			return ToLuaState(L)->luabase->CheckNumber(iStackPos);
		}

		static int EmptyGFunc(IntPtr L) {
			return 0;
		}
	};
}
#endif