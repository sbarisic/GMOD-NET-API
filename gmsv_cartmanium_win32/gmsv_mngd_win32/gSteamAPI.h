#pragma once
//#include <steam\isteamutils.h>
#include <steam\steam_api.h>

#pragma comment(lib, "steam_api.lib")

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