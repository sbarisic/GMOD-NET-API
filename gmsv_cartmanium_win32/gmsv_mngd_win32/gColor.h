#pragma once

#include <Color.h>

namespace GarrysMod {

	public ref class gColor {
	private:
		void Init(int R, int G, int B, int A);

	public:
		Color* Clr;

		gColor();
		gColor(int R, int G, int B);
		gColor(int R, int G, int B, int A);
		~gColor();
	};

}