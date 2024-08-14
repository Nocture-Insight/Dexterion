#pragma once

#include "include.hpp"

#include "../util/config.hpp"
#include "../gui/menu.hpp"
#include "../gui/overlay.hpp"

namespace misc {

	inline namespace sharedData {
		inline int bhopInAir = (1 << 0);
	};

	void droppedItem(C_CSPlayerPawn C_CSPlayerPawn, CGameSceneNode CGameSceneNode, view_matrix_t viewMatrix);
	bool isGameWindowActive();
}