#ifndef GARRYSMOD_LUA_LUABASE_H
#define GARRYSMOD_LUA_LUABASE_H

#include <stddef.h>
#include <Types.h>

namespace GarrysMod 
{
	struct lua_State;
	typedef int (__stdcall *CFunc)(lua_State *L);

	public class ILuaBase {
		public:
			virtual int				Top( void ) = 0;
			virtual void			Push( int iStackPos ) = 0;
			virtual void			Pop( int iAmt  ) = 0;
			virtual void			GetTable( int iStackPos ) = 0;
			virtual void			GetField( int iStackPos, const char* strName ) = 0;
			virtual void			SetField( int iStackPos, const char* strName ) = 0;
			virtual void			CreateTable() = 0;
			virtual void			SetTable( int i ) = 0;
			virtual void			SetMetaTable( int i ) = 0;
			virtual bool			GetMetaTable( int i ) = 0;
			virtual void			Call( int iArgs, int iResults ) = 0;
			virtual int				PCall( int iArgs, int iResults, int iErrorFunc ) = 0;
			virtual int				Equal( int iA, int iB ) = 0;
			virtual int				RawEqual( int iA, int iB ) = 0;
			virtual void			Insert( int iStackPos ) = 0;
			virtual void			Remove( int iStackPos ) = 0;
			virtual int				Next( int iStackPos ) = 0;
			virtual void*			NewUserdata( unsigned int iSize ) = 0;
			virtual void			ThrowError( const char* strError ) = 0;
			virtual void			CheckType( int iStackPos, int iType ) = 0;
			virtual void			ArgError( int iArgNum, const char* strMessage ) = 0;
			virtual void			RawGet( int iStackPos ) = 0;
			virtual void			RawSet( int iStackPos ) = 0;
			virtual const char*		GetString( int iStackPos , unsigned int* iOutLen  ) = 0;
			virtual double			GetNumber( int iStackPos ) = 0;
			virtual bool			GetBool( int iStackPos ) = 0;
			virtual CFunc			GetCFunction( int iStackPos  ) = 0;
			virtual void*			GetUserdata( int iStackPos  ) = 0;
			virtual void			PushNil() = 0;
			virtual void			PushString( const char* val, unsigned int iLen  ) = 0;
			virtual void			PushNumber( double val ) = 0;
			virtual void			PushBool( bool val ) = 0;
			virtual void			PushCFunction( CFunc val ) = 0;
			virtual void			PushCClosure( CFunc val, int iVars ) = 0;
			virtual void			PushUserdata( void* ) = 0;
			virtual int				ReferenceCreate() = 0;
			virtual void			ReferenceFree( int i ) = 0;
			virtual void			ReferencePush( int i ) = 0;
			virtual void			PushSpecial( int iType ) = 0;
			virtual bool			IsType( int iStackPos, int iType ) = 0;
			virtual int				GetType( int iStackPos ) = 0;
			virtual const char*		GetTypeName( int iType ) = 0;
			virtual void			CreateMetaTableType( const char* strName, int iType ) = 0;
			virtual const char*		CheckString( int iStackPos  ) = 0;
			virtual double			CheckNumber( int iStackPos  ) = 0;

	};

	public enum class SPECIAL : int {
		GLOB,
		ENV,
		REG,
	};

	// TODO: Make full lua_State port from Lua instead of that retarded ignore header
	public struct lua_State {
	public:
		unsigned char _ignore_this_common_lua_header_[69];
		GarrysMod::ILuaBase* luabase;
	};

	public ref struct UserData {
	public:
		void* data;
		unsigned char type;
	};
}
#endif 