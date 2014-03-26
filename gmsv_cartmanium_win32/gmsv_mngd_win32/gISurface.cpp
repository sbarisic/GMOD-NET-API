#include "GLua.h"
#include "GISurface.h"

namespace GarrysMod {
	void GISurface::Init(vgui::ISurface* S) {
		this->Surf = S;
	}

	GISurface::GISurface() {
		this->Init(Source::GetInterface<vgui::ISurface>(L"vguimatsurface.dll", VGUI_SURFACE_INTERFACE_VERSION));
	}

	GISurface::GISurface(vgui::ISurface* S) {
		this->Init(S);
	}

	GISurface::~GISurface() {
	}


	void GISurface::DrawSetColor(GColor ^C) {
		Surf->DrawSetColor(*C->Clr);
	}

	void GISurface::DrawSetColor(int R, int G, int B, int A) {
		Surf->DrawSetColor(R, G, B, A);
	}

	void GISurface::DrawLine(int X1, int Y1, int X2, int Y2) {
		Surf->DrawLine(X1, Y1, X2, Y2);
	}

}