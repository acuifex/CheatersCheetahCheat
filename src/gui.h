#pragma once
#include "il2cpp.h"
#include "gamesdk.h"


namespace CheatGUI {

	// idk if it's cheaper to have a handle or create a new one each time.
	inline il2cpp::Il2CppArray* GetEmptyGUILayoutOptions() {
		auto EmptyGUILayoutOptionArray = il2cpp::il2cpp_array_new(Game::UnityEngine::GUILayoutOption::klass, 0);
		return EmptyGUILayoutOptionArray;
	}
	void OnGUI();
	void Init();
}
