#include "gui.h"
#include "gamesdk.h"
#include "settings.h"
#include <format>

#include "Hacks/voicespammer.h"
#include "Hacks/chatlagexploit.h"
#include "Hacks/compressedpacketinflateexploit.h"

// todo: nuke all of this in favour of imgui
using namespace Game::UnityEngine;

static il2cpp::gchandle DoWindowDelegate;
static il2cpp::gchandle PingSpoofString;
static Rect_o rect {20, 420, 250, 400};
static Rect_o dragWindowRect {0, 0, 1000, 20};

void DoWindow() {
	GUI::DragWindow(&dragWindowRect);
	auto options = CheatGUI::GetEmptyGUILayoutOptions();
	Settings::ChatSpoofer::anonymousSenderEnabled = GUILayout::Toggle(Settings::ChatSpoofer::anonymousSenderEnabled, "Anonamize Chat Sender"_il2cpp, options);

	Settings::Spammer::enabled = GUILayout::Toggle(Settings::Spammer::enabled, "Chat Spammer"_il2cpp, options);
	GUILayout::BeginHorizontal(options);
	Settings::Spammer::delay = GUILayout::HorizontalSlider(Settings::Spammer::delay, 0.1f, 5.f, options);
	std::string delaystr = std::format("{} ms", int(Settings::Spammer::delay*1000));
	GUILayout::Label(il2cpp::il2cpp_string_new_len(delaystr.c_str(), delaystr.size()), options);
	GUILayout::EndHorizontal();

	Settings::VoiceSpammer::enabled = GUILayout::Toggle(Settings::VoiceSpammer::enabled, "Open Microphone"_il2cpp, options);
	Settings::BypassLegit::enabled = GUILayout::Toggle(Settings::BypassLegit::enabled, "Bypass Legit"_il2cpp, options);

	Settings::AutoFire::enabled = GUILayout::Toggle(Settings::AutoFire::enabled, "Aimbot AutoFire"_il2cpp, options);
	GUILayout::BeginHorizontal(options);
	Settings::AutoFire::mindmg = GUILayout::HorizontalSlider(Settings::AutoFire::mindmg, 1.f, 100.f, options);
	std::string mindmgstr = std::format("{} hp", int(Settings::AutoFire::mindmg));
	GUILayout::Label(il2cpp::il2cpp_string_new_len(mindmgstr.c_str(), mindmgstr.size()), options);
	GUILayout::EndHorizontal();

	Settings::PingSpoofer::enabled = GUILayout::Toggle(Settings::PingSpoofer::enabled, "Spoof Ping"_il2cpp, options);
	PingSpoofString.Set((il2cpp::Il2CppObject*)GUILayout::TextField((il2cpp::Il2CppString*)PingSpoofString.Get(), options));
	uint32_t PingSpoofParsed;
	// easier to call into managed than to parse whatever weird format it's using.
	if (Game::System::UInt32::TryParse((il2cpp::Il2CppString*)PingSpoofString.Get(), &PingSpoofParsed)) {
		Settings::PingSpoofer::value = (double)PingSpoofParsed/1000.0;
	}

	if (GUILayout::Button("Chat Lag/Crash Exploit"_il2cpp, options)) {
		ChatLagExploit::Invoke();
	}
	GUILayout::Label("Inflate needs a lot runs to crash due to mirror packet size limitations. Each invoke leaks ~512 MiB of memory on host."_il2cpp, options);
	if (GUILayout::Button("Packet Inflate Exploit"_il2cpp, options)) {
		CompressedPacketInflateExploit::Invoke();
	}

	GUILayout::Label("Hi LWSS!"_il2cpp, options);
}

void CheatGUI::OnGUI() {
	Rect_o pos {10, 25, 200, 200};
	GUI::Label(&pos, "CheatersCheetahCheatC++"_il2cpp);

	if (Game::SkateMenu::ImguiManager::get_IsBaseWindowOpen()) {
		// the return buffer MUST be different from the argument one. if it's not, you'll get corrupted values
		Rect_o return_buffer;
		rect = *GUILayout::Window(&return_buffer, 1, &rect, DoWindowDelegate, "CheatersCheetahCheatC++ menu"_il2cpp,
											 GetEmptyGUILayoutOptions());
	}
	Rect_o infopos {10, 40, 500, 500};
	GUILayout::BeginArea(&infopos);
	VoiceSpammer::OnCheatInfoGUI();
	GUILayout::EndArea();
}

void CheatGUI::Init() {
	auto typeObject = il2cpp::il2cpp_type_get_object(il2cpp::il2cpp_class_get_type(GUI::WindowFunction::klass));

	DoWindowDelegate = Game::System::Runtime::InteropServices::Marshal::GetDelegateForFunctionPointer(
			reinterpret_cast<uintptr_t>(DoWindow), typeObject);

	std::string PingSpoofstdstring = std::to_string(int(Settings::PingSpoofer::value*1000));
	PingSpoofString.Set((il2cpp::Il2CppObject*)il2cpp::il2cpp_string_new_len(PingSpoofstdstring.c_str(), PingSpoofstdstring.size()));
}