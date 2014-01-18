using GarrysMod;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System;

namespace gmsv_cartmanium_win32 {
	public unsafe class Kernel32 {
		[DllImport("Kernel32.dll")]
		public static extern bool AllocConsole();
	}

	public unsafe class Cartmanium {
		[RGiesecke.DllExport.DllExport("gmod13_open", CallingConvention.Cdecl)]
		public static int Open(lua_State* L) {
			GLua.CreateGlobalTable(L, "Cart");
			GLua.SetGlobalTableGFunc(L, "Cart", "AllocConsole", (l) => {
				GLua.PushBool(l, Kernel32.AllocConsole());
				return 1;
			});

			GLua.SetGlobalTableGFunc(L, "Cart", "Console", (l) => {
				int ArgCount = GLua.Top(l);
				for (int i = 0; i < ArgCount; i++) {
					var S = GLua.GetString(l, i + 1, (uint*)0);
					Console.Write(S);
					if (i + 1 < ArgCount)
						Console.Write(" ");
				}
				GLua.Pop(l, ArgCount);
				Console.WriteLine();
				return 0;
			});

			GLua.SetGlobalTableGFunc(L, "Cart", "TEST", GLua.Utils.TEST);
			GLua.SetGlobalTableGFunc(L, "Cart", "TEST2", GLua.Utils.TEST2);

			Kernel32.AllocConsole();
			try {
				new Cart().Register(L);
			} catch (Exception E) {
				Console.WriteLine(E.Message);
			}


			GLua.Utils.print(L, "Module loaded!");
			return 0;
		}

		[RGiesecke.DllExport.DllExport("gmod13_close", CallingConvention.Cdecl)]
		public static int Close(lua_State* L) {
			return 0;
		}
	}

	public unsafe class Cart : LuaLibrary {
		public int TESTEES(lua_State* L) {
			GLua.PushString(L, "HEY! YOU! HELLO THERE!");
			return 1;
		}
	}
}