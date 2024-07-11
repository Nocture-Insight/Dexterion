#define WIN32_LEAN_AND_MEAN 

#include <windows.h>
#include <thread>
#include <chrono>

#include "util/config.hpp"
#include "gui/overlay.hpp"
#include "util/MemMan.hpp"
#include "util/attributes.hpp"

#include <iostream>
#include <psapi.h> // For EnumProcesses

LRESULT Wndproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
		return 0;
	}
	switch (msg) {
		case WM_SYSCOMMAND: {
			if ((wParam & 0xfff0) == SC_KEYMENU)
				return 0;
			break;
		}

		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// Function to get the PID of a process by its name
DWORD GetPIDByName(const wchar_t* processName) {
	DWORD pid = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32W pe32; // Using PROCESSENTRY32W for wide strings (wchar_t)
		pe32.dwSize = sizeof(PROCESSENTRY32W);
		if (Process32FirstW(hSnap, &pe32)) { // Using Process32FirstW for wide strings (wchar_t)
			do {
				if (_wcsicmp(pe32.szExeFile, processName) == 0) { // Using _wcsicmp for wide strings (wchar_t) comparison
					pid = pe32.th32ProcessID;
					break;
				}
			} while (Process32NextW(hSnap, &pe32)); // Using Process32NextW for wide strings (wchar_t)
		}
		CloseHandle(hSnap);
	}
	return pid;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Execute updateoffset.cmd in order to update before run
	SetConsoleTextAttribute(hConsole, 9);
	printf("[MemMan] Updating required files\n");
	SetConsoleTextAttribute(hConsole, 15);
	system("cmd.exe /C updateoffset.cmd");
	SetConsoleTextAttribute(hConsole, 10);
	printf("[MemMan] Required files updated\n");

	DWORD cs2Pid = 0;

	while (cs2Pid == 0) {
		// Search for cs2.exe among the PIDs
		cs2Pid = GetPIDByName(L"cs2.exe");
		if (cs2Pid != 0) {
			SetConsoleTextAttribute(hConsole, 10);
			std::wcout << L"cs2.exe found! PID: " << cs2Pid << std::endl;
		}
		else {
			SetConsoleTextAttribute(hConsole, 12);
			std::wcout << L"cs2.exe not found. Retrying in 5 seconds..." << std::endl;
			Sleep(5000); // Wait for 5 seconds before the next attempt
		}
	}
	
	// Memory and game related vars (used in entry and passed through overlay)
	int procId = MemMan.getPid(L"cs2.exe");
	SetConsoleTextAttribute(hConsole, 9);
	if (procId == 0)
		printf("[MemMan] Waiting For Counter Strike 2\n");
	while (procId == 0) {
		procId = MemMan.getPid(L"cs2.exe");
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	}
	SetConsoleTextAttribute(hConsole, 10);
	printf("[MemMan] Counter Strike 2 Found (%d)!\n", procId);
	SetConsoleTextAttribute(hConsole, 9);
	printf("[Config.hpp] Checking for config file...\n");
	if (config::exists()) {
		SetConsoleTextAttribute(hConsole, 10);
		printf("[Config.hpp] Config File Found! Loading preferred config...\n");
		config::load();
	}
	else {
		SetConsoleTextAttribute(hConsole, 12);
		printf("[Config.hpp] Config File Not Found! Loading Defaults...\n");
		config::create();
		config::save();
	}
	
	SetConsoleTextAttribute(hConsole, 9);
	printf("[dexterion.cpp] Getting addresses...\n");
	MemoryManagement::moduleData client;
	client.module = MemMan.getModule(procId, L"client.dll");
	client.base = MemMan.getModuleBase(procId, "client.dll");
	while (client.base == 0 || client.module == 0) {
		client.module = MemMan.getModule(procId, L"client.dll");
		client.base = MemMan.getModuleBase(procId, "client.dll");
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	}
	SetConsoleTextAttribute(hConsole, 10);
	printf("[dexterion.cpp] Addresses found succesfully!\n");

	SetConsoleTextAttribute(hConsole, 9);
	printf("[dexterion.cpp] Creating overlay...\n");
	// Overlay
	overlayESP overlayClass;
	WNDCLASSEXW windowClass = overlayClass.createWindowClass(hInstance, Wndproc, L"Dexterion");
	HWND window = overlayClass.createWindow(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

	SetConsoleTextAttribute(hConsole, 9);
	printf("[dexterion.cpp] Drawing overlay...\n");
	overlayClass.makeFrameIntoClientArea();
	overlayClass.makeDeviceAndSwapChain();
	overlayClass.initWindow(nShowCmd);

	SetConsoleTextAttribute(hConsole, 9);
	printf("[overlay.cpp] Starting main loop...\n");
	overlayClass.renderLoop(client);

	return 0;
}
