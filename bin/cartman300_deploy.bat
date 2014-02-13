@ECHO off
IF exist "E:\Program Files\DarkSteam\client\steamapps\common\garrysmod" (
	COPY gmsv_cartmanium_win32.dll "E:\Program Files\DarkSteam\client\steamapps\common\garrysmod\garrysmod\lua\bin" /Y
	COPY gmsv_cartmanium_win32.dll "E:\Program Files\DarkSteam\client\steamapps\common\garrysmod\garrysmod\lua\bin\gmcl_cartmanium_win32.dll" /Y
	COPY ManagedWrapper.dll "E:\Program Files\DarkSteam\client\steamapps\common\garrysmod" /Y
	REM COPY ..\lua\lua51.dll "E:\Program Files\DarkSteam\client\steamapps\common\garrysmod" /Y
	COPY gmcl_steamapi_win32.dll "E:\Program Files\DarkSteam\client\steamapps\common\garrysmod\garrysmod\lua\bin" /Y
	COPY gmcl_steamapi_win32.dll "E:\Program Files\DarkSteam\client\steamapps\common\garrysmod\garrysmod\lua\bin\gmsv_steamapi_win32.dll" /Y
	ECHO Copied files to GMod directories...
) else (
	IF exist "D:\Steam\SteamApps\common\garrysmod" (
		COPY gmsv_cartmanium_win32.dll "D:\Steam\SteamApps\common\garrysmod\garrysmod\lua\bin" /Y
		COPY gmsv_cartmanium_win32.dll "D:\Steam\SteamApps\common\garrysmod\garrysmod\lua\bin\gmcl_cartmanium_win32.dll" /Y
		COPY ManagedWrapper.dll "D:\Steam\SteamApps\common\garrysmod" /Y
		REM COPY ..\lua\lua51.dll "D:\Steam\SteamApps\common\garrysmod" /Y
		COPY gmcl_steamapi_win32.dll "D:\Steam\SteamApps\common\garrysmod\garrysmod\lua\bin" /Y
		COPY gmcl_steamapi_win32.dll "D:\Steam\SteamApps\common\garrysmod\garrysmod\lua\bin\gmsv_steamapi_win32.dll" /Y
		ECHO Copied files to GMod PC directories...
	) else (
		ECHO Not found any GMod directories, skipping...
	)
)
