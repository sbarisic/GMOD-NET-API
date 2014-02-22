#pragma once

#include <Windows.h>
#include <vgui\ISurface.h>
#include <Color.h>
#include "gColor.h"

namespace GarrysMod {
	public ref class gISurface {
	private:
		void Init(vgui::ISurface*);

	public:
		vgui::ISurface* Surf;

		gISurface();
		gISurface(vgui::ISurface*);
		~gISurface();

		void DrawSetColor(gColor ^C);
		void DrawSetColor(int R, int G, int B, int A);

		void DrawLine(int X1, int Y1, int X2, int Y2);

	};
}