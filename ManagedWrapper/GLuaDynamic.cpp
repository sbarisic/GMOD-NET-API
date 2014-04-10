#include "stdafx.h"

#include "ManagedWrapper.cpp"

void GLuaDynamic::Init(IntPtr L) {
	this->L = L;
	this->DynamicType = (int)GarrysMod::Lua::Type::TABLE;
	this->FullPath = gcnew List<String^>();
}

GLuaDynamic::GLuaDynamic(IntPtr Ptr) {
	Init(Ptr);
	this->FullPath->Add("_G");
}

GLuaDynamic::GLuaDynamic(IntPtr Ptr, ...array<String^> ^FullPath) {
	Init(Ptr);
	this->FullPath->AddRange(FullPath);
}

bool Check(Object^% O) {
	if (O == nullptr) return false;
	return true;
}

bool GLuaDynamic::TryGetMember(GetMemberBinder ^GMB, Object^% O) {
	GLua::Lock(this->L);
	GLua::PushStackCount(this->L);
	int StackSize = GLua::glua_gettop(this->L);

	array<String^> ^Member = gcnew array<String^>(this->FullPath->Count + 1);
	this->FullPath->CopyTo(Member, 0);
	Member[Member->Length - 1] = GMB->Name;

	GLua::GetTableVal(this->L, Member);
	O = GLua::Get(this->L, -1);

	GLua::PopStackCount(this->L);
	GLua::Unlock(this->L);
	return Check(O);
}

static void StackDbg(lua_State* L) {
	int StackSize = lua_gettop(L);

	Console::Clear();
	for (int i = 1; i <= StackSize; i++)
		Console::WriteLine("[{0}] = {1}", i, gcnew String(lua_typename(L, lua_type(L, i))));
}

void GLuaDynamic::Dbg() {
	StackDbg(ToLuaState(this->L));
}

bool GLuaDynamic::TryInvokeMember(InvokeMemberBinder ^IMB, array<Object^> ^Args, Object^% O) {
	GLua::Lock(this->L);
	GLua::PushStackCount(this->L);

	array<String^> ^Func = gcnew array<String^>(this->FullPath->Count + 1);
	this->FullPath->CopyTo(Func, 0);
	Func[Func->Length - 1] = IMB->Name;

	int StackSize = GLua::glua_gettop(this->L);
	GLua::GetTableVal(this->L, Func);

	for each (auto A in Args)
		GLua::Push(this->L, A);

	if (GLua::glua_pcall(this->L, Args->Length, -1, 0))
		throw gcnew Exception(GLua::CheckString(this->L, GLua::glua_gettop(this->L)));

	int ArgC = GLua::glua_gettop(this->L) - StackSize;
	if (ArgC != 0)
		if (ArgC == 1)
			O = GLua::Get(this->L, -1);
		else throw gcnew NotImplementedException("TODO: Multiple return arguments");

	GLua::PopStackCount(this->L);
	GLua::Unlock(this->L);

	return true;
}