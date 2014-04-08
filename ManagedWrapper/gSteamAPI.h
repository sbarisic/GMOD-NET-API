#pragma once

#include <steam\steam_api.h>

namespace GarrysMod {
	public ref class GSteamAPI {
	internal:
		ISteamUtils* SUtils;

	public:
		GSteamAPI();
		~GSteamAPI();

		void SetOverlayNotificationPosition(int Pos);
	};
}