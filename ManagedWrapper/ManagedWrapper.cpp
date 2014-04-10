#ifndef MANAGED_WRAPPER_DISABLE

#include "stdafx.h"
#include "ManagedWrapper.h"

using namespace GarrysMod;
using namespace GarrysMod::Lua;
using namespace System::Collections::Generic;
using namespace System::Dynamic;

#define __static static

__static SpewRetval_t SpewOut(SpewType_t spewType, const tchar* pMsg) {
	if (GetCurrentThreadId() != SpewThreadID or !pMsg) return SPEW_CONTINUE;

	if (NewSpewOutputFunc != NULL and not InsideSpew) {
		InsideSpew = 1;
		auto Clr = GetSpewOutputColor();
		NewSpewOutputFunc(spewType, pMsg, Clr->r(), Clr->g(), Clr->b(), Clr->a());
	}

	InsideSpew = 0;
	return OldSpewOutputFunc(spewType, pMsg);
}

#define STACK_DEBUG

namespace GarrysMod {
	extending public ref class GLua {
	private:
		__static bool SkipMetamethods = false; // Ugly hack
		static Stack<int> ^glua_stack_counts = gcnew Stack<int>();
		static GLuaWriter ^glua_dump_writer = nullptr;

	public:
		// ============== UTILS ==
		ref class Utils {
		private:
			__static GSpewOutputFunc^ SpewOutputFunction = nullptr;
			__static bool PrintToConsole = false;

		public:
			__static void HookOutput(GSpewOutputFunc^ SpewOutFunc) {
				if (OldSpewOutputFunc != NULL) throw gcnew Exception("SpewOutputFunc alreay hooked!");

				SpewOutputFunction = SpewOutFunc;
				NewSpewOutputFunc = (NewSpewOutFunc)Marshal::GetFunctionPointerForDelegate(SpewOutputFunction).ToPointer();
				OldSpewOutputFunc = GetSpewOutputFunc();

				SpewThreadID = GetCurrentThreadId();
				SpewOutputFunc(SpewOut);
			}

			__static void UnhookOutput() {
				if (OldSpewOutputFunc == NULL) throw gcnew Exception("Old SpewOutputFunc is NULL");

				SpewOutputFunc(OldSpewOutputFunc);

				OldSpewOutputFunc = NULL;
				NewSpewOutputFunc = NULL;
				SpewOutputFunction = nullptr;
			}

			__static bool IsOutputHooked() {
				return OldSpewOutputFunc != NULL;
			}

			__static void print(LuaStateType L, String ^S) {
				GLua::GetTableVal(L, "print");
				GLua::PushString(L, S);
				GLua::Call(L, 1, 0);

				if (Utils::PrintToConsole)
					Console::WriteLine(S);
			}

			__static void print(LuaStateType L, String ^S, Boolean ToConsole) {
				auto oPTC = Utils::PrintToConsole; Utils::PrintToConsole = ToConsole;
				Utils::print(L, S);
				Utils::PrintToConsole = oPTC;
			}

			__static void print(LuaStateType L, String ^S, params array<Object^>^ VArgs) {
				Utils::print(L, String::Format(S, VArgs));
			}

			__static int DoString(LuaStateType L, String ^STR_S) {
				CSTR(S);
				int R = luaL_dostring(ToLuaState(L), S);
				DSTR(S);
				return R;
			}
		};

		// ============== KEEPALIVE ==
		ref class Keepalive {
		private:
			__static Dictionary<String^, Object^> ^KADict = gcnew Dictionary<String^, Object^>();

			__static bool CheckName(String^ Name) {
				if (Keepalive::KADict->ContainsKey(Name))
					Keepalive::Remove(Name);
				return true;
			}
		public:
			__static void Remove(String^ Name) {
				if (!Keepalive::KADict->ContainsKey(Name))
					return;
				Keepalive::KADict->Remove(Name);
			}

			__static void AddList(String^ Name, List<GFunc^>^ GFuncList) {
				if (Keepalive::CheckName(Name))
					Keepalive::KADict->Add(Name, GFuncList);
			}

			__static void AddObject(String^ Name, Object^ Obj) {
				if (Keepalive::CheckName(Name))
					Keepalive::KADict->Add(Name, Obj);
			}
		};

#undef __static
#define __static extending static
		// ============== FUNCTIONS ===================================================================================
		__static String ^GetTypeName(LuaStateType B){
			return GLua::GetTypeName(B, (Lua::Type)GLua::GetType(B, 1));
		}

		__static String ^GetTypeName(LuaStateType B, int Pos){
			return GLua::GetTypeName(B, GLua::GetType(B, Pos));
		}

		__static List<GFunc^> ^CreateLib(LuaStateType L, System::Type ^Lib) {
			return CreateLib(L, Lib, true);
		}

		__static List<GFunc^> ^CreateLib(LuaStateType L, System::Type ^Lib, bool Keepalive) {
			auto RetL = gcnew List<GFunc^>();
			auto Methods = Lib->GetMethods();
			String ^TableName = Lib->Name;											STACK_DEBUG
			GLua::CreateGlobalTable(L, TableName);									STACK_DEBUG
			auto GFuncType = (gcnew GFunc(GLua::EmptyGFunc))->GetType();
			for each (auto MInfo in Methods) {
				if (MInfo->ReturnType == (1).GetType()) {
					auto Params = MInfo->GetParameters();
					if (Params->Length == 1 && Params[0]->ParameterType->FullName == "System.IntPtr") {		STACK_DEBUG
						GFunc ^Func = (GFunc^)Delegate::CreateDelegate(GFuncType, MInfo);
						RetL->Add(Func);
						if (SkipMetamethods && MInfo->Name->StartsWith("__")) {		STACK_DEBUG
							PushSpecial(L, GarrysMod::SPECIAL::GLOB);
							PushString(L, Lib->Name);
							GetTable(L, -2);
							if (glua_getmetatable(L, -1) == 0)
								glua_createtable(L, 0, 0);
							PushGFunction(L, Func);
							glua_setfield(L, -2, MInfo->Name);
							glua_setmetatable(L, -1);				STACK_DEBUG
							continue;
						} STACK_DEBUG
						GLua::SetGlobalTableGFunc(L, TableName, MInfo->Name, Func); STACK_DEBUG
					}
				}
			}

			if (Keepalive)
				GLua::Keepalive::AddList(Lib->Name, RetL);

			return RetL;
		}

		// Ugly hack begin.
		__static List<GFunc^> ^CreateType(LuaStateType L, System::Type ^Typ) {
			return CreateType(L, Typ, true);
		}

		__static List<GFunc^> ^CreateType(LuaStateType L, System::Type ^Typ, bool Keepalive) {
			SkipMetamethods = true;
			List<GFunc^> ^GFL = CreateLib(L, Typ, Keepalive);
			SkipMetamethods = false;
			return GFL;
		}
		// Ugly hack end.

		// WRAPPERS
#define WRAPPERS_INCLUDE
#include "Wrappers.cpp"
#undef WRAPPERS_INCLUDE

		__static DumpResult glua_dump(LuaStateType LPtr, GLuaWriter ^GLW) { return glua_dump(LPtr, GLW, IntPtr::Zero); }
		__static DumpResult glua_dump(LuaStateType LPtr, GLuaWriter ^GLW, IntPtr Userdata) {
			glua_dump_writer = GLW;
			return glua_dump(LPtr, Userdata);
		}
		__static DumpResult glua_dump(LuaStateType LPtr) { return glua_dump(LPtr, IntPtr::Zero); }
		__static DumpResult glua_dump(LuaStateType LPtr, IntPtr Userdata) {
			if (glua_dump_writer == nullptr) return DumpResult::NO_DUMP_FUNCTION;
			return (DumpResult)lua_dump(ToLuaState(LPtr), GetFuncPointerC(lua_Writer, glua_dump_writer), Userdata.ToPointer());
		}

		/// Pushes stack count
		__static void PushStackCount(LuaStateType L) {
			//glua_stack_counts->Push(glua_gettop(L));
		}

		/// Restores stack count to last pushed count
		__static void PopStackCount(LuaStateType L) {
			/*int Cnt = lua_gettop(ToLuaState(L)) - glua_stack_counts->Pop();
			if (Cnt <= 0) return;
			Pop(L, -Cnt);*/
		}

		__static void Locked(LuaStateType L, LockedAction ^A) {
			Lock(L);
			PushStackCount(L);
			A();
			PopStackCount(L);
			Unlock(L);
		}

		__static bool IsClient(LuaStateType L) {
			return ToLuaStateExt(L)->IsClient();
		}

		__static bool IsServer(LuaStateType L) {
			return ToLuaStateExt(L)->IsServer();
		}

		__static IntPtr GetLuaState(LuaStateType L) {
			return IntPtr(((ILuaExtended*)ToLuaState(L)->luabase)->GetLuaState());
		}

		__static void AtPanic(LuaStateType L, GFunc ^F) {
			lua_atpanic(ToLuaState(L), ToCFunc(F));
		}

		__static bool IsMenu(LuaStateType L) { // TODO: Redo this?
			ILuaExtended* Le = (ILuaExtended*)ToLuaState(L);
			lua_getfield(ToLuaState(L), LUA_GLOBALSINDEX, "render");
			bool Render = lua_type(ToLuaState(L), -1) == (int)Lua::Type::NIL;
			lua_getfield(ToLuaState(L), LUA_GLOBALSINDEX, "chat");
			bool Chat = lua_type(ToLuaState(L), -1) == (int)Lua::Type::NIL;
			lua_getfield(ToLuaState(L), LUA_GLOBALSINDEX, "cam");
			bool Cam = lua_type(ToLuaState(L), -1) == (int)Lua::Type::NIL;
			if ((GLua::IsClient(L) or GLua::IsServer(L)) and (Render or Chat or Cam))
				return true;
			return false;
		}

		__static void Openlibs(LuaStateType L) {
			luaL_openlibs(ToLuaState(L));
		}

		__static void Shutdown(LuaStateType L) {
			ToLuaStateExt(L)->Shutdown();
		}

		__static void PushCFunction(LuaStateType L, void* F) {
			ToLuaState(L)->luabase->PushCFunction((CFunc)F);
		}

		__static void PushGFunction(LuaStateType L, GFunc ^F) {
			GLua::PushCFunction(L, ToCFunc(F));
		}
		
		__static void CreateGlobalTable(LuaStateType L, String ^S) {
			GLua::PushSpecial(L, GarrysMod::SPECIAL::GLOB);
			GLua::PushString(L, S);
			GLua::CreateTable(L);
			GLua::SetTable(L, -3);
		}

		__static void SetGlobalTableGFunc(LuaStateType L, String ^TableName, String ^FunctionName, GFunc ^F) {
			GLua::PushSpecial(L, GarrysMod::SPECIAL::GLOB);
			GLua::PushString(L, TableName);
			GLua::GetTable(L, -2);
			GLua::PushString(L, FunctionName);
			GLua::PushGFunction(L, F);
			GLua::SetTable(L, -3);
			GLua::Pop(L, -1);
		}

		__static int Top(LuaStateType L) {
			return ToLuaState(L)->luabase->Top();
		}

		__static void Push(LuaStateType L, int StackPos) {
			ToLuaState(L)->luabase->Push(StackPos);
		}

		__static void Pop(LuaStateType L, int Amount) {
			if (Amount == 0) return;
			ToLuaState(L)->luabase->Pop(Amount);
		}

		__static void GetTable(LuaStateType L, int StackPos) {
			ToLuaState(L)->luabase->GetTable(StackPos);
		}

		__static void GetField(LuaStateType L, int iStackPos, String ^strName) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			ToLuaState(L)->luabase->GetField(iStackPos, str);
			Marshal::FreeHGlobal(IntPtr((void*)str));
		}

		__static void SetField(LuaStateType L, int iStackPos, String ^strName) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			ToLuaState(L)->luabase->SetField(iStackPos, str);
			Marshal::FreeHGlobal(IntPtr((void*)str));
		}

		__static void CreateTable(LuaStateType L) {
			ToLuaState(L)->luabase->CreateTable();
		}

		__static void GetTableVal(LuaStateType L, params array<String^> ^TableNames) {
			PushSpecial(L, GarrysMod::SPECIAL::GLOB);
			for each (String ^Name in TableNames) {
				GetField(L, -1, Name);
				glua_remove(L, -2);
			}
		}

		__static void SetTable(LuaStateType L, int i) {
			ToLuaState(L)->luabase->SetTable(i);
		}

		__static void SetMetaTable(LuaStateType L, int i) {
			ToLuaState(L)->luabase->SetMetaTable(i);
		}

		__static bool GetMetaTable(LuaStateType L, int i) {
			return ToLuaState(L)->luabase->GetMetaTable(i);
		}

		__static void Call(LuaStateType L, int iArgs, int iResults) {
			ToLuaState(L)->luabase->Call(iArgs, iResults);
		}

		__static int PCall(LuaStateType L, int iArgs, int iResults, int iErrorFunc) {
			return ToLuaState(L)->luabase->PCall(iArgs, iResults, iErrorFunc);
		}

		__static int Equal(LuaStateType L, int iA, int iB) {
			return ToLuaState(L)->luabase->Equal(iA, iB);
		}

		__static int RawEqual(LuaStateType L, int iA, int iB) {
			return ToLuaState(L)->luabase->RawEqual(iA, iB);
		}

		__static void Insert(LuaStateType L, int iStackPos) {
			ToLuaState(L)->luabase->Insert(iStackPos);
		}

		__static void Remove(LuaStateType L, int iStackPos) {
			ToLuaState(L)->luabase->Remove(iStackPos);
		}

		__static int Next(LuaStateType L, int iStackPos) {
			return ToLuaState(L)->luabase->Next(iStackPos);
		}

		__static void* NewUserdata(LuaStateType L, unsigned int iSize) {
			return ToLuaState(L)->luabase->NewUserdata(iSize);
		}

		__static void ThrowError(LuaStateType L, String ^strError) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strError);
			ToLuaState(L)->luabase->ThrowError(str);
			Marshal::FreeHGlobal(IntPtr((void*)str));
		}

		__static void CheckType(LuaStateType L, int iStackPos, int iType) {
			ToLuaState(L)->luabase->CheckType(iStackPos, iType);
		}

		__static void ArgError(LuaStateType L, int iArgNum, String ^strMessage) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strMessage);
			ToLuaState(L)->luabase->ArgError(iArgNum, str);
			Marshal::FreeHGlobal(IntPtr((void*)str));
		}

		__static void RawGet(LuaStateType L, int iStackPos) {
			ToLuaState(L)->luabase->RawGet(iStackPos);
		}

		__static void RawSet(LuaStateType L, int iStackPos) {
			ToLuaState(L)->luabase->RawSet(iStackPos);
		}

		__static String^ GetString(LuaStateType L, int iStackPos, unsigned int* iOutLen) {
			return gcnew String(ToLuaState(L)->luabase->GetString(iStackPos, iOutLen));
		}

		__static double GetNumber(LuaStateType L, int iStackPos) {
			return ToLuaState(L)->luabase->GetNumber(iStackPos);
		}

		__static bool GetBool(LuaStateType L, int iStackPos) {
			return ToLuaState(L)->luabase->GetBool(iStackPos);
		}

		__static void* GetCFunction(LuaStateType L, int iStackPos) {
			return ToLuaState(L)->luabase->GetCFunction(iStackPos);
		}

		__static void* GetUserdata(LuaStateType L, int iStackPos) {
			return ToLuaState(L)->luabase->GetUserdata(iStackPos);
		}

		__static void PushNil(LuaStateType L) {
			ToLuaState(L)->luabase->PushNil();
		}

		__static void PushString(LuaStateType L, String ^val, unsigned int iLen) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(val);
			ToLuaState(L)->luabase->PushString(str, iLen);
			Marshal::FreeHGlobal(IntPtr((void*)str));
		}

		__static void PushString(LuaStateType L, String ^val) {
			GLua::PushString(L, val, 0);
		}
		
		__static void PushNumber(LuaStateType L, double val) {
			ToLuaState(L)->luabase->PushNumber(val);
		}

#define IsOfType(O, T) O->GetType() == T::typeid
		__static void Push(LuaStateType L, Object ^O) {
			if (IsOfType(O, String))
				PushString(L, (String^)O);
			else if (IsOfType(O, int))
				lua_pushinteger(ToLuaState(L), (int)O);
		}

		__static Object ^Get(LuaStateType L, int Pos) {
			if (IsType(L, Pos, GType::STRING))
				return GLua::glua_tostring(L, Pos);
			else if (IsType(L, Pos, GType::NUMBER))
				return GLua::glua_tonumber(L, Pos);
			else if (IsType(L, Pos, GType::NIL))
				return nullptr;
			else if (IsType(L, Pos, GType::TABLE))
				throw gcnew NotImplementedException("TODO: Pop table from stack?");
			return nullptr;
		}
#undef IsOfType

		__static void Lock(LuaStateType L) {
			ToLuaStateExt(L)->ThreadLock();
		}

		__static void Unlock(LuaStateType L) {
			ToLuaStateExt(L)->ThreadUnlock();
		}

		__static void PushBool(LuaStateType L, bool val) {
			ToLuaState(L)->luabase->PushBool(val);
		}

		__static void PushCClosure(LuaStateType L, void* val, int iVars) {
			ToLuaState(L)->luabase->PushCClosure((CFunc)val, iVars);
		}

		__static void PushUserdata(LuaStateType L, void* UData) {
			ToLuaState(L)->luabase->PushUserdata(UData);
		}

		__static int ReferenceCreate(LuaStateType L) {
			return ToLuaState(L)->luabase->ReferenceCreate();
		}

		__static void ReferenceFree(LuaStateType L, int i) {
			ToLuaState(L)->luabase->ReferenceFree(i);
		}

		__static void ReferencePush(LuaStateType L, int i) {
			ToLuaState(L)->luabase->ReferencePush(i);
		}

		__static void PushSpecial(LuaStateType L, GarrysMod::SPECIAL iType) {
			ToLuaState(L)->luabase->PushSpecial((int)iType);
		}

		__static bool IsType(LuaStateType L, int iStackPos, int iType) {
			return ToLuaState(L)->luabase->IsType(iStackPos, iType);
		}

		__static bool IsType(LuaStateType L, int iStackPos, Lua::Type iType) {
			return ToLuaState(L)->luabase->IsType(iStackPos, (int)iType);
		}

		__static Lua::Type GetType(LuaStateType L, int iStackPos) {
			return (Lua::Type)ToLuaState(L)->luabase->GetType(iStackPos);
		}

		__static String ^GetTypeName(LuaStateType L, Lua::Type iType) {
			return gcnew String(ToLuaState(L)->luabase->GetTypeName((int)iType));
		}

		__static void CreateMetaTableType(LuaStateType L, String ^strName, int iType) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			ToLuaState(L)->luabase->CreateMetaTableType(str, iType);
			Marshal::FreeHGlobal(IntPtr((void*)str));
		}

		__static String ^CheckString(LuaStateType L, int iStackPos) {
			return gcnew String(ToLuaState(L)->luabase->CheckString(iStackPos));
		}

		__static double CheckNumber(LuaStateType L, int iStackPos) {
			return ToLuaState(L)->luabase->CheckNumber(iStackPos);
		}

		static int EmptyGFunc(IntPtr L) {
			return 0;
		}

#undef __static
#define __static static
	};
}

#endif