# CheatersCheetahCheat
Or CCC for short, pronounced KKK

## Setup and compile
1. Install dotnet 6
2. Download and unpack win64 IL2CPP bepinex 6.0 into game folder. Either [prerelease](https://github.com/BepInEx/BepInEx/releases/tag/v6.0.0-pre.2)
([file](https://github.com/BepInEx/BepInEx/releases/download/v6.0.0-pre.2/BepInEx-Unity.IL2CPP-win-x64-6.0.0-pre.2.zip))
or [nightly](https://builds.bepinex.dev/projects/bepinex_be) ([file](https://builds.bepinex.dev/projects/bepinex_be/733/BepInEx-Unity.IL2CPP-win-x64-6.0.0-be.733%2B995f049.zip)) works
3. If you are on linux proton, you need to add winhttp to wine overrides. [wiki](https://docs.bepinex.dev/master/articles/advanced/steam_interop.html#adding-the-dll-override)
4. Launch the game to generate interop files
5. Reference the interop files.  
On rider it's done with Explorer -> Solution view, CheatersCheetahCheat -> Right click Dependencies -> Reference... -> Add from -> add files from `Cheaters Cheetah/BepInEx/interop`  
Or do it manually, open `CheatersCheetahCheat.csproj` and change all the lines from `..\..\..\.steam\steam\ ...` to whatever it is on your system.  
Also do that with `ScriptEngine.csproj`, or skip building it as it's not required to run.
7. Sometimes need to install nuget dependencies? **First do dotnet build, and check if it failed**
8. `dotnet build` or click the build icon in rider
9. copy or symlink `CheatersCheetahCheat/bin/Debug/net6.0/CheatersCheetahCheat.dll` to `Cheaters Cheetah/BepInEx/plugins/CheatersCheetahCheat.dll`


# Notes
ScriptEngine was my attempt to port [this](https://github.com/BepInEx/BepInEx.Debug/tree/master/src/ScriptEngine) for bepinex 6.0. It kinda works as in it reloads recompiled code, but doesn't completely rerun some code.

[CinematicUnityExplorer](https://github.com/originalnicodr/CinematicUnityExplorer/) ([file](https://github.com/originalnicodr/CinematicUnityExplorer/releases/latest/download/CinematicUnityExplorer.BepInEx.Unity.IL2CPP.CoreCLR.zip)) works while the original doesn't. Needs a few patches to fix class and singleton search. (`CinematicUnityExplorer.patch`)

[This gist](https://gist.github.com/BadMagic100/47096cbcf64ec0509cf75d48cfbdaea5) was very useful

... maybe will add some more stuff

credit to some lads on unknowncheats for some of the code. sorry, didn't keep track of what i stole :(
