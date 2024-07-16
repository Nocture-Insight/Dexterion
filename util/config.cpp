#include "config.hpp"

inline nlohmann::json aimConfig::to_json() {
	nlohmann::json json;
	json["rcs"] = rcs;
	json["fov"] = fov;
	json["bone"] = bone;
	json["sens"] = sens;
	json["state"] = state;
	json["bones"] = bones;
	json["hotAim"] = hotAim;
	json["hotKey"] = hotKey;
	json["trigger"] = trigger;
	json["boneMap"] = boneMap;
	json["aimMode"] = aimMode;
	json["isHotAim"] = isHotAim;
	json["aimModes"] = aimModes;
	json["smoothing"] = smoothing;
	json["hotKeyMap"] = hotKeyMap;
	json["fovCircle"] = fovCircle;
	json["boneSelect"] = boneSelect;
	json["hotTrigger"] = hotTrigger;
	json["playerLock"] = playerLock;
	json["aimModeMap"] = aimModeMap;
	json["checkSpotter"] = checkSpotted;
	json["hotSelectAim"] = hotSelectAim;
	json["isHotTrigger"] = isHotTrigger;
	json["hotSelectTrigger"] = hotSelectTrigger;
	return json;
}

inline bool aimConfig::from_json(nlohmann::json json) {
	try {
		rcs = json["rcs"];
		fov = json["fov"];
		bone = json["bone"];
		sens = json["sens"];
		state = json["state"];
		bones = json["bones"];
		hotAim = json["hotAim"];
		hotKey = json["hotKey"];
		trigger = json["trigger"];
		boneMap = json["boneMap"];
		aimMode = json["aimMode"];
		isHotAim = json["isHotAim"];
		aimModes = json["aimModes"];
		smoothing = json["smoothing"];
		hotKeyMap = json["hotKeyMap"];
		fovCircle = json["fovCircle"];
		boneSelect = json["boneSelect"];
		hotTrigger = json["hotTrigger"];
		playerLock = json["playerLock"];
		aimModeMap = json["aimModeMap"];
		checkSpotted = json["checkSpotter"];
		hotSelectAim = json["hotSelectAim"];
		isHotTrigger = json["isHotTrigger"];
		hotSelectTrigger = json["hotSelectTrigger"];
	}
	catch (nlohmann::json::type_error& ignored) {
		Logger::warn("[Config.cpp] aimConfig section has missing properties, using defaults for missing options.");
	}

	return true;
}

inline nlohmann::json espConfig::to_json() {
	nlohmann::json json;
	json["head"] = head;
	json["joint"] = joint;
	json["state"] = state;
	json["width"] = width;
	json["health"] = health;
	json["pawnGun"] = pawnGun;
	json["c4State"] = c4State;
	json["distance"] = distance;
	json["skeleton"] = skeleton;
	json["pawnName"] = pawnName;
	json["boundBox"] = boundBox;
	json["gradient"] = gradient;
	json["c4Colors"] = c4Colors;
	json["snapLines"] = snapLines;
	json["hpCounter"] = hpCounter;
	json["isPawnGun"] = isPawnGun;
	json["filledBox"] = filledBox;
	json["c4Carrier"] = c4Carrier;
	json["c4Gradient"] = c4Gradient;
	json["isPawnName"] = isPawnName;
	json["headColours"] = headColours;
	json["isHealthBar"] = isHealthBar;
	json["c4Thickness"] = c4Thickness;
	json["jointColours"] = jointColours;
	json["checkSpotted"] = checkSpotted;
	json["cornerColours"] = cornerColours;
	json["filledBoxAlpha"] = filledBoxAlpha;
	json["spottedColours"] = spottedColours;
	json["cornerGradient"] = cornerGradient;
	json["skeletonColours"] = skeletonColours;
	json["attributeColours"] = attributeColours;
	json["c4ColorsGradient"] = c4ColorsGradient;
	json["boundBoxThickness"] = boundBoxThickness;
	json["notSpottedColours"] = notSpottedColours;

	return json;
}

inline bool espConfig::from_json(nlohmann::json json) {
	try {
		head = json["head"];
		joint = json["joint"];
		state = json["state"];
		width = json["width"];
		health[0] = json["health"][0];
		health[1] = json["health"][1];
		health[2] = json["health"][2];
		pawnGun = json["pawnGun"];
		c4State = json["c4State"];
		distance = json["distance"];
		skeleton = json["skeleton"];
		pawnName = json["pawnName"];
		boundBox = json["boundBox"];
		gradient = json["gradient"];
		snapLines = json["snapLines"];
		hpCounter = json["hpCounter"];
		isPawnGun = json["isPawnGun"];
		c4Gradient = json["c4Gradient"];
		cornerGradient[0] = json["cornerGradient"][0];
		cornerGradient[1] = json["cornerGradient"][1];
		cornerGradient[2] = json["cornerGradient"][2];
		filledBox = json["filledBox"];
		c4Carrier = json["c4Carrier"];
		isPawnName = json["isPawnName"];
		headColours[0] = json["headColours"][0];
		headColours[1] = json["headColours"][1];
		headColours[2] = json["headColours"][2];
		isHealthBar = json["isHealthBar"];
		jointColours[0] = json["jointColours"][0];
		jointColours[1] = json["jointColours"][1];
		jointColours[2] = json["jointColours"][2];
		c4Colors[0] = json["c4Colors"][0];
		c4Colors[1] = json["c4Colors"][1];
		c4Colors[2] = json["c4Colors"][2];
		c4Thickness = json["c4Thickness"];
		checkSpotted = json["checkSpotted"];
		cornerColours[0] = json["cornerColours"][0];
		cornerColours[1] = json["cornerColours"][1];
		cornerColours[2] = json["cornerColours"][2];
		filledBoxAlpha = json["filledBoxAlpha"];
		spottedColours[0] = json["spottedColours"][0];
		spottedColours[1] = json["spottedColours"][1];
		spottedColours[2] = json["spottedColours"][2];
		skeletonColours[0] = json["skeletonColours"][0];
		skeletonColours[1] = json["skeletonColours"][1];
		skeletonColours[2] = json["skeletonColours"][2];
		attributeColours[0] = json["attributeColours"][0];
		attributeColours[1] = json["attributeColours"][1];
		attributeColours[2] = json["attributeColours"][2];
		boundBoxThickness = json["boundBoxThickness"];
		notSpottedColours[0] = json["notSpottedColours"][0];
		notSpottedColours[1] = json["notSpottedColours"][1];
		notSpottedColours[2] = json["notSpottedColours"][2];
		c4ColorsGradient[0] = json["c4ColorsGradient"][0];
		c4ColorsGradient[1] = json["c4ColorsGradient"][1];
		c4ColorsGradient[2] = json["c4ColorsGradient"][2];
	}
	catch (nlohmann::json::type_error& ignored) {
		std::cout << "[Config.cpp] espConfig section has missing properties, using defaults for missing options." << std::endl;
	}

	return true;
}


inline nlohmann::json miscConfig::to_json() {
	nlohmann::json json;
	json["fov"] = fov;
	json["flash"] = flash;
	json["itemESP"] = itemESP;
	json["bunnyHop"] = bunnyHop;
	json["fovCheck"] = fovCheck;
	json["bombTimer"] = bombTimer;
	json["spectator"] = spectator;
	json["deathmatchMode"] = deathmatchMode;
	json["spectatorColours"] = spectatorColours;
	json["bombTimerColours"] = bombTimerColours;
	return json;
}

inline bool miscConfig::from_json(nlohmann::json json) {
	try {
		fov = json["fov"];
		flash = json["flash"];
		itemESP = json["itemESP"];
		bunnyHop = json["bunnyHop"];
		fovCheck = json["fovCheck"];
		spectator = json["spectator"];
		deathmatchMode = json["deathmatchMode"];
		spectatorColours[0] = json["spectatorColours"][0];
		spectatorColours[1] = json["spectatorColours"][1];
		spectatorColours[2] = json["spectatorColours"][2];
		bombTimer = json["bombTimer"];
		bombTimerColours[0] = json["bombTimerColours"][0];
		bombTimerColours[1] = json["bombTimerColours"][1];
		bombTimerColours[2] = json["bombTimerColours"][2];
	}
	catch (nlohmann::json::type_error& ignored) {
		Logger::warn("[Config.cpp] miscConfig section has missing properties, using defaults for missing options.");
	}

	return true;
}

nlohmann::json config::to_json() {
	nlohmann::json json;
	json["espConf"] = espConf.to_json();
	json["aimConf"] = aimConf.to_json();
	json["miscConf"] = miscConf.to_json();
	return json;
}

void config::load(int index) {
	if (index < 0 || index >= MAX_CONFIGS) return;

	try {
		Logger::info(L"[Config.cpp] Loading config: " + CONFIG_NAMES[index], true);
		configFiles[index] = json::readFromJsonFile(CONFIG_NAMES[index]);
		aimConf.from_json(configFiles[index]["aimConf"]);
		espConf.from_json(configFiles[index]["espConf"]);
		miscConf.from_json(configFiles[index]["miscConf"]);
	}
	catch (const nlohmann::json::type_error& e) {
		std::ostringstream str;

		str << "[Config.cpp] Error: " << e.what();

		Logger::error(str.str(), true);
		Logger::warn("[Config.cpp] Configuration section has missing properties, using defaults for missing options.", true);
	}
}


void config::save(int index) {
	if (index < 0 || index >= MAX_CONFIGS) return;

	std::wstring filePath = utils::getExePath() + L"\\" + CONFIG_NAMES[index];
	//std::wcout << filePath << " Current index: " << index << std::endl; // debug
	std::ofstream outfile(filePath, std::ios_base::out);
	outfile << config::to_json();
	outfile.close();
}

void config::create(int index) {
	if (index < 0 || index >= MAX_CONFIGS) return;

	std::wstring filePath = utils::getExePath() + L"\\" + CONFIG_NAMES[index];
	std::ofstream outfile(filePath);
	outfile.close();
}

bool config::exists(int index) {
	if (index < 0 || index >= MAX_CONFIGS) return false;

	std::wstring filePath = utils::getExePath() + L"\\" + CONFIG_NAMES[index];
	return std::ifstream(filePath).good();
}
