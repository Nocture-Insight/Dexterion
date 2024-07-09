#include "attributes.hpp"



uintptr_t CCSPlayerController::getListEntry() {
	listEntry = MemMan.ReadMem<uintptr_t>(entityList + (0x8 * (id & 0x7FFF) >> 9) + 0x10);
	return listEntry;
}

uintptr_t CCSPlayerController::getController() {
	value = MemMan.ReadMem<uintptr_t>(listEntry + 0x78 * (id & 0x1FF));
	return value;
}

int CCSPlayerController::getPawnHealth() {
	pawnHealth = MemMan.ReadMem<int>(value + clientDLL::CCSPlayerController_["m_iPawnHealth"]);
	return pawnHealth;
}

bool CCSPlayerController::isAlive()
{
	alive = MemMan.ReadMem<int>(value + clientDLL::CCSPlayerController_["m_iPawnHealth"]) > 0 && MemMan.ReadMem<int>(value + clientDLL::CCSPlayerController_["m_iPawnHealth"]) < 2000;
	return alive;
}

uintptr_t getAddressBase(uintptr_t entityList, uintptr_t playerPawn) {
	uintptr_t listEntrySecond = MemMan.ReadMem<uintptr_t>(entityList + 0x8 * ((playerPawn & 0x7FFF) >> 9) + 16);
	return listEntrySecond == 0
		? 0
		: MemMan.ReadMem<uintptr_t>(listEntrySecond + 120 * (playerPawn & 0x1FF));
}

bool CCSPlayerController::isSpectating(bool localPlayer)
{
	uint32_t spectatorPawn = MemMan.ReadMem<uint32_t>(value + clientDLL::clientDLLOffsets["CBasePlayerController"]["fields"]["m_hPawn"]);
	uintptr_t pawn = getAddressBase(entityList, spectatorPawn);

	uintptr_t obs = MemMan.ReadMem<uintptr_t>(pawn + clientDLL::clientDLLOffsets["C_BasePlayerPawn"]["fields"]["m_pObserverServices"]);
	uint64_t oTarget = MemMan.ReadMem<uint64_t>(obs + clientDLL::clientDLLOffsets["CPlayer_ObserverServices"]["fields"]["m_hObserverTarget"]);
	uintptr_t handle = getAddressBase(entityList, oTarget);

	if (localPlayer) {
		uintptr_t LocalPlayer = MemMan.ReadMem<uintptr_t>(baseAddy + offsets::clientDLL["dwLocalPlayerController"]);
		uintptr_t localPlayerPawn = MemMan.ReadMem<uintptr_t>(LocalPlayer + clientDLL::clientDLLOffsets["CBasePlayerController"]["fields"]["m_hPawn"]);
		uintptr_t list_entry2 = MemMan.ReadMem<uintptr_t>(entityList + 0x8 * ((localPlayerPawn & 0x7FFF) >> 9) + 16);
		if (!list_entry2)
			return false;

		const uintptr_t CSlocalPlayerPawn = MemMan.ReadMem<uintptr_t>(list_entry2 + 120 * (localPlayerPawn & 0x1FF));

		if (obs && handle == CSlocalPlayerPawn)
			return true;
		return false;
	}
	else {
		if (obs)
			return true;
		return false;
	}
}

std::uint32_t CCSPlayerController::getC_CSPlayerPawn() {
	C_CSPlayerPawn_ = MemMan.ReadMem<std::uint32_t>(value + clientDLL::CCSPlayerController_["m_hPlayerPawn"]);
	return C_CSPlayerPawn_;
}

uintptr_t CCSPlayerController::getPawnTeam() {
	pawnTeam = MemMan.ReadMem<uintptr_t>(value + clientDLL::C_BaseEntity_["m_iTeamNum"]);
	return pawnTeam;
}

std::string CCSPlayerController::getPawnName() {
	pawnNameAddress = MemMan.ReadMem<uintptr_t>(value + clientDLL::CCSPlayerController_["m_sSanitizedPlayerName"]);
	if (pawnNameAddress) {
		char buf[MAX_PATH] = {};
		MemMan.ReadRawMem(pawnNameAddress, buf, MAX_PATH);
		pawnName = std::string(buf);
	}
	else {
		pawnName = "Unknown";
	}
	return pawnName;
}



uintptr_t C_CSPlayerPawn::getListEntry() {
	listEntry = MemMan.ReadMem<uintptr_t>(entityList + 0x8 * ((value & 0x7FFF) >> 9) + 0x10);
	return listEntry;
}

uintptr_t C_CSPlayerPawn::getPlayerPawn() {
	playerPawn = MemMan.ReadMem<uintptr_t>(listEntry + 0x78 * (value & 0x1FF));
	return playerPawn;
}

uintptr_t C_CSPlayerPawn::getPlayerPawnByCrossHairID(int crossHairEntity) {
	uintptr_t crosshairEntityEntry = MemMan.ReadMem<uintptr_t>(entityList + 0x8 * (crossHairEntity >> 9) + 0x10);
	playerPawn = MemMan.ReadMem<uintptr_t>(crosshairEntityEntry + 0x78 * (crossHairEntity & 0x1FF));
	return playerPawn;
}

Vector3 C_CSPlayerPawn::getOrigin() {
	origin = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_BasePlayerPawn_["m_vOldOrigin"]);
	return origin;
}

Vector3 C_CSPlayerPawn::getCameraPos() {
	cameraPos = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_vecLastClipCameraPos"]);
	return cameraPos;
}

Vector3 C_CSPlayerPawn::getEyePos() {
	eyePos = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_BasePlayerPawn_["m_vOldOrigin"]) +
		MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_BaseModelEntity_["m_vecViewOffset"]);
	return eyePos;
}

uintptr_t C_CSPlayerPawn::getCGameSceneNode() {
	CGameSceneNode = MemMan.ReadMem<uintptr_t>(playerPawn + clientDLL::C_BaseEntity_["m_pGameSceneNode"]);
	return CGameSceneNode;
}

Vector3 C_CSPlayerPawn::getViewAngles() {
	viewAngles = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_angEyeAngles"]);
	return viewAngles;
}

Vector3 C_CSPlayerPawn::getPosition() {
	position = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::CBaseAnimGraph_["m_vLastSlopeCheckPos"]);
	return position;
}

uint16_t C_CSPlayerPawn::getWeaponID() {
	C_CSWeaponBase = MemMan.ReadMem<uint64_t>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_pClippingWeapon"]);
	weaponID = MemMan.ReadMem<uint16_t>(C_CSWeaponBase + clientDLL::C_EconItemView_["m_iItemDefinitionIndex"] + clientDLL::C_AttributeContainer_["m_Item"] + clientDLL::C_EconEntity_["m_AttributeManager"]);
	return weaponID;
}

std::string C_CSPlayerPawn::getWeaponName() {
	C_CSWeaponBase = MemMan.ReadMem<uint64_t>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_pClippingWeapon"]);
	uint64_t weaponData = MemMan.ReadMem<uint64_t>(C_CSWeaponBase + clientDLL::C_BaseEntity_["m_nSubclassID"] + 0x8);
	uint64_t weaponNameAddress = MemMan.ReadMem<uint64_t>(weaponData + clientDLL::CCSWeaponBaseVData_["m_szName"]);

	if (!weaponNameAddress) {
		weaponName = "NULL";
	}
	else {
		char buf[MAX_PATH] = {};
		MemMan.ReadRawMem(weaponNameAddress, buf, MAX_PATH);
		weaponName = std::string(buf);
		if (weaponName.compare(0, 7, "weapon_") == 0) {
			weaponName = weaponName.substr(7, weaponName.length());
		}
	}
	return weaponName;
}

int C_CSPlayerPawn::getPawnHealth() {
	pawnHealth = MemMan.ReadMem<int>(playerPawn + clientDLL::C_BaseEntity_["m_iHealth"]);
	return pawnHealth;
}

uintptr_t C_CSPlayerPawn::getPawnTeam() {
	pawnTeam = MemMan.ReadMem<uintptr_t>(value + clientDLL::C_BaseEntity_["m_iTeamNum"]);
	return pawnTeam;
}

int C_CSPlayerPawn::getEntitySpotted() {
	spotted = MemMan.ReadMem<DWORD_PTR>(playerPawn + clientDLL::C_CSPlayerPawn_["m_entitySpottedState"] + clientDLL::EntitySpottedState_t_["m_bSpottedByMask"]);
	return spotted;
}

int C_CSPlayerPawn::getOwner() {
	owner = MemMan.ReadMem<DWORD_PTR>(playerPawn + clientDLL::C_BaseEntity_["m_hOwnerEntity"]);
	return owner;
}




uintptr_t LocalPlayer::getPlayerPawn() {
	playerPawn = MemMan.ReadMem<uintptr_t>(base + offsets::clientDLL["dwLocalPlayerPawn"]);
	return playerPawn;
}

uintptr_t LocalPlayer::getTeam() {
	team = MemMan.ReadMem<uintptr_t>(localPlayer + clientDLL::C_BaseEntity_["m_iTeamNum"]);
	return team;
}

Vector3 LocalPlayer::getCameraPos() {
	cameraPos = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_vecLastClipCameraPos"]);
	return cameraPos;
}

Vector3 LocalPlayer::getViewAngles() {
	viewAngles = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_BasePlayerPawn_["v_angle"]);
	return viewAngles;
}

Vector3 LocalPlayer::getPosition() {
	position = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::CBaseAnimGraph_["m_vLastSlopeCheckPos"]);
	return position;
}

Vector3 LocalPlayer::getOrigin() {
	origin = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_BasePlayerPawn_["m_vOldOrigin"]);
	return origin;
}

Vector3 LocalPlayer::getEyePos() {
	eyepos = this->getOrigin() + MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_BaseModelEntity_["m_vecViewOffset"]);
	return eyepos;
}

int LocalPlayer::getFlags() {
	flags = MemMan.ReadMem<int>(playerPawn + clientDLL::C_BaseEntity_["m_fFlags"]);
	return flags;
}

C_UTL_VECTOR LocalPlayer::getAimPunchCache() {
	aimPunchCache = MemMan.ReadMem<C_UTL_VECTOR>(playerPawn + clientDLL::C_CSPlayerPawn_["m_aimPunchCache"]);
	return aimPunchCache;
}

Vector2 LocalPlayer::getAimPunchAngle() {
	aimPunchAngle = MemMan.ReadMem<Vector2>(playerPawn + clientDLL::C_CSPlayerPawn_["m_aimPunchAngle"]);
	return aimPunchAngle;
}

int LocalPlayer::getShotsFired() {
	shotsFired = MemMan.ReadMem<int>(playerPawn + clientDLL::C_CSPlayerPawn_["m_iShotsFired"]);
	return shotsFired;
}

void LocalPlayer::noFlash() {
	MemMan.WriteMem<float>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_flFlashDuration"], 0.f);
}

int LocalPlayer::getEntitySpotted() {
	spotted = MemMan.ReadMem<DWORD_PTR>(playerPawn + clientDLL::C_CSPlayerPawn_["m_entitySpottedState"] + clientDLL::EntitySpottedState_t_["m_bSpottedByMask"]);
	return spotted;
}

bool LocalPlayer::getIsScoped() {
	isScoped = MemMan.ReadMem<DWORD_PTR>(playerPawn + clientDLL::C_CSPlayerPawn_["m_bIsScoped"]);
	return isScoped;
}



uintptr_t CGameSceneNode::getBoneArray() {
	boneArray = MemMan.ReadMem<uintptr_t>(value + clientDLL::CSkeletonInstance_["m_modelState"] + 0x80);
	return boneArray;
}

Vector3 CGameSceneNode::getOrigin() {
	origin = MemMan.ReadMem<Vector3>(value + clientDLL::CGameSceneNode_["m_vecAbsOrigin"]);
	return origin;
}



bool SharedFunctions::spottedCheck(C_CSPlayerPawn C_CSPlayerPawn, LocalPlayer localPlayer) {
	if (C_CSPlayerPawn.getEntitySpotted() & (1 << (localPlayer.playerPawn)) || localPlayer.getEntitySpotted() & (1 << (C_CSPlayerPawn.playerPawn))) return 1;
	return 0;
}

bool SharedFunctions::inGame(DWORD_PTR base) {
	uintptr_t gameRules = MemMan.ReadMem<uintptr_t>(base + offsets::clientDLL["dwGameRules"]);

	bool warmup = MemMan.ReadMem<bool>(gameRules + clientDLL::C_CSGameRules_["m_bWarmupPeriod"]);
	bool match = MemMan.ReadMem<bool>(gameRules + clientDLL::C_CSGameRules_["m_bHasMatchStarted"]);
	bool freeze = MemMan.ReadMem<bool>(gameRules + clientDLL::C_CSGameRules_["m_bFreezePeriod"]);

	return match;
}

bool C_C4::isPlanted() {
	planted = MemMan.ReadMem<bool>(base + offsets::clientDLL["dwPlantedC4"] - 0x8);
	return planted;
}

bool C_C4::isCarrier(int index) {
	return m_bCarrier = false;
}

uintptr_t C_C4::getCarrier() {
	return m_pCarrier = 0x0;
}

uintptr_t C_C4::getCGameSceneNode() {
	scene = MemMan.ReadMem<uintptr_t>(c4 + clientDLL::C_BaseEntity_["m_pGameSceneNode"]);
	return scene;
}
