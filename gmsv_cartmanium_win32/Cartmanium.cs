using GarrysMod;
using GType = GarrysMod.Lua.Type;
using GarrysMod.Utilities;
using System.Runtime.InteropServices;
using System;
using System.Text;

namespace gmsv_cartmanium_win32 {
	public unsafe class Kernel32 {
		[DllImport("Kernel32.dll")]
		public static extern bool AllocConsole();
	}

	public unsafe class Cartmanium {
		[RGiesecke.DllExport.DllExport("gmod13_open", CallingConvention.Cdecl)]
		public static int Open(IntPtr L) {
			Kernel32.AllocConsole(); Console.Title = "Garry's Mod";
			return Module.Open(L);
		}

		[RGiesecke.DllExport.DllExport("gmod13_close", CallingConvention.Cdecl)]
		public static int Close(IntPtr L) {
			return Module.Close(L);
		}
	}

	public unsafe static class Module {
		public static int Open(IntPtr L) {
			GLua.AtPanic(L, (I) => {
				throw new Exception(GLua.CheckString(I, -1));
				Environment.Exit(1);
			});

			GLua.Utils.DoString(L, "_G.SpewMsg = function() end");

			bool InHook = false;
			GLua.Utils.HookOutput(new GSpewOutputFunc((int T, string Str, int R, int G, int B, int A) => {
				if (InHook || L == IntPtr.Zero)
					return;
				InHook = true;

				int StackSize = GLua.glua_gettop(L);

				GLua.Lock(L);
				GLua.PushSpecial(L, SPECIAL.GLOB);
				GLua.glua_getfield(L, -1, "SpewMsg");
				GLua.glua_pushinteger(L, R);
				GLua.glua_pushinteger(L, G);
				GLua.glua_pushinteger(L, B);
				GLua.glua_pushinteger(L, A);
				GLua.glua_pushstring(L, Str);
				if (GLua.PCall(L, 5, 0, 0) != 0)
					GLua.Utils.print(L, GLua.CheckString(L, -1));

				GLua.Pop(L, GLua.glua_gettop(L) - StackSize);
				GLua.Unlock(L);
				InHook = false;
			}));

			GLua.CreateType(L, typeof(Cart));

			GLua.GetTableVal(L, "_G", "SpewMsg");
			GLua.glua_dump_writer = (LPtr, Dta, Size, Ud) => {
				Console.WriteLine("Wee! Works!\n>> \"{0}\"", Dta);
				return 0;
			};
			Console.WriteLine(GLua.glua_dump(L, IntPtr.Zero));

			GLua.Utils.print(L, string.Format("Test with ManagedWrapper v{0} loaded", ManagedWrapper.VERSION), false);
			return 0;
		}

		public static int Close(IntPtr L) {
			GLua.Utils.UnhookOutput();
			return 0;
		}
	}

	public unsafe static class Cart {
		public static int __tostring(IntPtr L) {
			GLua.PushString(L, "IT'S A MOTHERFUCKING CART TABLE!");
			return 1;
		}

		public static int Console(IntPtr L) {
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

		public static int AllocConsole(IntPtr L) {
			GLua.PushBool(L, Kernel32.AllocConsole());
			return 1;
		}

		public static int Break(IntPtr L) {
			if (System.Diagnostics.Debugger.IsAttached)
				System.Diagnostics.Debugger.Break();
			return 0;
		}
	}
}