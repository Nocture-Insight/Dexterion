#include "aim.hpp"

#include "random"
#include "windows.h"
#include <iostream>

#include "../util/config.hpp"

#include <iostream>

using namespace std;

void aim::aimBot(LocalPlayer localPlayer, Vector3 baseViewAngles, uintptr_t enemyPlayer, uintptr_t boneArray, MemoryManagement::moduleData client) {
	Vector3 aimPos;
	Vector3 newAngle;
	Vector3 angle;

	if (aimConf.playerLock)
		if (lockedPlayer != 0 && lockedPlayer != enemyPlayer) return;
	if (enemyPlayer == localPlayer.getPlayerPawn()) {
		lockedPlayer = 0;
		return;
	}

	aimPos = MemMan.ReadMem<Vector3>(boneArray + aimConf.boneMap[aimConf.bones[aimConf.boneSelect]] * 32);
	angle = CalculateAngle(localPlayer.eyepos, aimPos, localPlayer.viewAngles);

	float currentFov = aimConf.fov;
	float currentSmoothing = aimConf.smoothing;

	if (aimConf.rageModeEnabled) {
		currentFov = 360.0f; // Effectively no FOV limit
		currentSmoothing = 1.0f; // No smoothing
	}

	// 'angle' is the initial geometric angle to target.
	// 'rawTargetAngle' will be the final angle after FOV processing and potential RCS.
	Vector3 rawTargetAngle; 
	static Vector3 rcsOldPunch = {0,0,0}; // Static variable specifically for RCS state tracking (previously oldAngles)

	if (aimConf.rcs && localPlayer.getShotsFired() > 1 && localPlayer.shotsFired < 9999 /* Spectator check */) {
		Vector3 aimPunch = MemMan.ReadMem<Vector3>(localPlayer.getPlayerPawn() + clientDLL::C_CSPlayerPawn_["m_aimPunchAngle"]);

		if (aimConf.rageModeEnabled) {
			// Rage Mode RCS: Directly subtract scaled punch from the geometric target angle
			Vector3 rcsCompensatedAngle = angle; // Start with the pure geometric angle
			const float recoilScale = 2.0f;
			rcsCompensatedAngle.x -= aimPunch.x * recoilScale;
			rcsCompensatedAngle.y -= aimPunch.y * recoilScale;
			// Z component (roll) of aimPunch is usually not compensated this way.

			rawTargetAngle = calculateBestAngle(rcsCompensatedAngle, {0, 0, currentFov});
			// For rage RCS, rcsOldPunch isn't strictly needed for this calculation path, 
			// but keep it updated if non-rage RCS might still use it or for consistency.
			// Or, if rage implies no "memory" of old punch for delta, then rcsOldPunch might not be updated here.
			// Given the task, rage RCS is a direct subtraction, so no delta needed from rcsOldPunch.
            // However, to ensure non-rage RCS works correctly if toggled, rcsOldPunch should still be updated.
            rcsOldPunch = aimPunch; 
		} else {
			// Normal RCS: Use the existing delta-based offset logic
			Vector3 rcs_offsets = {0, 0, 0};
			// Calculate delta from the previous punch state (rcsOldPunch)
			rcs_offsets.x = (aimPunch.x - rcsOldPunch.x) * 2.f; 
			rcs_offsets.y = (aimPunch.y - rcsOldPunch.y) * 2.f;
			rcsOldPunch = aimPunch; // Update rcsOldPunch for the next iteration of normal RCS

			// Normal RCS applies these calculated offsets within calculateBestAngle
			rawTargetAngle = calculateBestAngle(angle, {rcs_offsets.x, rcs_offsets.y, currentFov});
		}
	} else {
		// No RCS, or not firing: Calculate rawTargetAngle directly from geometric angle with FOV
		rawTargetAngle = calculateBestAngle(angle, {0, 0, currentFov});
		// Reset rcsOldPunch if not firing, so normal RCS starts fresh next time
		if (!(localPlayer.getShotsFired() > 1 && localPlayer.shotsFired < 9999)) {
			rcsOldPunch = {0,0,0};
		}
	}
	bool hasValidRawTargetAngle = !rawTargetAngle.IsZero();

	// Determine if any aim action should be performed (either silent or mouse move)
	bool shouldPerformAimAction = false;
	if (aimConf.rageModeEnabled) {
		shouldPerformAimAction = hasValidRawTargetAngle;
	} else if (aimConf.isHotAim) {
		if (GetAsyncKeyState(aimConf.hotKeyMap[aimConf.hotKey[aimConf.hotSelectAim]])) {
			shouldPerformAimAction = hasValidRawTargetAngle;
		}
	} else { // Not rage, not hotkey based = always on if enabled
		shouldPerformAimAction = hasValidRawTargetAngle;
	}

	if (shouldPerformAimAction) {
		if (aimConf.rageModeEnabled && aimConf.ragePerfectSilent) {
			// --- Perfect Silent Aim Logic ---
			// Normalize angles
			rawTargetAngle.x = std::clamp(rawTargetAngle.x, -89.0f, 89.0f);
			rawTargetAngle.y = std::fmod(rawTargetAngle.y + 180.0f, 360.0f) - 180.0f;
			rawTargetAngle.z = 0.0f; // Roll is typically not set or set to 0

			// Write to memory. Assuming clientDLL::C_CSPlayerPawn_["m_pCameraServices"] and 
			// clientDLL::CCSPlayerBase_CameraServices_["m_vecViewAngle"] are valid offsets.
			// This is based on the structure observed in LocalPlayer::getViewAngles.
			// A more direct engine view angle (e.g., via dwClientState) would be preferable if available,
			// but we work with the offsets suggested by the existing codebase structure.
			uintptr_t playerPawnAddr = localPlayer.getPlayerPawn();
			if (playerPawnAddr != 0) { // Ensure playerPawn is valid
				// The following is speculative based on typical CS2 structure and clientDLL offsets.
				// It assumes m_pCameraServices is a direct member offset in C_CSPlayerPawn_
				// and m_vecViewAngle is an offset within the camera services structure.
				// These specific offsets (clientDLL::C_CSPlayerPawn_["m_pCameraServices"] and 
				// clientDLL::CCSPlayerBase_CameraServices_["m_vecViewAngle"]) must exist in the loaded JSON.
				// If they don't, this write will fail or write to an incorrect location.
				// This specific part is HIGHLY DEPENDENT on the actual JSON offset values.
				// For the purpose of this task, I will write the code as if these offsets are correctly defined.
				// Example path: PlayerPawn -> CameraServices -> ViewAngles
				try {
					uintptr_t cameraServicesPtr = MemMan.ReadMem<uintptr_t>(playerPawnAddr + clientDLL::C_CSPlayerPawn_["m_pCameraServices"].get<uintptr_t>());
					if (cameraServicesPtr != 0) {
						MemMan.WriteMem<Vector3>(cameraServicesPtr + clientDLL::CCSPlayerBase_CameraServices_["m_vecViewAngle"].get<uintptr_t>(), rawTargetAngle);
					}
				} catch (const nlohmann::json::exception& e) {
					// Log error or handle missing offset - for now, this will silently fail if offsets are missing
					// std::cerr << "JSON offset error for silent aim: " << e.what() << std::endl;
				}
			}
		} else {
			// --- Existing Mouse Movement Logic ---
			Vector3 mouseMoveAngleDelta = rawTargetAngle; // Use the preserved raw target angle
			mouseMoveAngleDelta.x = (mouseMoveAngleDelta.x / (0.022f * aimConf.sens)) / currentSmoothing;
			mouseMoveAngleDelta.y = (mouseMoveAngleDelta.y / (0.022f * aimConf.sens)) / currentSmoothing;

			if (!mouseMoveAngleDelta.IsZero()) { // Only move if there's a delta
				aim::moveMouseToLocation(mouseMoveAngleDelta);
			} else if (!aimConf.rageModeEnabled) { 
				// If delta is zero and not in rage mode, it implies no action needed, potentially release lock
				shouldPerformAimAction = false; // Override if mouse delta is zero and not rage
			}
		}
	} else { // No valid raw target angle to begin with, and not in rage mode (or hotkey not pressed)
		if (lockedPlayer == enemyPlayer) { // Clear lock if it was this player
			lockedPlayer = 0;
		}
		return; // Early exit
	}


	// Rage Auto Fire logic - triggers if any aim action was decided and conditions met
	if (aimConf.rageModeEnabled && aimConf.rageAutoFire && shouldPerformAimAction) {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}

	// Update lockedPlayer status
	if (shouldPerformAimAction) {
	    lockedPlayer = enemyPlayer;
	} else {
	    if (lockedPlayer == enemyPlayer) {
	        lockedPlayer = 0;
	    }
	}
}

void aim::moveMouseToLocation(Vector3 pos) {
	if (pos.x == 0.f && pos.y == 0.f && pos.z == 0.f) return;

	auto new_x = -pos.y;
	auto new_y = pos.x;

	mouse_event(MOUSEEVENTF_MOVE, new_x, new_y, 0, 0);
}

Vector3 aim::recoilControl(LocalPlayer localPlayer, bool move) {
	localPlayer.getAimPunchCache();
	localPlayer.getViewAngles();

	static Vector3 oldAngles = { 0, 0, 0 };
	Vector3 newAngles = { 0, 0, 0 };

	if (localPlayer.getShotsFired() == 54587654) return newAngles; // Spectator check

	if (localPlayer.getShotsFired() > 1) {
		Vector3 aimPunch = MemMan.ReadMem<Vector3>(localPlayer.getPlayerPawn() + clientDLL::C_CSPlayerPawn_["m_aimPunchAngle"]);
		newAngles.x = (aimPunch.x - oldAngles.x) * 2.f / (0.022f * aimConf.sens);
		newAngles.y = (aimPunch.y - oldAngles.y) * 2.f / (0.022f * aimConf.sens);

		if (move) aim::moveMouseToLocation(newAngles * -1);

		oldAngles = aimPunch;
		return newAngles;
	}
	else {
		oldAngles = { 0, 0, 0 };
		return newAngles;
	}
}

bool clicked = false;

const int trigger_cooldown()
{
	// Generate a random float between 0.0 and 0.5, add 0.15F to it, then cast to int milliseconds
	return static_cast<int>((static_cast<float>(rand() % 50) / 100.0F + 0.15F) * 1000);
}

void aim::triggerBot(LocalPlayer localPlayer, DWORD_PTR base) {
	int crossHairEntity = MemMan.ReadMem<int>(localPlayer.getPlayerPawn() + clientDLL::C_CSPlayerPawnBase_["m_iIDEntIndex"]);
	int localPlayerHealth = MemMan.ReadMem<int>(localPlayer.getPlayerPawn() + clientDLL::C_BaseEntity_["m_iHealth"]);
	if (!crossHairEntity) return;

	C_CSPlayerPawn crossHairPawn(base);
	CCSPlayerController crossHairEntityController(base);

	crossHairPawn.getPlayerPawnByCrossHairID(crossHairEntity);
	crossHairEntityController.value = crossHairPawn.playerPawn;

	bool isValidEntity = (crossHairEntity != -1 && crossHairPawn.getPawnHealth() > 0 && crossHairPawn.getPawnHealth() <= 100 && crossHairEntityController.getPawnTeam() != localPlayer.getTeam());
	bool isDeathMatchEntity = (crossHairEntity != -1 && crossHairPawn.getPawnHealth() > 0 && crossHairPawn.getPawnHealth() <= 100 && miscConf.deathmatchMode);

	if (localPlayerHealth > 100 || localPlayerHealth <= 0) return;

	if (aimConf.isHotTrigger) {
		if (GetAsyncKeyState(aimConf.hotKeyMap[aimConf.hotKey[aimConf.hotSelectTrigger]])) {
			if (isValidEntity || isDeathMatchEntity) {
				if (!clicked)
				{
					clicked = true;
					const int t = trigger_cooldown();
					//printf("Cooldown: %d ms\n", t);  // Correct printf syntax for int
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					Sleep(t/2);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					Sleep(t/2);
					clicked = false;
				}
			};
		}
	}
	else {
		if (isValidEntity || isDeathMatchEntity)
		{
			if (!clicked)
			{
				clicked = true;
				const int t = trigger_cooldown();
				//printf("Cooldown: %d ms\n", t);  // Correct printf syntax for int
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				Sleep(t / 2);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				Sleep(t / 2);
				clicked = false;
			}
		};
	}
}
