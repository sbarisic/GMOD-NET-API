// Add this .cs file to your project
using System;
using System.IO;
using System.Reflection;
using System.Resources;

namespace GarrysMod.Utilities {
	internal static class ResourceLoader {
		public static void RegisterAssembly(ResourceManager ResMgr, string AsmName = "ManagedWrapper", string OverrideName = "") {
			AppDomain.CurrentDomain.AssemblyResolve += (S, E) => {
				try {
					if (E.Name.Split(',')[0] != AsmName)
						return null;
					string Name = OverrideName.Length != 0 ? OverrideName : AsmName;
					object ResObj = ResMgr.GetObject(Name);
					AppDomain.CurrentDomain.SetupInformation.ShadowCopyFiles = "true";
					string TempFilename = Path.GetTempFileName();
					File.WriteAllBytes(TempFilename, (byte[])ResObj);
					Assembly MWAsm = Assembly.LoadFrom(TempFilename);
					AppDomain.CurrentDomain.SetupInformation.ShadowCopyFiles = "false";
					return MWAsm;
				} catch (Exception) {
					throw;
				}

			};
		}
	}
}