GMOD-NET-API
============

Garry's Mod Managed Application Programming Interface

##### Notice
* This repository is not maintained anymore, it is bugged and i might rewrite it some time later. Consider using this instead
https://github.com/cartman300/gmsv_gsharp_win32

##### What is it?
* It's a C++\CLI Wrapper over Garry's unmanaged GMod Binary Module headers

##### What can it do?
* It allows you to write binary modules in managed languages

##### How to install it?
* Put the binary in same directory as hl2.exe (common/garrysmod)

##### How do i create managed binary modules?
* Get Visual Studio 2012 and NuGet
* Create a C# .dll solution named like your module
* Install Unmanaged Exports from NuGet - this allows you to create static entry points for your module to be loadable by GMod
* Add reference to ManagedWrapper.dll and disable copy to local output, you don't need it in output - it gets automatically loaded from hl2.exe dir
* Write your code!
* Compile, put into garrysmod/lua/bin and require() it ingame!
* Note: Make sure the exported functions (Unmanaged Exports) have to be in a public class, else it won't work!
* Note 2: Also make sure you compile your project as x86, else Unmanaged Exports won't do it's magic!

##### What if i don't know how to do it/have bug/%insert_shit_here%?
* In case of a bug make an issue here on github
* In case of anything else add one on Steam

#### Is it possible to embed the wrapper into the module?
* It is, look in the gmsv_cartmanium_win32 project

[Steam profile](http://steamcommunity.com/id/cartman300/)