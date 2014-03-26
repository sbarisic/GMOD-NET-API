#pragma once

#include <Color.h>

namespace GarrysMod {

	public ref class GColor {
	private:
		void Init(int R, int G, int B, int A);

	public:
		Color* Clr;

		GColor();
		GColor(int R, int G, int B);
		GColor(int R, int G, int B, int A);
		~GColor();
	};

}