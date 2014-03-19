using GarrysMod;
using GarrysMod.Utilities;
using System.Runtime.InteropServices;
using System;

namespace gmsv_cartmanium_win32 {
	public unsafe class Kernel32 {
		[DllImport("Kernel32.dll")]
		public static extern bool AllocConsole();
	}

	public unsafe class Cartmanium {
		[RGiesecke.DllExport.DllExport("gmod13_open", CallingConvention.Cdecl)]
		public static int Open(lua_State* L) {
			ResourceLoader.RegisterAssembly(Properties.Resources.ResourceManager, OverrideName: "Wrapper");
			Kernel32.AllocConsole();
			return Module.Open(L);
		}

		[RGiesecke.DllExport.DllExport("gmod13_close", CallingConvention.Cdecl)]
		public static int Close(lua_State* L) {
			return Module.Close(L);
		}
	}

	public unsafe static class Module {
		//static gSteamAPI SteamAPI = new gSteamAPI();

		public static int Open(lua_State* L) {
			GLua.CreateType(L, typeof(Cart));

			GLua.Utils.print(L, string.Format("Test with ManagedWrapper v{0} loaded", ManagedWrapper.VERSION));
			return 0;
		}

		public static int Close(lua_State* L) {
			return 0;
		}
	}

	public unsafe static class Cart {
		static int Calls = 0;

		public static int __tostring(lua_State* L) {
			GLua.PushString(L, "IT'S A MOTHERFUCKING CART TABLE!");
			return 1;
		}

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

		public static int Test(lua_State* L) {
			string S = GLua.CheckString(L, 1);
			System.Console.WriteLine(">> {0}", S);
			return 0;
		}

		public static int ReadLine(lua_State* L) {
			GLua.PushString(L, System.Console.ReadLine());
			return 1;
		}

		public static int CallCounter(lua_State* L) {
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