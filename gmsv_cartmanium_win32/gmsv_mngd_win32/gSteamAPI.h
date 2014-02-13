//#include <steam\isteamutils.h>
#include <steam\steam_api.h>

#pragma comment(lib, "steam_api.lib")

namespace GarrysMod {
	public ref class gSteamAPI {
	internal:
		ISteamUtils* SUtils;

	public:
		gSteamAPI();
		~gSteamAPI();

		void SetOverlayNotificationPosition(int Pos);
	};
}