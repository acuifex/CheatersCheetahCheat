#include "voicespammer.h"
#include "../settings.h"
#include "../gui.h"
#include <format>

static bool wasEnabled = false;

enum CommActivationMode
{
	None,
	VoiceActivation,
	PushToTalk,
	Open
};

Game::VoiceChat::VoiceChatManager_o* GetInstance() {
	return (Game::VoiceChat::VoiceChatManager_o *)(*(void**)Game::VoiceChat::VoiceChatManager::klass->static_fields);
}

bool VoiceSpammer::UpdateBroadcastMode(Game::VoiceChat::VoiceChatManager_o* this_) {
	// since there are multiple VoiceChatManager instances (it's a singleton??) we kinda have to do this.
	bool isGlobalInstance = this_ == GetInstance();
	if (!isGlobalInstance)
		return true;
	if (wasEnabled && !Settings::VoiceSpammer::enabled) {
		if (this_->fields.groupVoiceBroadcastTrigger != nullptr)
			Game::Dissonance::VoiceBroadcastTrigger::set_Mode(
					this_->fields.groupVoiceBroadcastTrigger, CommActivationMode::None);
		if (this_->fields.globalVoiceBroadcastTrigger != nullptr)
			Game::Dissonance::VoiceBroadcastTrigger::set_Mode(
					this_->fields.globalVoiceBroadcastTrigger, CommActivationMode::None);
	}
	wasEnabled = Settings::VoiceSpammer::enabled;
	if (!Settings::VoiceSpammer::enabled)
		return true;

	if (this_->fields.groupVoiceBroadcastTrigger != nullptr)
		Game::Dissonance::VoiceBroadcastTrigger::set_Mode(
				this_->fields.groupVoiceBroadcastTrigger, CommActivationMode::Open);
	if (this_->fields.globalVoiceBroadcastTrigger != nullptr)
		Game::Dissonance::VoiceBroadcastTrigger::set_Mode(
				this_->fields.globalVoiceBroadcastTrigger, CommActivationMode::Open);

	return false;
}

void VoiceSpammer::OnCheatInfoGUI() {
	// first value is an _instance pointer. evil hack ik.
	auto manager = GetInstance();
	if (manager == nullptr){
		return;
	}
	const char* groupstr = "null";
	const char* global = "null";
	if (manager->fields.groupVoiceBroadcastTrigger != nullptr) {
		if (Game::Dissonance::VoiceBroadcastTrigger::get_IsTransmitting(manager->fields.groupVoiceBroadcastTrigger)) {
			groupstr = "true";
		} else {
			groupstr = "false";
		}
	}
	if (manager->fields.globalVoiceBroadcastTrigger != nullptr) {
		if (Game::Dissonance::VoiceBroadcastTrigger::get_IsTransmitting(manager->fields.globalVoiceBroadcastTrigger)) {
			global = "true";
		} else {
			global = "false";
		}
	}
	// https://youtrack.jetbrains.com/issue/CPP-38669/stdformat-In-template-auto-in-return-type-deduced-as-typeidentitydouble-here-but-deduced-as
	// fuck you clion
	std::string str = std::format("Broadcast Group:{} Global:{}", groupstr, global);
	Game::UnityEngine::GUILayout::Label(
			il2cpp::il2cpp_string_new_len(str.c_str(), str.size()),
			CheatGUI::GetEmptyGUILayoutOptions());

}