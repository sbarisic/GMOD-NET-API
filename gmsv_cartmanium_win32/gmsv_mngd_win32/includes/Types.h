#ifndef GARRYSMOD_LUA_TYPES_H
#define GARRYSMOD_LUA_TYPES_H

#ifdef ENTITY
#undef ENTITY
#endif 

#ifdef VECTOR
#undef VECTOR
#endif 

namespace GarrysMod  {
	namespace Lua {
		public enum class Type : int {
			INVALID = -1,
			NIL, 
			BOOL,
			LIGHTUSERDATA,
			NUMBER, 
			STRING, 
			TABLE,
			FUNCTION,
			USERDATA,
			THREAD,

			// UserData
			ENTITY, 
			VECTOR, 
			ANGLE,
			PHYSOBJ,
			SAVE,
			RESTORE,
			DAMAGEINFO,
			EFFECTDATA,
			MOVEDATA,
			RECIPIENTFILTER,
			USERCMD,
			SCRIPTEDVEHICLE,

			// Client Only
			MATERIAL,
			PANEL,
			PARTICLE,
			PARTICLEEMITTER,
			TEXTURE,
			USERMSG,

			CONVAR,
			IMESH,
			MATRIX,
			SOUND,
			PIXELVISHANDLE,
			DLIGHT,
			VIDEO,
			FILE,

			COUNT
		};

		namespace TypeNames {
			static const char* Name[] =  {
				"nil",
				"bool",
				"lightuserdata",
				"number",
				"string",
				"table",
				"function",
				"userdata",
				"thread",
				"entity",
				"vector",
				"angle",
				"physobj",
				"save",
				"restore",
				"damageinfo",
				"effectdata",
				"movedata",
				"recipientfilter",
				"usercmd",
				"vehicle",
				"material",
				"panel",
				"particle",
				"particleemitter",
				"texture",
				"usermsg",
				"convar",
				"mesh",
				"matrix",
				"sound",
				"pixelvishandle",
				"dlight",
				"video",
				"file",
				0
			};
		}
	}
}

#endif