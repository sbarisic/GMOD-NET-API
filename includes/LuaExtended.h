#ifndef GARRYSMOD_LUA_LUAINTERFACE_H
#define GARRYSMOD_LUA_LUAINTERFACE_H

#define GMMODULE
#include "LuaBase.h"
#include "LuaCallback.h"
#include <string>

#undef LUA
#define LUA ((ILuaExtended*)(state->luabase))
#define LS(a) ((ILuaExtended*)(a->luabase))

namespace Bootil {
	class Buffer;
}

class Color;

#ifndef lua_h
typedef struct lua_Debug {
	int event;
	const char *name;			/* (n) */
	const char *namewhat;		/* (n) */
	const char *what;			/* (S) */
	const char *source;			/* (S) */
	int currentline;			/* (l) */
	int nups;					/* (u) number of upvalues */
	int linedefined;			/* (S) */
	int lastlinedefined;		/* (S) */
	char short_src[512];		/* (S) */
	/* private part */
	int i_ci;
} lua_Debug;
#endif

namespace GarrysMod {
	namespace Lua {
		class ILuaObject;

		public class ILuaExtended : public ILuaBase {
		public:
			virtual void PLACEHOLDER( ) = 0;
			virtual bool Init( ILuaCallback *, bool ) = 0;
			virtual void Shutdown( ) = 0;
			virtual void Cycle( ) = 0;
			virtual lua_State *GetLuaState( ) = 0;
			virtual ILuaObject *Global( ) = 0;
			virtual ILuaObject *GetObject( int index ) = 0;
			virtual void DELETE_ME_5437( int ) = 0;
			virtual void _DELETE_ME2466( int ) = 0;
			virtual void PushLuaObject( ILuaObject *obj ) = 0;
			virtual void PushLuaFunction( CFunc func ) = 0;
			virtual void LuaError( const char *err, int index ) = 0;
			virtual void TypeError( const char *name, int index ) = 0;
			virtual void CallInternal( int args, int rets ) = 0;
			virtual void CallInternalNoReturns( int args ) = 0;
			virtual bool CallInternalGetBool( int args ) = 0;
			virtual const char *CallInternalGetString( int args ) = 0;
			virtual bool CallInternalGet( int args, ILuaObject *obj ) = 0;
			virtual void _DELETE_ME( ILuaObject *, void * ) = 0;
			virtual void NewGlobalTable( const char *name ) = 0;
			virtual ILuaObject *NewTemporaryObject( ) = 0;
			virtual bool isUserData( int index ) = 0;
			virtual ILuaObject *GetMetaTableObject( const char *name, int type ) = 0;
			virtual ILuaObject *GetMetaTableObject( int index ) = 0;
			virtual ILuaObject *GetReturn( int index ) = 0;
			virtual bool IsServer( ) = 0;
			virtual bool IsClient( ) = 0;
			virtual bool IsDedicatedServer( ) = 0;
			virtual void DestroyObject( ILuaObject *obj ) = 0;
			virtual ILuaObject *CreateObject( ) = 0;
			virtual void SetMember( ILuaObject *table, ILuaObject *key, ILuaObject *value ) = 0;
			virtual void GetNewTable( ) = 0;
			virtual void SetMember( ILuaObject *table, float key ) = 0;
			virtual void SetMember( ILuaObject *table, float key, ILuaObject *value ) = 0;
			virtual void SetMember( ILuaObject *table, const char *key ) = 0;
			virtual void SetMember( ILuaObject *table, const char *key, ILuaObject *value ) = 0;
			virtual void SetIsServer( bool isServer ) = 0;
			virtual void PushLong( long num ) = 0;
			virtual int GetFlags( int index ) = 0;
			virtual bool FindOnObjectsMetaTable( int objIndex, int keyIndex ) = 0;
			virtual bool FindObjectOnTable( int tableIndex, int keyIndex ) = 0;
			virtual void SetMemberFast( ILuaObject *table, int keyIndex, int valueIndex ) = 0;
			virtual bool RunString( const char *filename, const char *path, const char *stringToRun, bool run, bool showErrors ) = 0;
			virtual bool IsEqual( ILuaObject *objA, ILuaObject *objB ) = 0;
			virtual void Error( const char *err ) = 0;
			virtual const char *GetStringOrError( int index ) = 0;
			virtual bool RunLuaModule( const char *name ) = 0;
			virtual bool FindAndRunScript( const char *filename, bool run, bool showErrors, const char * ) = 0;
			virtual void SetPathID( const char *pathID ) = 0;
			virtual const char *GetPathID( ) = 0;
			virtual void ErrorNoHalt( const char *fmt, ... ) = 0;
			virtual void Msg( const char *fmt, ... ) = 0;
			virtual void PushPath( const char *path ) = 0;
			virtual void PopPath( ) = 0;
			virtual const char *GetPath( ) = 0;
			virtual int GetColor( int index ) = 0;
			virtual void PushColor( int r, int g, int b, int a ) = 0;
			virtual int GetStack( int level, lua_Debug *dbg ) = 0;
			virtual int GetInfo( const char *what, lua_Debug *dbg ) = 0;
			virtual const char *GetLocal( lua_Debug *dbg, int n ) = 0;
			virtual const char *GetUpvalue( int funcIndex, int n ) = 0;
			virtual void RunStringEx( const char *filename, const char *path, const char *stringToRun, bool run, bool showErrors, bool ) = 0;
			virtual void DELETE_ME1( const char *, int ) = 0;
			virtual size_t GetDataString( int index, const char **str ) = 0;
			virtual void ErrorFromLua( const char *fmt, ... ) = 0;
			virtual void GetCurrentLocation( ) = 0;
			virtual void MsgColour( const Color &col, const char *fmt, ... ) = 0;
			virtual void PushState( lua_State *state ) = 0;
			virtual void PopState( ) = 0;
			virtual void GetCurrentFile( std::string &outStr ) = 0;
			virtual void CompileString( Bootil::Buffer &dumper, const std::string &stringToCompile ) = 0;
			virtual void ThreadLock( ) = 0;
			virtual void ThreadUnlock( ) = 0;
			virtual bool CallFunctionProtected( int, int, bool ) = 0;
			virtual void Require( const char *name ) = 0;
			virtual void GetActualTypeName( int type ) = 0;
			virtual void SetupInfiniteLoopProtection( ) = 0; // useless
			int LoadString(const char* code) {
				return 0; //luaL_loadstring(this->GetLuaState(), code);
			}
		};
		class ILuaObject_001 {
		public:
			virtual void	Set( ILuaObject* obj ) = 0;
			virtual void	SetFromStack( int i ) = 0;
			virtual void	UnReference() = 0;

			virtual int				GetType( void ) = 0;

			virtual const char*		GetString( void ) = 0;
			virtual float			GetFloat( void ) = 0;
			virtual int				GetInt( void ) = 0;
			virtual void*			GetUserData( void ) = 0;

			virtual void			SetMember( const char* name ) = 0;
			virtual void			SetMember( const char* name, ILuaObject* obj ) = 0; // ( This is also used to set nil by passing NULL )
			virtual void			SetMember( const char* name, float val ) = 0;
			virtual void			SetMember( const char* name, bool val ) = 0;
			virtual void			SetMember( const char* name, const char* val ) = 0;
			virtual void			SetMember( const char* name, lua_CFunction f ) = 0;

			virtual bool			GetMemberBool( const char* name, bool b = true ) = 0;
			virtual int				GetMemberInt( const char* name, int i = 0 ) = 0;
			virtual float			GetMemberFloat( const char* name, float f = 0.0f ) = 0;
			virtual const char*		GetMemberStr( const char* name, const char* = "" ) = 0;
			virtual void*			GetMemberUserData( const char* name, void* = 0 ) = 0;
			virtual void*			GetMemberUserData( float name, void* = 0 ) = 0;
			virtual ILuaObject* 	GetMember( const char* name ) = 0;
			virtual ILuaObject* 	GetMember( ILuaObject* ) = 0;

			virtual void			SetMetaTable( ILuaObject* obj ) = 0;
			virtual void			SetUserData( void* obj ) = 0;

			virtual void			Push( void ) = 0;

			virtual bool			isNil() = 0;
			virtual bool			isTable() = 0;
			virtual bool			isString() = 0;
			virtual bool			isNumber() = 0;
			virtual bool			isFunction() = 0;
			virtual bool			isUserData() = 0;

			virtual ILuaObject* 	GetMember( float fKey ) = 0;

			virtual void*			Remove_Me_1( const char* name, void* = 0 ) = 0;

			virtual void			SetMember( float fKey ) = 0;
			virtual void			SetMember( float fKey, ILuaObject* obj ) = 0;
			virtual void			SetMember( float fKey, float val ) = 0;
			virtual void			SetMember( float fKey, bool val ) = 0;
			virtual void			SetMember( float fKey, const char* val ) = 0;
			virtual void			SetMember( float fKey, lua_CFunction f ) = 0;

			virtual const char*		GetMemberStr( float name, const char* = "" ) = 0;

			virtual void			SetMember( ILuaObject* k, ILuaObject* v ) = 0;
			virtual bool			GetBool( void ) = 0;
		};

		class ILuaObject : public ILuaObject_001 {
		public:
			virtual bool			PushMemberFast( int iStackPos ) = 0;
			virtual void			SetMemberFast( int iKey, int iValue ) = 0;

			virtual void			SetFloat( float val ) = 0;
			virtual void			SetString( const char* val ) = 0;

			virtual void*	GetMembers( void ) = 0;

			// Set member 'pointer'. No GC, no metatables. 
			virtual void			SetMemberUserDataLite( const char* strKeyName, void* pData ) = 0;
			virtual void*			GetMemberUserDataLite( const char* strKeyName ) = 0;
		};
	}
}

#endif
