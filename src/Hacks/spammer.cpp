#include "spammer.h"
#include "../gamesdk.h"
#include "../settings.h"

static float lastMessageTime = 0;
static il2cpp::gchandle textChatComponent(true);

void Spammer::Update() {
	if (!Settings::Spammer::enabled) {
		return;
	}
	float currentTime = Game::UnityEngine::Time::get_time();
	if (lastMessageTime > currentTime-Settings::Spammer::delay) {
		return;
	}

	if (!Game::UnityEngine::Object::op_Implicit(textChatComponent)) {

		il2cpp::Il2CppObject* obj = Game::UnityEngine::GameObject::FindObjectOfType(
				il2cpp::ClassGetTypeObject(Game::GlobalUI::TextChatComponent::klass), false);
		textChatComponent = obj;
	}
	if (!Game::UnityEngine::Object::op_Implicit(textChatComponent)) {
		return;
	}
	lastMessageTime = currentTime;
	il2cpp::Il2CppObject* obj = textChatComponent;
	Game::GlobalUI::TextChatComponent::ToggleChatMode(obj, true);
	// TODO: support unicode.
	const std::string& message = Settings::Spammer::messages[std::rand() % Settings::Spammer::messages.size()];
	Game::GlobalUI::TextChatComponent::OnMessageSubmit(obj, il2cpp::il2cpp_string_new_len(message.c_str(), message.size()));
}