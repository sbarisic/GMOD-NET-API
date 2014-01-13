using GarrysMod;
using RGiesecke.DllExport;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System;

namespace gmsv_cartmanium_win32 {
	[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
	public unsafe delegate int CFunc(lua_State* L);

	public unsafe class ST {
		[DllImport("Kernel32.dll")]
		public static extern bool AllocConsole();

		public static void PushCFunction(lua_State* L, CFunc F) {
			void* f = Marshal.GetFunctionPointerForDelegate(F).ToPointer();
			GLua.PushCFunction(L, f);
		}

		public static void CreateGlobalTable(lua_State* L, string Name) {
			GLua.PushSpecial(L, SPECIAL.GLOB);
			GLua.PushString(L, Name);
			GLua.CreateTable(L);
			GLua.SetTable(L, -3);
		}

		public static void SetGlobalTableFunc(lua_State* L, string TableName, string FunctionName, CFunc F) {
			GLua.PushSpecial(L, SPECIAL.GLOB);
			GLua.PushString(L, TableName);
			GLua.GetTable(L, -2);
			GLua.PushString(L, FunctionName);
			PushCFunction(L, F);
			GLua.SetTable(L, -3);
		}
	}

	public unsafe class Cartmanium {
		[DllExport("gmod13_open", CallingConvention.Cdecl)]
		public static int Open(lua_State* L) {
			Cart = new Cart(L);

			GLua.PushSpecial(L, SPECIAL.GLOB);
			GLua.PushString(L, "print");
			GLua.GetTable(L, -2);
			GLua.PushString(L, "C# Module loaded!");
			GLua.Call(L, 1, 0);
			return 0;
		}

		static Cart Cart;

		[DllExport("gmod13_close", CallingConvention.Cdecl)]
		public static int Close(lua_State* L) {
			Cart.Close(L);
			return 0;
		}
	}

	public unsafe class Cart {
		public Cart(lua_State* L) {
			ST.CreateGlobalTable(L, "Cart");
			ST.SetGlobalTableFunc(L, "Cart", "AllocConsole", (l) => {
				GLua.PushBool(l, ST.AllocConsole());
				return 1;
			});

			ST.SetGlobalTableFunc(L, "Cart", "Console", (l) => {
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

			ST.SetGlobalTableFunc(L, "Cart", "Test", (l) => {

				return 0;
			});
		}

		public void Close(lua_State* L) {

		}
	}
}