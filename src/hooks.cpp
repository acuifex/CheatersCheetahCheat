#include "hooks.h"
#include "gamesdk.h"
#include "gui.h"
#include "Hacks/spammer.h"
#include "settings.h"
#include "polyhook2/Detour/x64Detour.hpp"
#include "Hacks/voicespammer.h"

#define DEFINE_HOOK(namespaze, ret, func, params) namespaze::func##_t func##_orig; \
ret __fastcall func##_hook params

DEFINE_HOOK(Game::SkateMenu::ImguiManager, void, Update, (il2cpp::Il2CppObject *_this)) {
	Update_orig(_this);

	Spammer::Update();
}

DEFINE_HOOK(Game::Dissonance::Demo::Logo, void, OnGUI, (il2cpp::Il2CppObject *_this)) {
//	OnGUI_orig(_this);
	CheatGUI::OnGUI();
}

DEFINE_HOOK(Game::DataStructs::CheatModeExtensions, bool, IsFeatureEnabled, (uint8_t current, uint8_t cheatMode)) {
	if (Settings::BypassLegit::enabled)
		return true;
	return IsFeatureEnabled_orig(current, cheatMode);
}

DEFINE_HOOK(Game::VoiceChat::VoiceChatManager, void, UpdateBroadcastMode, (Game::VoiceChat::VoiceChatManager_o* this_)) {
	if (VoiceSpammer::UpdateBroadcastMode(this_))
		UpdateBroadcastMode_orig(this_);
}

static bool aimlocked = false;
DEFINE_HOOK(Game::Game_::Player::Aimbot::Ragebot, void*, ApplyRagebot,
(void* return_storage_, void* moveData, bool willGetConsumed, bool willGetConsumedIfPrimaryDown, bool* overwritePrimaryDown)){
	if (Settings::AutoFire::enabled) {
		void* ret = ApplyRagebot_orig(return_storage_, moveData, willGetConsumedIfPrimaryDown, willGetConsumedIfPrimaryDown, overwritePrimaryDown);
		*overwritePrimaryDown = aimlocked;
		return ret;
	}
	return ApplyRagebot_orig(return_storage_, moveData, willGetConsumed, willGetConsumedIfPrimaryDown, overwritePrimaryDown);
}

DEFINE_HOOK(Game::Game_::Player::Aimbot::Ragebot, bool, ShouldActivateAimLock,
(void* aimPoints, int32_t* aimPointIndex, il2cpp::Il2CppObject* config, bool manual)) {
	if (Settings::AutoFire::enabled) {
		manual = false;
	}
	aimlocked = ShouldActivateAimLock_orig(aimPoints, aimPointIndex, config, manual);
	return aimlocked;
}

template<typename T>
bool HookManagedFunction(il2cpp::MethodInfo* methodInfo, T hook, T* original) {
	if (methodInfo == nullptr)
		return false;  // dumbass
	if (original != nullptr)
		*original = reinterpret_cast<T>(methodInfo->methodPointer);
	methodInfo->methodPointer = (il2cpp::Il2CppMethodPointer)hook;
	methodInfo->virtualMethodPointer = (il2cpp::Il2CppMethodPointer)hook;
	return true;
}

std::vector<std::pair<const char*, std::unique_ptr<PLH::x64Detour>>> hooks;

bool InitializeHooks() {
	using namespace Game;
	using namespace il2cpp;
	bool ok = true;
	ok &= HookManagedFunction(Dissonance::Demo::Logo::OnGUI_info, (Dissonance::Demo::Logo::OnGUI_t)OnGUI_hook, &OnGUI_orig);
	ok &= HookManagedFunction(SkateMenu::ImguiManager::Update_info, (SkateMenu::ImguiManager::Update_t) Update_hook,
	                    &Update_orig);
	//	HookManagedFunction(Game::DataStructs::CheatModeExtensions::IsFeatureEnabled_info, (Game::DataStructs::CheatModeExtensions::IsFeatureEnabled_t)IsFeatureEnabled_hook, &IsFeatureEnabled_orig);
#define ADD_HOOK(what, to) \
	hooks.emplace_back(#what, std::make_unique<PLH::x64Detour>( \
						   (uint64_t) what, \
						   (uint64_t) to##_hook, \
						   (uint64_t*) &to##_orig))
	ADD_HOOK(DataStructs::CheatModeExtensions::IsFeatureEnabled, IsFeatureEnabled);
	ADD_HOOK(Game::VoiceChat::VoiceChatManager::UpdateBroadcastMode, UpdateBroadcastMode);
	ADD_HOOK(Game::Game_::Player::Aimbot::Ragebot::ApplyRagebot, ApplyRagebot);
	ADD_HOOK(Game::Game_::Player::Aimbot::Ragebot::ShouldActivateAimLock, ShouldActivateAimLock);
	// hooks.emplace_back("IsFeatureEnabled", std::make_unique<PLH::x64Detour>(
	// 	                   (uint64_t) Game::DataStructs::CheatModeExtensions::IsFeatureEnabled,
	// 	                   (uint64_t) IsFeatureEnabled_hook,
	// 	                   (uint64_t*) &IsFeatureEnabled_orig));
	// hooks.emplace_back("UpdateBroadcastMode", std::make_unique<PLH::x64Detour>(
	// 	                   (uint64_t) Game::VoiceChat::VoiceChatManager::UpdateBroadcastMode,
	// 	                   (uint64_t) UpdateBroadcastMode_hook,
	// 	                   (uint64_t*) &UpdateBroadcastMode_orig));
	// static PLH::x64Detour IsFeatureEnabledHooker((uint64_t) Game::DataStructs::CheatModeExtensions::IsFeatureEnabled,
	//                                              (uint64_t) IsFeatureEnabled_hook,
	//                                              (uint64_t*)&IsFeatureEnabled_orig);
	// static PLH::x64Detour UpdateBroadcastModeHooker((uint64_t)Game::VoiceChat::VoiceChatManager::UpdateBroadcastMode, (uint64_t)UpdateBroadcastMode_hook,
	// 										   (uint64_t*)&UpdateBroadcastMode_orig);
	for (auto& hook: hooks) {
		if (hook.second->hook()) {
			LOG("%s ok", hook.first);
		} else {
			LOG("%s hook failed", hook.first);
			ok = false;
		}
	}
	// if (!IsFeatureEnabledHooker.hook())
	// 	LOG("IsFeatureEnabled hook failed");
	// else
	// 	LOG("IsFeatureEnabled ok: %p", IsFeatureEnabled_orig);
	// if (!UpdateBroadcastModeHooker.hook())
	// 	LOG("UpdateBroadcastModeHooker hook failed");
	// else
	// 	LOG("UpdateBroadcastModeHooker ok: %p", IsFeatureEnabled_orig);
	return ok;
}