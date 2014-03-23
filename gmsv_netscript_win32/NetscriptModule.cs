using Microsoft.CSharp;
using System;
using System.CodeDom;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GarrysMod;

namespace gmsv_netscript_win32 {
	internal unsafe class Kernel32 {
		[DllImport("Kernel32.dll")]
		public static extern bool AllocConsole();
	}

	public unsafe static class NetscriptModule {
		[RGiesecke.DllExport.DllExport("gmod13_open", CallingConvention.Cdecl)]
		public static int Open(lua_State* L) {
			return Module.Open(L);
		}

		[RGiesecke.DllExport.DllExport("gmod13_close", CallingConvention.Cdecl)]
		public static int Close(lua_State* L) {
			return Module.Close(L);
		}
	}

	internal unsafe static class Module {
		public static int Open(lua_State* L) {
			try {
				GLua.CreateLib(L, typeof(Netscript));
				NetscriptDomain.ReloadAll(L);
			} catch (Exception E) {
				GLua.gluaL_error(L, E.Message);
			}
			return 0;
		}

		public static int Close(lua_State* L) {
			return 0;
		}
	}

	public unsafe static class Netscript {
		public static int Load(lua_State* L) {
			GLua.PushBool(L, NetscriptDomain.Load(L, GLua.CheckString(L, -1)));
			return 1;
		}

		public static int Unload(lua_State* L) {
			GLua.PushBool(L, NetscriptDomain.Unload(L, GLua.CheckString(L, -1)));
			return 1;
		}

		public static int Reload(lua_State* L) {
			NetscriptDomain.ReloadAll(L);
			return 0;
		}
	}
}