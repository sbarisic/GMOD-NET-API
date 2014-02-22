using GarrysMod;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Collections.Generic;
using System;
using System.Reflection;

namespace gmsv_cartmanium_win32 {
	public unsafe class Kernel32 {
		[DllImport("Kernel32.dll")]
		public static extern bool AllocConsole();
	}

	public unsafe class Cartmanium {
		static gSteamAPI SteamAPI = new gSteamAPI();

		[RGiesecke.DllExport.DllExport("gmod13_open", CallingConvention.Cdecl)]
		public static int Open(lua_State* L) {
			Kernel32.AllocConsole();

			GLua.CreateClassLib(L, typeof(Cart));

			GLua.Utils.print(L, "Module v{0} loaded!", ManagedWrapper.VERSION);
			return 0;
		}

		[RGiesecke.DllExport.DllExport("gmod13_close", CallingConvention.Cdecl)]
		public static int Close(lua_State* L) {
			return 0;
		}
	}

	public unsafe static class Cart {
		static int Calls = 0;

		public static int Console(lua_State* L) {
			int ArgCount = GLua.Top(L);
			for (int i = 0; i < ArgCount; i++) {
				var S = GLua.GetString(L, i + 1, (uint*)0);
				System.Console.Write(S);
				if (i + 1 < ArgCount)
					System.Console.Write(" ");
			}
			GLua.Pop(L, ArgCount);
			System.Console.WriteLine();
			return 0;
		}

		public static int AllocConsole(lua_State* L) {
			GLua.PushBool(L, Kernel32.AllocConsole());
			return 1;
		}

		public static int ReadLine(lua_State* L) {
			GLua.PushString(L, System.Console.ReadLine());
			return 1;
		}

		public static int CallTest(lua_State* L) {
			Calls++;
			System.Console.WriteLine("Call: {0}", Calls);
			return 0;
		}

		public static int Break(lua_State* L) {
			if (System.Diagnostics.Debugger.IsAttached)
				System.Diagnostics.Debugger.Break();
			return 0;
		}

		public static int SurfaceTest(lua_State* L) {
			var Surface = new gISurface();
			gColor DrawClr = new gColor(0, 255, 0);
			Surface.DrawSetColor(DrawClr);
			Surface.DrawLine(0, 0, 100, 100);
			DrawClr.Dispose();
			return 0;
		}
	}
}