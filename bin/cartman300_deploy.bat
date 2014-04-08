@ECHO off
IF exist "E:\Program Files\DarkSteam\client\steamapps\common\garrysmod" (
	E:
	CD E:\Dropbox\Projects\ManagedWrapper\bin
	COPY ManagedWrapper.dll "E:\Program Files\DarkSteam\client\steamapps\common\garrysmod" /Y
	ECHO Copied files to GMod directories...
) else (
	IF exist "D:\Steam\SteamApps\common\garrysmod" (
		COPY ManagedWrapper.dll "D:\Steam\SteamApps\common\garrysmod" /Y
		ECHO Copied files to GMod PC directories...
	) else (
		ECHO Not found any GMod directories, skipping...
	)
)