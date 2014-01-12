using GarrysMod;
using RGiesecke.DllExport;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace gmsv_cartmanium_win32 {
	public unsafe class Cartmanium {
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		delegate int CFunc(lua_State* L);

		[DllExport("gmod13_open", CallingConvention.Cdecl)]
		public static int Open(lua_State* L) {
			void* F = Marshal.GetFunctionPointerForDelegate(new CFunc((l) => {
				GLua.PushString(l, "GMODAPI_TEST_PASS: [CODE 100] OKAY");
				return 1;
			})).ToPointer();

			GLua.PushSpecial(L, SPECIAL.GLOB);
			GLua.PushString(L, "GMODAPI_TEST", 0);
			GLua.PushCFunction(L, F);
			GLua.SetTable(L, -3);
			return 0;
		}

		[DllExport("gmod13_close", CallingConvention.Cdecl)]
		public static int Close(lua_State* L) {
			return 0;
		}
	}
}