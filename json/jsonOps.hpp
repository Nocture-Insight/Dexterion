#pragma once

#include <fstream>

#include "json.hpp"
#include "../util/utilFunctions.hpp"

namespace json {
	std::wstring clientDLLFile = L"\\client.dll.json";
	std::wstring offsetFile = L"\\offsets.json";
	std::wstring buttonsFile = L"\\buttons.json";

	nlohmann::json readFromJsonFile(std::wstring path, std::wstring fileName);
}
