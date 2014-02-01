#pragma comment(lib, "lua_shared.lib")

#include "GLua.h"

#using <mscorlib.dll>

#define or ||
#define PRINT(P) Console::WriteLine(P)

#define MWRAPPER
#ifdef MWRAPPER

using namespace System;
using namespace GarrysMod::Lua;

namespace GarrysMod {
	public ref class GLua {
	private:
	public:
		ref class Utils {
		public:
			static void print(lua_State* L, System::String ^S) {
				GLua::PushSpecial(L, GarrysMod::SPECIAL::GLOB);
				GLua::PushString(L, "print");
				GLua::GetTable(L, -2);
				GLua::PushString(L, S);
				GLua::Call(L, 1, 0);
			}

			static void print(lua_State* L, System::String ^S, System::Boolean ToConsole) {
				Utils::print(L, S);
				if (ToConsole)
					System::Console::WriteLine(S);
			}

			static ILuaExtended* ToExtended(ILuaBase* B) {
				return (ILuaExtended*)B;
			}

			static ILuaExtended* ToExtended(lua_State* B) {
				return (ILuaExtended*)B->luabase;
			}
		};

		static System::Collections::Generic::List<GFunc^> ^CreateClassLib(lua_State *L, System::Type ^Lib) {
			auto RetL = gcnew System::Collections::Generic::List<GFunc^>();

			auto Methods = Lib->GetMethods();
			System::String ^TableName = Lib->Name;
			GLua::CreateGlobalTable(L, TableName);
			auto GFuncType = (gcnew GFunc(GLua::EmptyGFunc))->GetType();
			for each (auto MInfo in Methods) {
				if (MInfo->ReturnType == (1).GetType()) {
					auto Params = MInfo->GetParameters();
					if (Params->Length == 1 && Params[0]->ParameterType->FullName == "lua_State*") {
						GFunc ^Func = (GFunc^)System::Delegate::CreateDelegate(GFuncType, MInfo);
						RetL->Add(Func);
						GLua::SetGlobalTableGFunc(L, TableName, MInfo->Name, Func);
					}
				}
			}

			return RetL;
		}

#include "Wrappers.h"

		static bool IsClient(lua_State* L) {
			return Utils::ToExtended(L)->IsClient();
		}

		static bool IsServer(lua_State* L) {
			return Utils::ToExtended(L)->IsServer();
		}

		static void Shutdown(lua_State* L) {
			Utils::ToExtended(L)->Shutdown();
		}

		static void PushCFunction(lua_State* L, void* F) {
			L->luabase->PushCFunction((CFunc)F);
		}

		static void PushGFunction(lua_State* L, GFunc ^F) {
			GLua::PushCFunction(L, Marshal::GetFunctionPointerForDelegate(F).ToPointer());
		}
		
		static void CreateGlobalTable(lua_State* L, System::String ^S) {
			GLua::PushSpecial(L, GarrysMod::SPECIAL::GLOB);
			GLua::PushString(L, S);
			GLua::CreateTable(L);
			GLua::SetTable(L, -3);
		}

		static void SetGlobalTableGFunc(lua_State* L, System::String ^TableName, System::String ^FunctionName, GFunc ^F) {
			GLua::PushSpecial(L, GarrysMod::SPECIAL::GLOB);
			GLua::PushString(L, TableName);
			GLua::GetTable(L, -2);
			GLua::PushString(L, FunctionName);
			GLua::PushGFunction(L, F);
			GLua::SetTable(L, -3);
		}

		static int Top(lua_State* L) {
			return L->luabase->Top();
		}

		static void Push(lua_State* L, int StackPos) {
			L->luabase->Push(StackPos);
		}

		static void Pop(lua_State* L, int Amount) {
			L->luabase->Pop(Amount);
		}

		static void GetTable(lua_State* L, int StackPos) {
			L->luabase->GetTable(StackPos);
		}

		static void GetField(lua_State* L, int iStackPos, System::String ^strName) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			L->luabase->GetField(iStackPos, str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void SetField(lua_State* L, int iStackPos, System::String ^strName) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			L->luabase->SetField(iStackPos, str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void CreateTable(lua_State* L) {
			L->luabase->CreateTable();
		}

		static void SetTable(lua_State* L, int i) {
			L->luabase->SetTable(i);
		}

		static void SetMetaTable(lua_State* L, int i) {
			L->luabase->SetMetaTable(i);
		}

		static bool GetMetaTable(lua_State* L, int i) {
			return L->luabase->GetMetaTable(i);
		}

		static void Call(lua_State* L, int iArgs, int iResults) {
			L->luabase->Call(iArgs, iResults);
		}

		static int PCall(lua_State* L, int iArgs, int iResults, int iErrorFunc) {
			return L->luabase->PCall(iArgs, iResults, iErrorFunc);
		}

		static int Equal(lua_State* L, int iA, int iB) {
			return L->luabase->Equal(iA, iB);
		}

		static int RawEqual(lua_State* L, int iA, int iB) {
			return L->luabase->RawEqual(iA, iB);
		}

		static void Insert(lua_State* L, int iStackPos) {
			L->luabase->Insert(iStackPos);
		}

		static void Remove(lua_State* L, int iStackPos) {
			L->luabase->Remove(iStackPos);
		}

		static int Next(lua_State* L, int iStackPos) {
			return L->luabase->Next(iStackPos);
		}

		static void* NewUserdata(lua_State* L, unsigned int iSize) {
			return L->luabase->NewUserdata(iSize);
		}

		static void ThrowError(lua_State* L, System::String ^strError) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strError);
			L->luabase->ThrowError(str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void CheckType(lua_State* L, int iStackPos, int iType) {
			L->luabase->CheckType(iStackPos, iType);
		}

		static void ArgError(lua_State* L, int iArgNum, System::String ^strMessage) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strMessage);
			L->luabase->ArgError(iArgNum, str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void RawGet(lua_State* L, int iStackPos) {
			L->luabase->RawGet(iStackPos);
		}

		static void RawSet(lua_State* L, int iStackPos) {
			L->luabase->RawSet(iStackPos);
		}

		static System::String^ GetString(lua_State* L, int iStackPos, unsigned int* iOutLen) {
			return gcnew System::String(L->luabase->GetString(iStackPos, iOutLen));
		}

		static double GetNumber(lua_State* L, int iStackPos) {
			return L->luabase->GetNumber(iStackPos);
		}

		static bool GetBool(lua_State* L, int iStackPos) {
			return L->luabase->GetBool(iStackPos);
		}

		static void* GetCFunction(lua_State* L, int iStackPos) {
			return L->luabase->GetCFunction(iStackPos);
		}

		static void* GetUserdata(lua_State* L, int iStackPos) {
			return L->luabase->GetUserdata(iStackPos);
		}

		static void PushNil(lua_State* L) {
			L->luabase->PushNil();
		}

		static void PushString(lua_State* L, System::String ^val, unsigned int iLen) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(val);
			L->luabase->PushString(str, iLen);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void PushString(lua_State* L, System::String ^val) {
			GLua::PushString(L, val, 0);
		}
		
		static void PushNumber(lua_State* L, double val) {
			L->luabase->PushNumber(val);
		}

		static void PushBool(lua_State* L, bool val) {
			L->luabase->PushBool(val);
		}

		static void PushCClosure(lua_State* L, void* val, int iVars) {
			L->luabase->PushCClosure((CFunc)val, iVars);
		}

		static void PushUserdata(lua_State* L, void* UData) {
			L->luabase->PushUserdata(UData);
		}

		static int ReferenceCreate(lua_State* L) {
			return L->luabase->ReferenceCreate();
		}

		static void ReferenceFree(lua_State* L, int i) {
			L->luabase->ReferenceFree(i);
		}

		static void ReferencePush(lua_State* L, int i) {
			L->luabase->ReferencePush(i);
		}

		static void PushSpecial(lua_State* L, GarrysMod::SPECIAL iType) {
			L->luabase->PushSpecial((int)iType);
		}

		static bool IsType(lua_State* L, int iStackPos, int iType) {
			return L->luabase->IsType(iStackPos, iType);
		}

		static int GetType(lua_State* L, int iStackPos) {
			return L->luabase->GetType(iStackPos);
		}

		static System::String ^GetTypeName(lua_State* L, int iType) {
			return gcnew System::String(L->luabase->GetTypeName(iType));
		}

		static void CreateMetaTableType(lua_State* L, System::String ^strName, int iType) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			L->luabase->CreateMetaTableType(str, iType);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static System::String ^CheckString(lua_State* L, int iStackPos) {
			return gcnew System::String(L->luabase->CheckString(iStackPos));
		}

		static double CheckNumber(lua_State* L, int iStackPos) {
			return L->luabase->CheckNumber(iStackPos);
		}

		static int EmptyGFunc(lua_State* L) {
			return 0;
		}
	};
}
#endif