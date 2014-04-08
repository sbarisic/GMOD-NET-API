#include "stdafx.h"

namespace GarrysMod {
#define CLR this->Clr
	void GColor::Init(int R, int G, int B, int A) {
		Clr = new Color(R, G, B, A);
	}

	GColor::GColor() {
		Init(255, 255, 255, 255);
	}

	GColor::GColor(const Color* Col) {
		Init(Col->r(), Col->g(), Col->b(), Col->a());
	}

	GColor::GColor(int C[]) {
		Init(C[0], C[1], C[2], C[3]);
	}
	
	GColor::GColor(array<int> ^C) {
		if (C->Length == 4)
			Init(C[0], C[1], C[2], C[3]);
		else throw gcnew System::Exception("Invalid color array!");
	}

	GColor::GColor(int R, int G, int B) {
		Init(R, G, B, 255);
	}

	GColor::GColor(int R, int G, int B, int A) {
		Init(R, G, B, A);
	}

	GColor::~GColor() {
		delete Clr;
	}

/*#define PUSHCLR(L, C) GLua::glua_pushnumber(L, CLR-> C ())
	int GColor::Push(System::IntPtr L) {
		GLua::GetTableVal(L, "Color");
		PUSHCLR(L, r);
		PUSHCLR(L, g);
		PUSHCLR(L, b);
		PUSHCLR(L, a);
		GLua::Call(L, 4, 1);
		return 1;
	}*/

#define GetClrAtomic(C) int GColor:: C () { return CLR-> C (); }

	GetClrAtomic(r)
	GetClrAtomic(g)
	GetClrAtomic(b)
	GetClrAtomic(a)

	System::String^ GColor::ToString() {
		return System::String::Format("R{0} G{1} B{2} A{3}", CLR->r(), CLR->g(), CLR->b(), CLR->a());
	}

#undef CLR
}