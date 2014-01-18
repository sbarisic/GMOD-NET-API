#include "GLua.h"

namespace GarrysMod {
	public ref class GLua {
	private:
	public:
		ref class Utils {
		public:
			static void print(lua_State* L, System::String ^S);
			static void print(lua_State* L, System::String ^S, System::Boolean ToConsole);
			static int TEST(lua_State* L);
			static int TEST2(lua_State* L);
			static GarrysMod::Lua::ILuaExtended* ToExtended(GarrysMod::Lua::ILuaBase* B);
			static GarrysMod::Lua::ILuaExtended* ToExtended(lua_State* B);
		};
	};

	public ref class ILuaClass {
	private:
	public:
		virtual void Register(lua_State *L) {
			array<System::Reflection::MethodInfo^, 1> ^Methods = this->GetType()->GetMethods();
			for each (System::Reflection::MethodInfo ^MInfo in Methods) {
				
			}
		}
	};
}