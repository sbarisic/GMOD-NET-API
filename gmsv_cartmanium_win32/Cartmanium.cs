using GarrysMod;
using GType = GarrysMod.Lua.Type;
using GarrysMod.Utilities;
using System.Runtime.InteropServices;
using System;
using System.Text;
using ImpromptuInterface;

namespace gmsv_cartmanium_win32 {
	public unsafe class Kernel32 {
		[DllImport("Kernel32.dll")]
		public static extern bool AllocConsole();
	}

	public unsafe class Cartmanium {
		[RGiesecke.DllExport.DllExport("gmod13_open", CallingConvention.Cdecl)]
		public static int Open(IntPtr L) {
			L.glua_settop(0); // Remove weird constants
			L.PushGFunction(GLua.EmptyGFunc);
			L.PushGFunction(GLua.EmptyGFunc);
			L.PushGFunction(GLua.EmptyGFunc);
			L.PushGFunction(GLua.EmptyGFunc);
			L.PushGFunction(GLua.EmptyGFunc);

			Kernel32.AllocConsole();
			Console.Title = "Garry's Mod";

			GLuaDynamic _GD = new GLuaDynamic(L);
			dynamic _G = _GD;

			_GD.Dbg();
			L.CreateType(typeof(Cart));

			_GD.Dbg();
			GLua.Utils.DoString(L, "TESTVAR = 256; function TESTFUNC(...) Cart.Console(...) print(...) end");

			_GD.Dbg();
			_G.TESTFUNC("Hello from DLR! ", 42);
			_G.TESTFUNC(_G.TESTVAR);

			L.SetGlobalTableGFunc("_G", "SpewMsg", GLua.EmptyGFunc);

			bool InHook = false;
			GLua.Utils.HookOutput(new GSpewOutputFunc((int T, string Str, int R, int G, int B, int A) => {
				if (InHook)
					return;
				InHook = true;

				L.Locked(() => {
					L.PushSpecial(SPECIAL.GLOB);
					L.glua_getfield(-1, "SpewMsg");
					L.glua_pushinteger(R);
					L.glua_pushinteger(G);
					L.glua_pushinteger(B);
					L.glua_pushinteger(A);
					L.glua_pushstring(Str);
					if (L.PCall(5, 0, 0) != 0)
						GLua.Utils.print(L, L.CheckString(-1));
				});
				InHook = false;
			}));

			L.Locked(() => {
				if (L.gluaL_loadstring("function TEST_DUMP() print(\"Hello universe!\") end") != 0)
					Console.WriteLine(L.CheckString(-1));
				if (L.glua_pcall(0, 0, 0) != 0)
					Console.WriteLine(L.CheckString(-1));
			});

			/*L.GetTableVal("_G", "TEST_DUMP");
			L.glua_dump((LPtr, Dump, Size, UData) => { // TODO: Fix, what is this shit.
				string Str = Marshal.PtrToStringAnsi(Dump, (int)Size);
				Console.WriteLine("{0} >> \"{1}\"", Size, Str);
				return 0;
			});*/

			GLua.Utils.print(L, string.Format("Test with ManagedWrapper v{0} loaded", ManagedWrapper.VERSION), false);
			return 0;
		}

		[RGiesecke.DllExport.DllExport("gmod13_close", CallingConvention.Cdecl)]
		public static int Close(IntPtr L) {
			GLua.Utils.UnhookOutput();
			return 0;
		}
	}

	public unsafe static class Cart {
		public static int __tostring(IntPtr L) {
			L.PushString("IT'S A MOTHERFUCKING CART TABLE!");
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