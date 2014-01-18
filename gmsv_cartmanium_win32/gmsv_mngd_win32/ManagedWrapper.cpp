//#define GLUA

#ifndef GLUA
	extern "C" {
		#include "lua.h"
		#include "lualib.h"
		#include "lauxlib.h"
	}
	#pragma comment(lib, "lua_shared.lib")
#endif

#include <LuaExtended.h>

#using <mscorlib.dll>

#define or ||
#define PRINT(P) Console::WriteLine(P)

#define MWRAPPER
#ifdef MWRAPPER

using namespace System;
using namespace GarrysMod::Lua;
using namespace System::Runtime::InteropServices;

namespace GarrysMod {
	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	public delegate int GFunc(lua_State* L);
	
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

			static int TEST(lua_State* L) {
				lua_getglobal(L, "func");
				if(lua_pcall(L, 0, 0, 0)) return 1;
				return 0;
			}


			static ILuaExtended* ToExtended(ILuaBase* B) {
				return (ILuaExtended*)B;
			}

			static ILuaExtended* ToExtended(lua_State* B) {
				return (ILuaExtended*)B->luabase;
			}
		};

		lua_State* S;

		GLua(lua_State* State) {
			this->S = State;
		}

		GLua(System::IntPtr ^State) {
			this->S = (lua_State*)State->ToPointer();
		}

		GLua(void* State) {
			this->S = (lua_State*)State;
		}

		~GLua() {
			delete S;
		}

		static bool IsClient(lua_State* L) {
			return Utils::ToExtended(L)->IsClient();
		}

		bool IsClient() {
			return GLua::IsClient(this->S);
		}

		static bool IsServer(lua_State* L) {
			return Utils::ToExtended(L)->IsServer();
		}

		bool IsServer() {
			return GLua::IsServer(this->S);
		}

		static void Shutdown(lua_State* L) {
			Utils::ToExtended(L)->Shutdown();
		}

		void Shutdown() {
			GLua::Shutdown(this->S);
		}

		static void PushCFunction(lua_State* L, void* F) {
			L->luabase->PushCFunction((CFunc)F);
		}

		void PushCFunction(CFunc val) {
			GLua::PushCFunction(this->S, val);
		}

		void PushCFunction(void* F) {
			this->PushCFunction((CFunc)F);
		}

		static void PushGFunction(lua_State* L, GFunc ^F) {
			GLua::PushCFunction(L, Marshal::GetFunctionPointerForDelegate(F).ToPointer());
		}
		
		void PushGFunction(GFunc ^F) {
			GLua::PushGFunction(this->S, F);
		}

		static void CreateGlobalTable(lua_State* L, System::String ^S) {
			GLua::PushSpecial(L, GarrysMod::SPECIAL::GLOB);
			GLua::PushString(L, S);
			GLua::CreateTable(L);
			GLua::SetTable(L, -3);
		}

		void CreateGlobalTable(System::String ^S) {
			GLua::CreateGlobalTable(this->S, S);
		}

		static void SetGlobalTableGFunc(lua_State* L, System::String ^TableName, System::String ^FunctionName, GFunc ^F) {
			GLua::PushSpecial(L, GarrysMod::SPECIAL::GLOB);
			GLua::PushString(L, TableName);
			GLua::GetTable(L, -2);
			GLua::PushString(L, FunctionName);
			GLua::PushGFunction(L, F);
			GLua::SetTable(L, -3);
		}

		void SetGlobalTableGFunc(System::String ^TableName, System::String ^FunctionName, GFunc ^F) {
			GLua::SetGlobalTableGFunc(this->S, TableName, FunctionName, F);
		}

		static int Top(lua_State* L) {
			return L->luabase->Top();
		}

		int Top() {
			return GLua::Top(this->S);
		}

		static void Push(lua_State* L, int StackPos) {
			L->luabase->Push(StackPos);
		}

		void Push(int StackPos) {
			GLua::Push(this->S, StackPos);
		}
		
		static void Pop(lua_State* L, int Amount) {
			L->luabase->Pop(Amount);
		}

		void Pop(int Amount) {
			GLua::Pop(this->S, Amount);
		}

		static void GetTable(lua_State* L, int StackPos) {
			L->luabase->GetTable(StackPos);
		}

		void GetTable(int StackPos) {
			GLua::GetTable(this->S, StackPos);
		}

		static void GetField(lua_State* L, int iStackPos, System::String ^strName) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			L->luabase->GetField(iStackPos, str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		void GetField(int iStackPos, System::String ^strName) {
			GLua::GetField(this->S, iStackPos, strName);
		}

		static void SetField(lua_State* L, int iStackPos, System::String ^strName) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			L->luabase->SetField(iStackPos, str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		void SetField(int iStackPos, System::String ^strName) {
			GLua::SetField(this->S, iStackPos, strName);
		}

		static void CreateTable(lua_State* L) {
			L->luabase->CreateTable();
		}

		void CreateTable() {
			GLua::CreateTable(this->S);
		}

		static void SetTable(lua_State* L, int i) {
			L->luabase->SetTable(i);
		}

		void SetTable(int i) {
			GLua::SetTable(this->S, i);
		}

		static void SetMetaTable(lua_State* L, int i) {
			L->luabase->SetMetaTable(i);
		}

		void SetMetaTable(int i) {
			GLua::SetMetaTable(this->S, i);
		}

		static bool GetMetaTable(lua_State* L, int i) {
			return L->luabase->GetMetaTable(i);
		}

		bool GetMetaTable(int i) {
			return GLua::GetMetaTable(this->S, i);
		}

		static void Call(lua_State* L, int iArgs, int iResults) {
			L->luabase->Call(iArgs, iResults);
		}

		void Call(int iArgs, int iResults) {
			GLua::Call(this->S, iArgs, iResults);
		}

		static int PCall(lua_State* L, int iArgs, int iResults, int iErrorFunc) {
			return L->luabase->PCall(iArgs, iResults, iErrorFunc);
		}

		int PCall(int iArgs, int iResults, int iErrorFunc) {
			return GLua::PCall(this->S, iArgs, iResults, iErrorFunc);
		}

		static int Equal(lua_State* L, int iA, int iB) {
			return L->luabase->Equal(iA, iB);
		}

		int Equal(int iA, int iB) {
			return GLua::Equal(this->S, iA, iB);
		}

		static int RawEqual(lua_State* L, int iA, int iB) {
			return L->luabase->RawEqual(iA, iB);
		}

		int RawEqual(int iA, int iB) {
			return GLua::RawEqual(this->S, iA, iB);
		}

		static void Insert(lua_State* L, int iStackPos) {
			L->luabase->Insert(iStackPos);
		}

		void Insert(int iStackPos) {
			GLua::Insert(this->S, iStackPos);
		}

		static void Remove(lua_State* L, int iStackPos) {
			L->luabase->Remove(iStackPos);
		}

		void Remove(int iStackPos) {
			GLua::Remove(this->S, iStackPos);
		}

		static int Next(lua_State* L, int iStackPos) {
			return L->luabase->Next(iStackPos);
		}

		int Next(int iStackPos) {
			return GLua::Next(this->S, iStackPos);
		}

		static void* NewUserdata(lua_State* L, unsigned int iSize) {
			return L->luabase->NewUserdata(iSize);
		}

		void* NewUserdata(unsigned int iSize) {
			return GLua::NewUserdata(this->S, iSize);
		}

		static void ThrowError(lua_State* L, System::String ^strError) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strError);
			L->luabase->ThrowError(str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		void ThrowError(System::String ^strError) {
			GLua::ThrowError(this->S, strError);
		}

		static void CheckType(lua_State* L, int iStackPos, int iType) {
			L->luabase->CheckType(iStackPos, iType);
		}

		void CheckType(int iStackPos, int iType) {
			GLua::CheckType(this->S, iStackPos, iType);
		}

		static void ArgError(lua_State* L, int iArgNum, System::String ^strMessage) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strMessage);
			L->luabase->ArgError(iArgNum, str);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		void ArgError(int iArgNum, System::String ^strMessage) {
			GLua::ArgError(this->S, iArgNum, strMessage);
		}

		static void RawGet(lua_State* L, int iStackPos) {
			L->luabase->RawGet(iStackPos);
		}

		void RawGet(int iStackPos) {
			GLua::RawGet(this->S, iStackPos);
		}

		static void RawSet(lua_State* L, int iStackPos) {
			L->luabase->RawSet(iStackPos);
		}

		void RawSet(int iStackPos) {
			GLua::RawSet(this->S, iStackPos);
		}

		static System::String^ GetString(lua_State* L, int iStackPos, unsigned int* iOutLen) {
			return gcnew System::String(L->luabase->GetString(iStackPos, iOutLen));
		}

		System::String^ GetString(int iStackPos, unsigned int* iOutLen) {
			return GLua::GetString(this->S, iStackPos, iOutLen);
		}

		static double GetNumber(lua_State* L, int iStackPos) {
			return L->luabase->GetNumber(iStackPos);
		}

		double GetNumber(int iStackPos) {
			return GLua::GetNumber(this->S, iStackPos);
		}

		static bool GetBool(lua_State* L, int iStackPos) {
			return L->luabase->GetBool(iStackPos);
		}

		bool GetBool(int iStackPos) {
			return GLua::GetBool(this->S, iStackPos);
		}

		static void* GetCFunction(lua_State* L, int iStackPos) {
			return L->luabase->GetCFunction(iStackPos);
		}

		void* GetCFunction(int iStackPos) {
			return GLua::GetCFunction(this->S, iStackPos);
		}

		static void* GetUserdata(lua_State* L, int iStackPos) {
			return L->luabase->GetUserdata(iStackPos);
		}

		void* GetUserdata(int iStackPos) {
			return GLua::GetUserdata(this->S, iStackPos);
		}

		static void PushNil(lua_State* L) {
			L->luabase->PushNil();
		}

		void PushNil() {
			GLua::PushNil(this->S);
		}

		static void PushString(lua_State* L, System::String ^val, unsigned int iLen) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(val);
			L->luabase->PushString(str, iLen);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		static void PushString(lua_State* L, System::String ^val) {
			GLua::PushString(L, val, 0);
		}

		void PushString(System::String ^str, unsigned int iLen) {
			GLua::PushString(this->S, str, iLen);
		}

		void PushString(System::String ^str) {
			GLua::PushString(this->S, str);
		}
		
		static void PushNumber(lua_State* L, double val) {
			L->luabase->PushNumber(val);
		}

		void PushNumber(double N) {
			GLua::PushNumber(this->S, N);
		}

		static void PushBool(lua_State* L, bool val) {
			L->luabase->PushBool(val);
		}

		void PushBool(bool B) {
			GLua::PushBool(this->S, B);
		}

		static void PushCClosure(lua_State* L, void* val, int iVars) {
			L->luabase->PushCClosure((CFunc)val, iVars);
		}

		void PushCClosure(void* val, int iVars) {
			GLua::PushCClosure(this->S, val, iVars);
		}

		static void PushUserdata(lua_State* L, void* UData) {
			L->luabase->PushUserdata(UData);
		}

		void PushUserdata(void* UData) {
			GLua::PushUserdata(this->S, UData);
		}

		static int ReferenceCreate(lua_State* L) {
			return L->luabase->ReferenceCreate();
		}

		int ReferenceCreate() {
			return GLua::ReferenceCreate(this->S);
		}

		static void ReferenceFree(lua_State* L, int i) {
			L->luabase->ReferenceFree(i);
		}

		void ReferenceFree(int i) {
			GLua::ReferenceFree(this->S, i);
		}

		static void ReferencePush(lua_State* L, int i) {
			L->luabase->ReferencePush(i);
		}

		void ReferencePush(int i) {
			GLua::ReferencePush(this->S, i);
		}

		static void PushSpecial(lua_State* L, GarrysMod::SPECIAL iType) {
			L->luabase->PushSpecial((int)iType);
		}

		void PushSpecial(GarrysMod::SPECIAL Spec) {
			GLua::PushSpecial(this->S, Spec);
		}

		static bool IsType(lua_State* L, int iStackPos, int iType) {
			return L->luabase->IsType(iStackPos, iType);
		}

		bool IsType(int iStackPos, int iType) {
			return GLua::IsType(this->S, iStackPos, iType);
		}

		static int GetType(lua_State* L, int iStackPos) {
			return L->luabase->GetType(iStackPos);
		}

		int GetType(int iStackPos) {
			return GLua::GetType(this->S, iStackPos);
		}

		static System::String ^GetTypeName(lua_State* L, int iType) {
			return gcnew System::String(L->luabase->GetTypeName(iType));
		}

		System::String ^GetTypeName(int iType) {
			return GLua::GetTypeName(this->S, iType);
		}

		static void CreateMetaTableType(lua_State* L, System::String ^strName, int iType) {
			const char* str = (const char*)(void*)Marshal::StringToHGlobalAnsi(strName);
			L->luabase->CreateMetaTableType(str, iType);
			Marshal::FreeHGlobal(System::IntPtr((void*)str));
		}

		void CreateMetaTableType(System::String ^strName, int iType) {
			GLua::CreateMetaTableType(this->S, strName, iType);
		}

		static System::String ^CheckString(lua_State* L, int iStackPos) {
			return gcnew System::String(L->luabase->CheckString(iStackPos));
		}

		System::String ^CheckString(int iStackPos) {
			return GLua::CheckString(this->S, iStackPos);
		}

		static double CheckNumber(lua_State* L, int iStackPos) {
			return L->luabase->CheckNumber(iStackPos);
		}

		double CheckNumber(int iStackPos) {
			return GLua::CheckNumber(this->S, iStackPos);
		}
	};
}
#endif