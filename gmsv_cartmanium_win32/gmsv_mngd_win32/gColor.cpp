#include "gColor.h"

namespace GarrysMod {
	void gColor::Init(int R, int G, int B, int A) {
		Clr = new Color(R, G, B, A);
	}

	gColor::gColor() {
		Init(255, 255, 255, 255);
	}
	
	gColor::gColor(int R, int G, int B) {
		Init(R, G, B, 255);
	}

	gColor::gColor(int R, int G, int B, int A) {
		Init(R, G, B, A);
	}

	gColor::~gColor() {
		delete Clr;
	}
}