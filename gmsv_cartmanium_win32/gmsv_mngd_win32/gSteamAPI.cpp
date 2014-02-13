#include "GLua.h"

using namespace System;
using namespace GarrysMod;

gSteamAPI::gSteamAPI() {
	if (SteamAPI_Init()) {
		auto SC = SteamClient();
		auto SHPipe = GetHSteamPipe();

		this->SUtils = SC->GetISteamUtils(SHPipe, STEAMUTILS_INTERFACE_VERSION);

		if (this->SUtils == NULL)
			throw gcnew Exception("gSteamAPI is NULL!");
	} else 
		printf("%s\n", "Could not initialize SteamAPI!");
}

gSteamAPI::~gSteamAPI() {
	SteamAPI_Shutdown();
}

void gSteamAPI::SetOverlayNotificationPosition(int Pos) {
	if (this->SUtils == NULL) return;

	auto P = ENotificationPosition::k_EPositionTopRight;

	if (Pos == 4) P = ENotificationPosition::k_EPositionBottomLeft;
	else if (Pos == 3) P = ENotificationPosition::k_EPositionBottomRight;
	else if (Pos == 1) P = ENotificationPosition::k_EPositionTopLeft;
	else if (Pos == 2) P = ENotificationPosition::k_EPositionTopRight;

	this->SUtils->SetOverlayNotificationPosition(P);
}