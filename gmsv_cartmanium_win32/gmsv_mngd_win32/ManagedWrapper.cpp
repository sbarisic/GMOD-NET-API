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
	public ref class LuaState {
	private:
		lua_State* LS;
	public:
		LuaState(lua_State* LS) {
			this->LS = LS;
		}

		LuaState(IntPtr ^IPtr) {
			this->LS = (lua_State*)IPtr->ToPointer();
		}

		lua_State* ToLuaState() {
			return this->LS;
		}
	};

	public ref class GLua {
	private:
		static bool SkipMetamethods = false; // Ugly hack

	public:
		ref class Utils {
		public:
			static bool PrintToConsole = true;

			static void print(LuaState^ LS, System::String ^S) {
				GLua::PushSpecial(LS, GarrysMod::SPECIAL::GLOB);
				GLua::PushString(LS, "print");
				GLua::GetTable(LS, -2);
				GLua::PushString(LS, S);
				GLua::Call(LS, 1, 0);
				if (Utils::PrintToConsole)
					System::Console::WriteLine(S);

			}

			static void print(LuaState^ LS, System::String ^S, System::Boolean ToConsole) {
				auto oPTC = Utils::PrintToConsole; Utils::PrintToConsole = ToConsole;
				Utils::print(LS, S);
				Utils::PrintToConsole = oPTC;
			}

			static void print(LuaState^ LS, System::String ^S, params array<Object^>^ VArgs) {
				Utils::print(LS, System::String::Format(S, VArgs));
			}

			static int DoString(LuaState^ LS, System::String ^STR_S) {
				CSTR(S);
				int R = luaL_dostring(LS->ToLuaState(), S);
				DSTR(S);
				return R;
			}

			static ILuaExtended* ToExtended(ILuaBase* B) {
				return (ILuaExtended*)B;
			}

			static ILuaExtended* ToExtended(LuaState^ B) {
				return (ILuaExtended*)B->ToLuaState()->luabase;
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

		static System::String ^GetTypeName(LuaState^ B){
			return GLua::GetTypeName(B, GLua::GetType(B, 1));
		}

		static List<GFunc^> ^CreateLib(LuaState^ LS, System::Type ^Lib) {
			return CreateLib(LS, Lib, true);
		}

		static List<GFunc^> ^CreateLib(LuaState^ LS, System::Type ^Lib, bool Keepalive) {
			auto RetL = gcnew List<GFunc^>();
			auto Methods = Lib->GetMethods();
			System::String ^TableName = Lib->Name;
			GLua::CreateGlobalTable(LS, TableName);
			auto GFuncType = (gcnew GFunc(GLua::EmptyGFunc))->GetType();
			for each (auto MInfo in Methods) {
				if (MInfo->ReturnType == (1).GetType()) {
					auto Params = MInfo->GetParameters();
					if (Params->Length == 1 && Params[0]->ParameterType->FullName == "LuaState^") {
						GFunc ^Func = (GFunc^)System::Delegate::CreateDelegate(GFuncType, MInfo);
						RetL->Add(Func);
						if (SkipMetamethods && MInfo->Name->StartsWith("__")) {
							PushSpecial(LS, GarrysMod::SPECIAL::GLOB);
							PushString(LS, Lib->Name);
							GetTable(LS, -2);
							if (glua_getmetatable(LS, -1) == 0)
								glua_createtable(LS, 0, 0);
							PushGFunction(LS, Func);
							glua_setfield(LS, -2, MInfo->Name);
							glua_setmetatable(LS, -2);
							GLua::Pop(LS, 1);
							continue;
						} 
						GLua::SetGlobalTableGFunc(LS, TableName, MInfo->Name, Func);
					}
				}
			}

			if (Keepalive)
				GLua::Keepalive::AddList(Lib->Name, RetL);

			return RetL;
		}

		// Ugly hack begin.
		static List<GFunc^> ^CreateType(LuaState^ LS, System::Type ^Typ) {
			return CreateType(LS, Typ, true);
		}

		static List<GFunc^> ^CreateType(LuaState^ LS, System::Type ^Typ, bool Keepalive) {
			SkipMetamethods = true;
			List<GFunc^> ^GFL = CreateLib(LS, Typ, Keepalive);
			SkipMetamethods = false;
			return GFL;
		}
		// Ugly hack end.

#include "Wrappers.h"

		static bool IsClient(LuaState^ LS) {
			return Utils::ToExtended(LS)->IsClient();
		}

		static bool IsServer(LuaState^ LS) {
			return Utils::ToExtended(LS)->IsServer();
		}

		static bool IsMenu(LuaState^ LS) {
			ILuaExtended* Le = (ILuaExtended*)LS->ToLuaState();
			lua_getfield(LS->ToLuaState(), LUA_GLOBALSINDEX, "render");
			bool Render = lua_type(LS->ToLuaState(), -1) == (int)Lua::Type::NIL;
			lua_getfield(LS->ToLuaState(), LUA_GLOBALSINDEX, "chat");
			bool Chat = lua_type(LS->ToLuaState(), -1) == (int)Lua::Type::NIL;
			lua_getfield(LS->ToLuaState(), LUA_GLOBALSINDEX, "cam");
			bool Cam = lua_type(LS->ToLuaState(), -1) == (int)Lua::Type::NIL;
			if ((GLua::IsClient(LS) || GLua::IsServer(LS)) && (Render || Chat || Cam))
				return true;
			return false;
		}

		static void Openlibs(LuaState^ LS) {
			luaL_openlibs(LS->ToLuaState());
		}

		static void Shutdown(LuaState^ LS) {
			Utils::ToExtended(LS)->Shutdown();
		}

		static void PushCFunction(LuaState^ LS, void* F) {
			LS->ToLuaState()->luabase->PushCFunction((CFunc)F);
		}

		static void PushGFunction(LuaState^ LS, GFunc ^F) {
			GLua::PushCFunction(LS, Marshal::GetFunctionPointerForDelegate(F).ToPointer());
		}
		
		static void CreateGlobalTable(LuaState^ LS, System::String ^S) {
			GLua::PushSpecial(LS, GarrysMod::SPECIAL::GLOB);
			GLua::PushString(LS, S);
			GLua::CreateTable(LS);
			GLua::SetTable(LS, -3);
		}

		static void SetGlobalTableGFunc(LuaState^ LS, System::String ^TableName, System::String ^FunctionName, GFunc ^F) {
			GLua::PushSpecial(LS, GarrysMod::SPECIAL::GLOB);
			GLua::PushString(LS, TableName);
			GLua::GetTable(LS, -2);
			GLua::PushString(LS, FunctionName);
			GLua::PushGFunction(LS, F);
			GLua::SetTable(LS, -3);
		}

		static int Top(LuaState^ LS) {
			return LS->ToLuaState()->luabase->Top();
		}

		static void Push(LuaState^ LS, int StackPos) {
			LS->ToLuaState()->luabase->Push(StackPos);
		}

		static void Pop(LuaState^ LS, int Amount) {
			LS->ToLuaState()->luabase->Pop(Amount);
		}

		static void GetTable(LuaState^ LS, int StackPos) {
			LS->ToLuaState()->luabase->GetTable(StackPos);
		}

		static void GetField(LuaState^ LS, int iStackPos, System::String ^strName) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			LS->ToLuaState()->luabase->GetField(iStackPos, str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void SetField(LuaState^ LS, int iStackPos, System::String ^strName) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			LS->ToLuaState()->luabase->SetField(iStackPos, str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void CreateTable(LuaState^ LS) {
			LS->ToLuaState()->luabase->CreateTable();
		}

		static void GetTableVal(LuaState^ LS, params array<System::String^> ^TableNames) {
			PushSpecial(LS, GarrysMod::SPECIAL::GLOB);
			for each (System::String ^Name in TableNames)
				GetField(LS, -1, Name);
		}

		static void SetTable(LuaState^ LS, int i) {
			LS->ToLuaState()->luabase->SetTable(i);
		}

		static void SetMetaTable(LuaState^ LS, int i) {
			LS->ToLuaState()->luabase->SetMetaTable(i);
		}

		static bool GetMetaTable(LuaState^ LS, int i) {
			return LS->ToLuaState()->luabase->GetMetaTable(i);
		}

		static void Call(LuaState^ LS, int iArgs, int iResults) {
			LS->ToLuaState()->luabase->Call(iArgs, iResults);
		}

		static int PCall(LuaState^ LS, int iArgs, int iResults, int iErrorFunc) {
			return LS->ToLuaState()->luabase->PCall(iArgs, iResults, iErrorFunc);
		}

		static int Equal(LuaState^ LS, int iA, int iB) {
			return LS->ToLuaState()->luabase->Equal(iA, iB);
		}

		static int RawEqual(LuaState^ LS, int iA, int iB) {
			return LS->ToLuaState()->luabase->RawEqual(iA, iB);
		}

		static void Insert(LuaState^ LS, int iStackPos) {
			LS->ToLuaState()->luabase->Insert(iStackPos);
		}

		static void Remove(LuaState^ LS, int iStackPos) {
			LS->ToLuaState()->luabase->Remove(iStackPos);
		}

		static int Next(LuaState^ LS, int iStackPos) {
			return LS->ToLuaState()->luabase->Next(iStackPos);
		}

		static void* NewUserdata(LuaState^ LS, unsigned int iSize) {
			return LS->ToLuaState()->luabase->NewUserdata(iSize);
		}

		static void ThrowError(LuaState^ LS, System::String ^strError) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strError);
			LS->ToLuaState()->luabase->ThrowError(str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void CheckType(LuaState^ LS, int iStackPos, int iType) {
			LS->ToLuaState()->luabase->CheckType(iStackPos, iType);
		}

		static void ArgError(LuaState^ LS, int iArgNum, System::String ^strMessage) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strMessage);
			LS->ToLuaState()->luabase->ArgError(iArgNum, str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void RawGet(LuaState^ LS, int iStackPos) {
			LS->ToLuaState()->luabase->RawGet(iStackPos);
		}

		static void RawSet(LuaState^ LS, int iStackPos) {
			LS->ToLuaState()->luabase->RawSet(iStackPos);
		}

		static System::String^ GetString(LuaState^ LS, int iStackPos, unsigned int* iOutLen) {
			return gcnew System::String(LS->ToLuaState()->luabase->GetString(iStackPos, iOutLen));
		}

		static double GetNumber(LuaState^ LS, int iStackPos) {
			return LS->ToLuaState()->luabase->GetNumber(iStackPos);
		}

		static bool GetBool(LuaState^ LS, int iStackPos) {
			return LS->ToLuaState()->luabase->GetBool(iStackPos);
		}

		static void* GetCFunction(LuaState^ LS, int iStackPos) {
			return LS->ToLuaState()->luabase->GetCFunction(iStackPos);
		}

		static void* GetUserdata(LuaState^ LS, int iStackPos) {
			return LS->ToLuaState()->luabase->GetUserdata(iStackPos);
		}

		static void PushNil(LuaState^ LS) {
			LS->ToLuaState()->luabase->PushNil();
		}

		static void PushString(LuaState^ LS, System::String ^val, unsigned int iLen) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(val);
			LS->ToLuaState()->luabase->PushString(str, iLen);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void PushString(LuaState^ LS, System::String ^val) {
			GLua::PushString(LS, val, 0);
		}
		
		static void PushNumber(LuaState^ LS, double val) {
			LS->ToLuaState()->luabase->PushNumber(val);
		}

		static void PushBool(LuaState^ LS, bool val) {
			LS->ToLuaState()->luabase->PushBool(val);
		}

		static void PushCClosure(LuaState^ LS, void* val, int iVars) {
			LS->ToLuaState()->luabase->PushCClosure((CFunc)val, iVars);
		}

		static void PushUserdata(LuaState^ LS, void* UData) {
			LS->ToLuaState()->luabase->PushUserdata(UData);
		}

		static int ReferenceCreate(LuaState^ LS) {
			return LS->ToLuaState()->luabase->ReferenceCreate();
		}

		static void ReferenceFree(LuaState^ LS, int i) {
			LS->ToLuaState()->luabase->ReferenceFree(i);
		}

		static void ReferencePush(LuaState^ LS, int i) {
			LS->ToLuaState()->luabase->ReferencePush(i);
		}

		static void PushSpecial(LuaState^ LS, GarrysMod::SPECIAL iType) {
			LS->ToLuaState()->luabase->PushSpecial((int)iType);
		}

		static bool IsType(LuaState^ LS, int iStackPos, int iType) {
			return LS->ToLuaState()->luabase->IsType(iStackPos, iType);
		}

		static int GetType(LuaState^ LS, int iStackPos) {
			return LS->ToLuaState()->luabase->GetType(iStackPos);
		}

		static System::String ^GetTypeName(LuaState^ LS, int iType) {
			return gcnew System::String(LS->ToLuaState()->luabase->GetTypeName(iType));
		}

		static void CreateMetaTableType(LuaState^ LS, System::String ^strName, int iType) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			LS->ToLuaState()->luabase->CreateMetaTableType(str, iType);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static System::String ^CheckString(LuaState^ LS, int iStackPos) {
			return gcnew System::String(LS->ToLuaState()->luabase->CheckString(iStackPos));
		}

		static double CheckNumber(LuaState^ LS, int iStackPos) {
			return LS->ToLuaState()->luabase->CheckNumber(iStackPos);
		}

		static int EmptyGFunc(LuaState^ LS) {
			return 0;
		}
	};
}
#endif