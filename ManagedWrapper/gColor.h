#pragma once

#include <Color.h>

namespace GarrysMod {

	public ref class GColor {
	private:
		void Init(int R, int G, int B, int A);

	public:
		Color* Clr;

		GColor();
		GColor(const Color* Clr);
		GColor(int C[]);
		GColor(array<int> ^C);
		GColor(int R, int G, int B);
		GColor(int R, int G, int B, int A);
		~GColor();
		
#define GetClrAtomicH(C) int C ()

		GetClrAtomicH(r);
		GetClrAtomicH(g);
		GetClrAtomicH(b);
		GetClrAtomicH(a);

		virtual System::String^ ToString() override;
	};

}