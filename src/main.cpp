#include <windows.h>
#include <cstdio>
#include <iostream>
#include "polyhook2/PE/IatHook.hpp"
#include "proxy.h"
#include "logger.h"
#include "il2cpp.h"
#include "polyhook2/PE/EatHook.hpp"
#include "polyhook2/Detour/x64Detour.hpp"
#include "gamesdk.h"
#include "gui.h"
#include "hooks.h"


// we got a reasonably ready environment now.
void EnvironmentReady() {
	using namespace il2cpp;
	using namespace Game;
	// At first i thought this was joining a thread, but actually this is much cooler.
	// this adds the thread into garbage collector's stop the world thing, scans registers and stack
	// for managed pointers, and pins them in place so they're not copied away or collected while we're working.
	// idk if il2cpp does any of that, or if i'm correct at all.
	// https://www.mono-project.com/docs/advanced/garbage-collector/sgen/
	il2cpp_thread_attach(il2cpp_domain_get());
	if (!Game::Initialize()) {
		LOG("Some functionality failed to load");
		return;
	}
	InitializeHooks();

	auto ImguiManager = UnityEngine::GameObject::Find("ImguiManager"_il2cpp);
	LOG("ImguiManager %p", ImguiManager);
	// Dissonance::Demo::Logo is an unused class that we can take over for OnGUI callbacks.
	UnityEngine::GameObject::AddComponent(ImguiManager, il2cpp_type_get_object(il2cpp_class_get_type(Dissonance::Demo::Logo::klass)));

	auto CheatObject = UnityEngine::GameObject::Find("CheatObject"_il2cpp);
	LOG("CheatObject %p", CheatObject);
	auto nonexistent = UnityEngine::GameObject::Find("nonexistent"_il2cpp);
	LOG("nonexistent %p", nonexistent);


	CheatGUI::Init();
}

NOINLINE int __stdcall il2cpp_init_hook(const char *domain_name) {
	LOG("il2cpp_init_hook %s", domain_name);
	return il2cpp::il2cpp_init(domain_name);
}

uint64_t il2cpp_runtime_invoke_orig;
NOINLINE il2cpp::Il2CppObject* __stdcall il2cpp_runtime_invoke_hook(const il2cpp::MethodInfo * method, void *obj, void **params, il2cpp::Il2CppException **exc) {
	static int scene_changed = 0;
	if (scene_changed < 2) {
		auto name = il2cpp::il2cpp_method_get_name(method);
		if (strcmp(name, "Internal_ActiveSceneChanged") == 0) {
			LOG("il2cpp_runtime_invoke_hook %s", name);
			// bepinex i think does first (0-th) one? second seems like a more ready environment.
			// TODO: probably should create a monobehaviour object instead, and do the calls from its callbacks, or hook some start/awake func
			if (scene_changed == 1) {
				LOG("calling EnvironmentReady");
				EnvironmentReady();
			}
			scene_changed++;
		}
	}
	return ((il2cpp::il2cpp_runtime_invoke_t)il2cpp_runtime_invoke_orig)(method, obj, params, exc);
}


typedef FARPROC(__stdcall* GetProcAddress_t)(HMODULE hModule, LPCSTR lpProcName);
uint64_t GetProcAddress_orig;

PLH::x64Detour* il2cpp_runtime_invokeHooker;

NOINLINE FARPROC __stdcall GetProcAddress_hook(HMODULE hModule, LPCSTR lpProcName) {
//	LOG("GetProcAddress %s", lpProcName);
	FARPROC h = ((GetProcAddress_t)GetProcAddress_orig)(hModule, lpProcName);
	// LOG("GetProcAddress(%p, %s) -> %p", hModule, lpProcName, h);
	LoadIl2CppAddress(h, lpProcName);
#define HOOK_PROC(name, override) \
    if (lstrcmpA(lpProcName, #name) == 0) { \
        LOG("GetProcAddress hooking "#name); \
        if (override) \
            h = (FARPROC)override; \
    }
//	HOOK_PROC(il2cpp_init, nullptr);
//	static bool skipped_bepinex = false;
//	if (lstrcmpA(lpProcName, "il2cpp_runtime_invoke") == 0) {
//		if (skipped_bepinex) {
//			LOG("GetProcAddress hooking il2cpp_runtime_invoke");
//			h = (FARPROC)il2cpp_runtime_invoke_hook;
//		} else {
//			LOG("GetProcAddress skipping bepinex il2cpp_runtime_invoke");
//		}
//		skipped_bepinex = true;
//    }
//	HOOK_PROC(il2cpp_runtime_invoke, il2cpp_runtime_invoke_hook);
	if (lstrcmpA(lpProcName, "il2cpp_runtime_invoke") == 0 && !il2cpp_runtime_invoke_orig) {
        LOG("GetProcAddress hooking il2cpp_runtime_invoke");
//		h = (FARPROC)il2cpp_runtime_invoke_hook;
		// detour instead of returning a different pointer is because bepinex's detour impl is retarded and just mega fucks our shit somehow
		il2cpp_runtime_invokeHooker = new PLH::x64Detour((uint64_t)h, (uint64_t)il2cpp_runtime_invoke_hook, &il2cpp_runtime_invoke_orig);
		if (!il2cpp_runtime_invokeHooker->hook())
			LOG("il2cpp_runtime_invoke hook failed");
		else
			LOG("il2cpp_runtime_invoke_orig ok: %p", il2cpp_runtime_invoke_orig);
    }
#undef HOOK_PROC
	return h;
}
// iat doesn't work because doorstop's iat impl is retarded
//PLH::IatHook GetProcAddressHooker("kernel32.dll", "GetProcAddress", (char*)&GetProcAddress_hook, &GetProcAddress_orig, L"UnityPlayer.dll");
// eat i swear was just kinda working yesterday, but now i'm not getting calls that are intercepted by doorstop?
//PLH::EatHook GetProcAddressHooker("GetProcAddress", L"kernel32.dll", (char*)&GetProcAddress_hook, &GetProcAddress_orig);
PLH::x64Detour GetProcAddressHooker((uint64_t)GetProcAddress, (uint64_t)GetProcAddress_hook, &GetProcAddress_orig);

void Startup() {
	init_logger("ccc.log");
	time_t timer;
	char timebuffer[26];
	struct tm* tm_info;

	timer = time(NULL);
	tm_info = localtime(&timer);

	strftime(timebuffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);

	LOG("Started up at %s", timebuffer);
	load_proxy("winhttp");


	if (!GetProcAddressHooker.hook())
		LOG("GetProcAddress hook failed");
	else
		LOG("oGetProcAddress ok: %p", GetProcAddress_orig);
}

void Shutdown() {
	free_logger();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD nReason, LPVOID lpReserved) {
	switch (nReason) {
		case DLL_PROCESS_ATTACH:
			MessageBox(
					NULL,
					"Right now would be a great time\nTo attach a debugger if you're debugging\n\nOr just press ok",
					"CheatersCheetahCheatC++",
					MB_OK
			);
			Startup();
			break;
		case DLL_PROCESS_DETACH:
			Shutdown();
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	}
	return TRUE;
}