#pragma once

#include "include.hpp"

#include "../util/config.hpp"
#include "../gui/overlay.hpp"

namespace bomb {
	bool isPlanted;
	std::time_t plantTime;

	void timer(C_C4 C_C4);
}