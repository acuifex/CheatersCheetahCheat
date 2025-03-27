# CheatersCheetahCheat
Or CCC for short, pronounced KKK. Now in C++!

## Building

### Linux
1. Install mingw tools. You'll need cmake, g++, and probably headers and some libs.  
  On arch i believe they are `aur/mingw-w64-cmake` and `mingw-w64` package group
2. `./build-static` or `./build` but then you'll need to copy these libraries to game root:
  `libgcc_s_seh-1.dll libssp-0.dll libstdc++-6.dll libwinpthread-1.dll`
3. `cp ./build/winhttp.dll ~/.steam/steam/steamapps/common/Cheaters Cheetah/` (or set `-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=...`)

It also works alongside bepinex/doorstop if you rename it to `winhttp_alt.dll` (or set `-DCCC_PROXY_LIB_NAME="winhttp_alt"`)

### Windows
Dunno man i think you just download cmake and a build system like `make`, `nmake`, or `ninja` and then you do `cmake .` and `cmake --build .`

## Debugging

`./gdb` or `PROTON_WAIT_ATTACH=1` launch option and `./gdbwait` if you need a very early attach (sometimes doesn't work on first time)

You may need to skip sigsegv for a bit after launching if you're using bepinex.
`handle SIGSEGV nostop noprint pass` `handle SIGSEGV stop pass`

## Why the C++ rewrite?
There is a [bug in HarmonyX](https://github.com/BepInEx/HarmonyX/issues/125)
that is borderline impossible to debug behind 50 layers of abstractions plus shitty gdb wine support situation.

It's all a wrapper around il2cpp api calls and other native stuff anyway with its own CoreCLR runtime separate from unity.

And there are like 33 players peak in the game so like who even gives a shit this is all a "haha cheat for a cheat game" shitpost and an exercise in wine/unity hacking

# Notes
If you're using clion, switch to [ReShaper C++](https://youtrack.jetbrains.com/issue/CPP-38669/stdformat-In-template-auto-in-return-type-deduced-as-typeidentitydouble-here-but-deduced-as)  
and create MinGW toolchain with Settings -> Build, Execution, Deployment -> Toolchains -> add  
and Cmake -> profile -> toolchain -> select MinGW option

Original C# code can be found in `csharp` branch

[This gist](https://gist.github.com/BadMagic100/47096cbcf64ec0509cf75d48cfbdaea5) was very useful

[Il2CppDumper](https://github.com/Perfare/Il2CppDumper) Honestly should be used instead of manual work, 
but the generated files are just so massive, and it would require a lot of code generation code in python or something, so i didn't bother.

Credits to:
* UnityDoorstop, bepinex for some api and proxy reference and etc
* Probably some lads on unknowncheats for something
* [ByNameModding](https://github.com/ByNameModding/BNM-Android) is an interesting reference
* Il2CppInspectorPro for headers (not a submodule because holy shit 1.4 GiB of unit tests)