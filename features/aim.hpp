#pragma once

#include "include.hpp"

#include "../util/config.hpp"
#include "../gui/overlay.hpp"


namespace aim {
	void aimBot(LocalPlayer localPlayer, Vector3 baseViewAngles, uintptr_t enemyPlayer, uintptr_t boneArray, MemoryManagement::moduleData client);
	void moveMouseToPlayer(Vector3 pos);
	void recoilControl(LocalPlayer localPlayer, DWORD_PTR baseViewAnglesAddy);
	void triggerBot(LocalPlayer localPlayer, DWORD_PTR base);

	uintptr_t lockedPlayer = 0;
}
