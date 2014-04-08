#pragma once

#include "gColor.h"

namespace GarrysMod {
	public ref class GISurface {
	private:
		void Init(vgui::ISurface*);

	public:
		vgui::ISurface* Surf;

		GISurface();
		GISurface(vgui::ISurface*);
		~GISurface();

		void DrawSetColor(GColor ^C);
		void DrawSetColor(int R, int G, int B, int A);

		void DrawLine(int X1, int Y1, int X2, int Y2);

	};
}