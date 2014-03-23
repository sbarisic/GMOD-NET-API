using System;
using GarrysMod;

public unsafe class SteamOverlayNotificationPos : INetScript {
	public static gSteamAPI API;
	
	public SteamOverlayNotificationPos() {
		this.ID = "BottomRightNotifyPos"; // Do not put anything here besides the script ID! (I'll fuck you up if you do)
	}

	public override void Open(lua_State* L) { // Initialize everything here
		API = new gSteamAPI();
		API.SetOverlayNotificationPosition(3); // 1 is top left, it goes clockwise to 4
	}

	public override void Close(lua_State* L) {
		API.SetOverlayNotificationPosition(2);
	}
}