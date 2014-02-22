#include "GLua.h"
#include "gISurface.h"

namespace GarrysMod {
	void gISurface::Init(vgui::ISurface* S) {
		this->Surf = S;
	}

	gISurface::gISurface() {
		this->Init(Source::GetInterface<vgui::ISurface>(L"vguimatsurface.dll", VGUI_SURFACE_INTERFACE_VERSION));
	}

	gISurface::gISurface(vgui::ISurface* S) {
		this->Init(S);
	}

	gISurface::~gISurface() {
	}


	void gISurface::DrawSetColor(gColor ^C) {
		Surf->DrawSetColor(*C->Clr);
	}

	void gISurface::DrawSetColor(int R, int G, int B, int A) {
		Surf->DrawSetColor(R, G, B, A);
	}

	void gISurface::DrawLine(int X1, int Y1, int X2, int Y2) {
		Surf->DrawLine(X1, Y1, X2, Y2);
	}

}