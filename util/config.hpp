#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "../json/jsonOps.hpp"

struct espConfig {
	// *--*--*--*--*--*Player ESP*--*--*--*--*--* \\ 
	bool state;
	bool checkSpotted;

	bool boundBox = true;
	bool gradient;
	bool filledBox = true;
	float boundBoxThickness = 1.5f;
	float spottedColours[4] = { 0.f,1.f,0.75f };
	float notSpottedColours[4] = { 0.f,1.f,0.75f };
	float cornerColours[4] = { 1.f,1.f,1.f };
	float cornerGradient[4] = { 1.f,1.f,1.f };
	float width = 2.5f;

	bool isPawnName;
	std::string pawnName;

	bool isPawnGun;
	std::string pawnGun;

	bool isHealthBar = true;
	bool hpCounter;
	float health[4];

	float attributeColours[4] = { 1.f,1.f,1.f };

	bool skeleton;
	float skeletonColours[4] = { 1.f,1.f,1.f };

	bool head;
	float headColours[4] = { 1.f,1.f,1.f };

	bool joint;
	float jointColours[4] = { 1.f,1.f,1.f };

	bool snapLines;

	bool distance;
	// *--*--*--*--*--*C4 ESP*--*--*--*--*--* \\ 
	bool c4State;
	bool c4Gradient;

	bool c4Carrier;

	float c4Thickness = 1.f;

	float c4Colors[4] = { 1.f, 0.f, 0.f};
	float c4ColorsGradient[4] = { 1.f, 0.f, 0.f };

	inline nlohmann::json to_json();
	inline bool from_json(nlohmann::json json);
};
espConfig espConf = {};


struct aimConfig {
	bool state;
	bool rcs;
	bool trigger;

	bool checkSpotted = true;
	float smoothing = 3.2f;

	float fov = 2.5;
	bool fovCircle;

	int bone;
	int boneSelect = 0;
	std::vector<std::string> bones = { "Head", "Neck","Chest", "Crotch" };
	std::map <std::string, int> boneMap = { {"Head",6},{"Neck",5},{"Chest",4},{"Crotch",0} };

	int aimMode = 3;
	std::vector<std::string> aimModes = { "Closest to Player", "Closest to Crosshair", "Furthest from crosshair", "No preference" };
	std::map <std::string, int> aimModeMap = { {"Closest to Player",0},{"Closest to Crosshair",1},{"Furthest from crosshair",2},{"No preference",3} };

	bool isHotAim;
	int hotSelectAim = 0;
	int hotAim;

	float sens = 1.25f;

	bool isHotTrigger;
	int hotSelectTrigger = 0;
	int hotTrigger;

	bool playerLock;

	std::vector<std::string> hotKey = { "SHIFT","ALT","CTRL","Left mouse","Right mouse" };
	std::map <std::string, int> hotKeyMap = { {"SHIFT",VK_SHIFT}, {"ALT",VK_MENU},{"CTRL",VK_CONTROL},{"Left mouse",VK_LBUTTON},{"Right mouse",VK_RBUTTON} };

	inline nlohmann::json to_json();
	inline bool from_json(nlohmann::json json);
};
aimConfig aimConf = {};


struct miscConfig {
	bool bunnyHop;
	bool flash;
	bool itemESP;
	bool deathmatchMode;
	bool fovCheck = false;
	bool spectator;
	bool bombTimer;
	bool consoleVisible = true;
	bool obsBypass = true;
	float bombTimerColours[4] = { 0.f, 1.f, 0.5f };
	float spectatorColours[4] = { 1.f, 0.f, 0.f };
	int fov = 90;

	inline nlohmann::json to_json();
	inline bool from_json(nlohmann::json json);
};
miscConfig miscConf = {};

//settings for configs
constexpr int MAX_CONFIGS = 4;
const std::wstring CONFIG_NAMES[MAX_CONFIGS] = { L"config.json", L"config1.json", L"config2.json", L"config3.json"};
inline namespace config {
	inline nlohmann::json configFiles[MAX_CONFIGS]; // to store multiple configs
	inline int currentConfigIndex = 0; // current config

	nlohmann::json to_json();
	void load(int index);
	void save(int index);
	void create(int index);
	bool exists(int index);
}

enum bones : int {
	head            = 6,
	neck            = 5,
	chest           = 4,
	chest_1         = 2,
	shoulderRight   = 8,
	shoulderLeft    = 13,
	elbowRight      = 9,
	elbowLeft       = 14,
	handRight       = 11,
	handLeft        = 16,
	crotch          = 0,
	leftCrotch      = 22,
	rightCrotch     = 25,
	kneeRight       = 26,
	kneeLeft        = 23,
	ankleRight      = 27,
	ankleLeft       = 24,
};

struct BoneConnection {
	int bone1;
	int bone2;

	BoneConnection(int b1, int b2) : bone1(b1), bone2(b2) {}
};

BoneConnection boneConnections[] = {
	BoneConnection(bones::head, bones::neck),
	BoneConnection(bones::neck, bones::chest),
	BoneConnection(bones::chest,bones::crotch),
	BoneConnection(bones::chest, bones::shoulderRight),
	BoneConnection(bones::shoulderRight, bones::elbowRight),
	BoneConnection(bones::elbowRight, bones::handRight),
	BoneConnection(bones::chest, bones::shoulderLeft),
	BoneConnection(bones::shoulderLeft, bones::elbowLeft),
	BoneConnection(bones::elbowLeft, bones::handLeft),
	BoneConnection(bones::chest, bones::chest_1),
	BoneConnection(bones::crotch, bones::leftCrotch),
	BoneConnection(bones::crotch, bones::rightCrotch),
	BoneConnection(bones::leftCrotch, bones::kneeLeft),
	BoneConnection(bones::kneeLeft,bones::ankleLeft),
	BoneConnection(bones::rightCrotch, bones::kneeRight),
	BoneConnection(bones::kneeRight, bones::ankleRight)
};

namespace DexterionSystem {
	std::string weaponIconsTTF = ".\\fonts\\weaponIcons.ttf";
}