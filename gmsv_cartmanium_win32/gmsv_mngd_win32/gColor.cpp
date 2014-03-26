#include "GColor.h"

namespace GarrysMod {
	void GColor::Init(int R, int G, int B, int A) {
		Clr = new Color(R, G, B, A);
	}

	GColor::GColor() {
		Init(255, 255, 255, 255);
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
}