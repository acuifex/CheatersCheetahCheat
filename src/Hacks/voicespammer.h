#pragma once

#include "../gamesdk.h"


namespace VoiceSpammer
{
	//Hooks
	bool UpdateBroadcastMode(Game::VoiceChat::VoiceChatManager_o* this_); // false == skip original
	void OnCheatInfoGUI();
}