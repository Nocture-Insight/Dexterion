#include "bomb.hpp"
#include "misc.hpp"

#include <iostream>

void bomb::timer(C_C4 C_C4) {
	if (!overlayESP::isMenuOpen()) {
		if (!misc::isGameWindowActive()) return;
	}
	bool planted = C_C4.isPlanted();
	bool defusing = C_C4.isBeingDefused();
	float defuseTime = C_C4.getDefuseTime();

	static float overlayWidth = 200.f;
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
	ImGui::SetNextWindowPos({ (ImGui::GetIO().DisplaySize.x - overlayWidth) / 2.f, 80.f }, ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize({ overlayWidth, 60 }, ImGuiCond_FirstUseEver);

	ImGui::Begin("Bomb Timer", nullptr, flags);

	uint64_t time = currentTimeMillis();

	if (planted && !isPlanted && (plantTime == NULL || time - plantTime > 60000)) {
		isPlanted = true;
		plantTime = time;
	}

	float remaining = (40000 - (int64_t)time + plantTime) / (float)1000;

	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 100.f) * .5f);
	float bar = planted ? remaining <= 0.f ? 0.f : remaining >= 40.f ? 1.f : (remaining / 40.f) : 0.f;

	if (isPlanted && remaining >= 0) {
		std::ostringstream oss;

		std::vector<std::string> sites = {
			"A",
			"B",
			"C"
		};

		oss.precision(4);
		oss << "Bomb on " << sites[C_C4.getPlantedSite()] << ": " << std::fixed << remaining << " s";

		std::string Text = std::move(oss).str().c_str();

		float windowWidth = ImGui::GetWindowSize().x;
		float textWidth = ImGui::CalcTextSize(Text.c_str()).x;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
		ImGui::Text(Text.c_str());
	}
	else {
		std::string Text = "C4 not planted";

		float windowWidth = ImGui::GetWindowSize().x;
		float textWidth = ImGui::CalcTextSize(Text.c_str()).x;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
		ImGui::Text(Text.c_str());
	}

	if (isPlanted && !planted) {
		isPlanted = false;
		bar = 0.f;
	}

	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, utils::float3ToImColor(miscConf.bombTimerColours, miscConf.bombTimerColours[3]).Value);
	ImGui::ProgressBar(bar, { overlayWidth - 20, 15 });
	ImGui::PopStyleColor();
	ImGui::End();
}