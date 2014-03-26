using Microsoft.CSharp;
using Microsoft.CSharp.RuntimeBinder;
using System;
using System.CodeDom;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using GarrysMod;
using System.Windows.Forms;

namespace gmsv_netscript_win32 {
	internal unsafe static class NetscriptDomain {
		private static bool Initialized = false;

		public static List<INetScript> LoadedScripts = new List<INetScript>();
		public static string ScriptDir = Path.Combine(Application.StartupPath, "garrysmod", "netscript");

		public static void Init() {
			if (Initialized)
				return;
			Initialized = true;
			AppDomain.CurrentDomain.AssemblyResolve += (S, E) => {
				string AsmName = E.Name.Split(',')[0];
				if (AsmName == "gmsv_netscript_win32")
					return Assembly.GetExecutingAssembly();
				string ScriptDirBin = Path.Combine(ScriptDir, "bin", AsmName + ".dll");
				if (File.Exists(ScriptDirBin))
					return Assembly.LoadFile(ScriptDirBin);
				return null;
			};
		}

		public static Assembly LoadFile(string Pth) {
			if (!File.Exists(Pth))
				throw new Exception(string.Format("File does not exist \"{0}\"", Pth));
			string Code = File.ReadAllText(Pth);

			CSharpCodeProvider Provider = new CSharpCodeProvider();

			CompilerParameters CParams = new CompilerParameters();
			CParams.GenerateExecutable = !(CParams.GenerateInMemory = true);
			CParams.ReferencedAssemblies.Add("System.dll");
			CParams.ReferencedAssemblies.Add("System.Windows.Forms.dll");
			CParams.ReferencedAssemblies.Add(Path.Combine(Application.StartupPath, "ManagedWrapper.dll"));
			CParams.ReferencedAssemblies.Add(Assembly.GetExecutingAssembly().Location);
			CParams.CompilerOptions = "/unsafe";

			CompilerResults CRes = Provider.CompileAssemblyFromSource(CParams, Code);
			if (CRes.Errors.HasErrors) {
				StringBuilder Errors =
					new StringBuilder(string.Format("{0} errors found in \"{1}\"\n", CRes.Errors.Count, Path.GetFileName(Pth)));
				foreach (CompilerError Err in CRes.Errors)
					Errors.AppendFormat("Ln {0} Col {1}; {2}\n", Err.Line, Err.Column, Err.ErrorText);
				throw new Exception(Errors.ToString().Trim());
			}
			return CRes.CompiledAssembly;
		}

		public static INetScript[] ExecuteFile(IntPtr L, string Pth) {
			List<INetScript> INetScripts = new List<INetScript>();
			var FileAsm = LoadFile(Pth);
			Type[] Types = null;
			try {
				Types = FileAsm.GetTypes();
			} catch (ReflectionTypeLoadException E) {
				foreach (var Ex in E.LoaderExceptions)
					throw Ex;
			}
			foreach (var T in Types)
				if (T.BaseType == typeof(INetScript)) {
					INetScript INS = (INetScript)Activator.CreateInstance(T);
					INS.Filename = Pth;
					Unload(L, INS.ID);
					LoadedScripts.Add(INS);
					INetScripts.Add(INS);
				}
			return INetScripts.ToArray();
		}

		public static void Msg(IntPtr L, object O, params object[] OO) {
			string S = "[NETSCRIPT] " + O.ToString();
			if (OO != null)
				S = string.Format(S, OO);
			GLua.Utils.print(L, S, true);
		}

		public static bool Load(IntPtr L, string Pth, bool DoMsg = true) {
			Init();
			bool DidLoad = false;
			try {
				var Scripts = ExecuteFile(L, Pth);
				foreach (var S in Scripts) {
					S.Open(L);
					if (DoMsg)
						Msg(L, "Loaded \"{0}\" in \"{1}\"", S.ID, Path.GetFileName(S.Filename));
					DidLoad = true;
				}
			} catch (Exception E) {
				Msg(L, "ERROR: {0}", E.Message);
				Msg(L, "Failed to load \"{0}\"", Path.GetFileName(Pth));
			}
			return DidLoad;
		}

		public static bool Unload(IntPtr L, string ID, bool DoMsg = true) {
			INetScript[] Scripts = LoadedScripts.ToArray();
			LoadedScripts.Clear();
			bool DidUnload = false;
			for (int i = 0; i < Scripts.Length; i++) {
				if (Scripts[i].ID == ID) {
					try {
						Scripts[i].Close(L);
					} catch (Exception E) {
						Msg(L, "ERROR: {0}", E.Message);
					}
					if (DoMsg)
						Msg(L, "Unloaded \"{0}\" in \"{1}\"", ID, Path.GetFileName(Scripts[i].Filename));
					Scripts[i] = null;
					DidUnload = true;
				}
			}
			for (int i = 0; i < Scripts.Length; i++) if (Scripts[i] != null)
					LoadedScripts.Add(Scripts[i]);
			return DidUnload;
		}

		public static string[] LoadedScriptIDs() {
			List<string> StringNames = new List<string>();
			foreach (var LS in LoadedScripts)
				StringNames.Add(LS.ID);
			return StringNames.ToArray();
		}

		public static void ReloadAll(IntPtr L) {
			var LSIDs = LoadedScriptIDs();
			foreach (var LSID in LSIDs)
				Unload(L, LSID, false);
			foreach (var NetScr in Directory.GetFiles(ScriptDir, "*.cs", SearchOption.TopDirectoryOnly))
				Load(L, NetScr);
		}
	}
}

public unsafe class INetScript {
	public string ID, Filename;
	public bool Enabled = true;
	public virtual void Open(IntPtr L) {
	}
	public virtual void Close(IntPtr L) {
	}
}