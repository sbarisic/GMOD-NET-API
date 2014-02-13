using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using GarrysMod;

namespace gmcl_steamapi_win32 {

	public unsafe static class SteamAPILoader {

		[RGiesecke.DllExport.DllExport("gmod13_open", CallingConvention.Cdecl)]
		public static int gmod13_open(lua_State* L) {
			try {

				GLua.CreateClassLib(L, typeof(SteamAPI));
				GLua.Utils.print(L, "SteamAPI loaded");

			} catch (Exception E) {

				GLua.Utils.print(L, E.Message);
				GLua.Utils.print(L, "SteamAPI failed to load");

			}
			return 0;
		}

		[RGiesecke.DllExport.DllExport("gmod13_close", CallingConvention.Cdecl)]
		public static int gmod13_close(lua_State* L) {
			return 0;
		}
	}

	public unsafe static class SteamAPI {
		public static gSteamAPI API = new gSteamAPI();

		public static int SetOverlayPos(lua_State* L) {
			return SetOverlayNotificationPosition(L);
		}

		public static int SetOverlayNotificationPosition(lua_State* L) {
			try {
				int T = GLua.GetType(L, 1);
				string TName = GLua.GetTypeName(L, T);
				if (TName == "number" || TName == "string") {
					int Pos = 2;
					if (TName == "string") {
						string Arg = GLua.GetString(L, -1, null);
						switch (Arg) {
							case "top_left":
							Pos = 1;
							break;
							case "top_right":
							Pos = 2;
							break;
							case "bottom_right":
							Pos = 3;
							break;
							case "bottom_left":
							Pos = 4;
							break;
						}
					} else
						Pos = (int)GLua.GetNumber(L, -1);
					API.SetOverlayNotificationPosition(Pos);
				} else
					GLua.ThrowError(L, string.Format("Expected number or string, got {0}", GLua.GetTypeName(L, T)));
			} catch (Exception E) {
				GLua.ThrowError(L, E.Message);
			}
			return 0;
		}
	}
}