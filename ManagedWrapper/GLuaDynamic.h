#pragma once

using namespace System;
using namespace System::Dynamic;
using namespace System::Collections::Generic;

public ref class GLuaDynamic : DynamicObject  {
private:
	List<String^> ^FullPath;
	int DynamicType;

	IntPtr L;

	void Init(IntPtr);

public:
	GLuaDynamic(IntPtr);
	GLuaDynamic(IntPtr, ...array<String^> ^FullPath);

	virtual bool TryGetMember(GetMemberBinder^, Object^%) override;
	virtual bool TryInvokeMember(InvokeMemberBinder^, array<Object^> ^, Object^%) override;

	void Dbg();
};

