using GarrysMod;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Collections.Generic;
using System;

namespace gmsv_cartmanium_win32 {
	public unsafe class Kernel32 {
		[DllImport("Kernel32.dll")]
		public static extern bool AllocConsole();
	}

	public unsafe class Cartmanium {
		[RGiesecke.DllExport.DllExport("gmod13_open", CallingConvention.Cdecl)]
		public static int Open(lua_State* L) {
			Kernel32.AllocConsole();

			GLua.Keepalive.AddList("Cart", GLua.CreateClassLib(L, typeof(Cart)));

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

		public static int TEST(lua_State* L) {
			Calls++;
			System.Console.WriteLine("Call: {0}", Calls);
			return 0;
		}
	}
}