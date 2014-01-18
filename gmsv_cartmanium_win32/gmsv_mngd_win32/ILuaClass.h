namespace GarrysMod {
	public ref class ILuaClass {
	public:
		virtual void Register(lua_State* L);
	};
}