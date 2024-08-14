#include "menu.hpp"

#include "../features/entry.hpp"
#include "../util/config.hpp"
#include "../util/DiscordVerify.hpp"
#include "../util/utilFunctions.hpp"

void imGuiMenu::setStyle() {
		// Dexterion GUI style from ImThemes
		ImGuiStyle& style = ImGui::GetStyle();

		style.Alpha = 1.0f;
		style.DisabledAlpha = 1.0f;
		style.WindowPadding = ImVec2(12.0f, 12.0f);
		style.WindowRounding = 6.0f;
		style.WindowBorderSize = 0.0f;
		style.WindowMinSize = ImVec2(20.0f, 20.0f);
		style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
		style.WindowMenuButtonPosition = ImGuiDir_Right;
		style.ChildRounding = 6.0f;
		style.ChildBorderSize = 1.0f;
		style.PopupRounding = 6.0f;
		style.PopupBorderSize = 1.0f;
		style.FramePadding = ImVec2(20.0f, 8.0f);
		style.FrameRounding = 6.0f;
		style.FrameBorderSize = 0.0f;
		style.ItemSpacing = ImVec2(7.900000095367432f, 6.0f);
		style.ItemInnerSpacing = ImVec2(6.0f, 3.0f);
		style.CellPadding = ImVec2(12.0f, 6.0f);
		style.IndentSpacing = 20.0f;
		style.ColumnsMinSpacing = 20.0f;
		style.ScrollbarSize = 15.89999961853027f;
		style.ScrollbarRounding = 20.0f;
		style.GrabMinSize = 10.0f;
		style.GrabRounding = 20.0f;
		style.TabRounding = 6.0f;
		style.TabBorderSize = 1.0f;
		style.TabMinWidthForCloseButton = 10.0f;
		style.ColorButtonPosition = ImGuiDir_Left;
		style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
		style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

		style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.2745098173618317f, 0.3176470696926117f, 0.4509803950786591f, 1.0f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5372549295425415f, 0.5529412031173706f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 1.0f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 1.0f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
		style.Colors[ImGuiCol_Separator] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 1.0f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
		style.Colors[ImGuiCol_Tab] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6394850015640259f, 0.650776743888855f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4980392456054688f, 0.4980392456054688f, 1.0f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.4980392456054688f, 0.4980392456054688f, 1.0f);
		style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
		style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
		style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
		style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
		style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
		style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
}


void imGuiMenu::verticalSplitter(float width,float height) {
	ImGui::SameLine();
	ImGui::InvisibleButton("vsplitter", ImVec2(8.0f, height));
	if (ImGui::IsItemActive())
		width += ImGui::GetIO().MouseDelta.x;
	ImGui::SameLine();
}


void imGuiMenu::horizontalSplitter(float height) {
	ImGui::InvisibleButton("hsplitter", ImVec2(-1, 8.0f));
	if (ImGui::IsItemActive())
		height += ImGui::GetIO().MouseDelta.y;
}


void imGuiMenu::espRender() {
	if (tabCount == 1) {

		ImGui::BeginChild("Features", ImVec2(imGuiMenu::widthSeparatorInt, imGuiMenu::heightSeparatorInt), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Attributes");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("ESP toggle", &espConf.state);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		if (espConf.state) {
			ImGui::Checkbox("Gradient Line", &espConf.gradient);
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
			ImGui::Checkbox("Bounding Box", &espConf.boundBox);
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
			ImGui::Checkbox("Player name", &espConf.isPawnName);
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
			ImGui::Checkbox("Weapon name", &espConf.isPawnGun);
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
			ImGui::Checkbox("Health bar", &espConf.isHealthBar);
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
			ImGui::Checkbox("Skeleton", &espConf.skeleton);
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
			ImGui::Checkbox("Head", &espConf.head);
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
			ImGui::Checkbox("Joints", &espConf.joint);
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
			ImGui::Checkbox("Distance", &espConf.distance);
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
			ImGui::Checkbox("Snap lines", &espConf.snapLines);
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		}
		ImGui::Checkbox("C4 ESP Toggle", &espConf.c4State);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		if (espConf.c4State) {
			ImGui::Checkbox("Gradient", &espConf.c4Gradient);
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
			ImGui::Checkbox("Carrier", &espConf.c4Carrier);
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		}
		ImGui::EndChild();

		verticalSplitter(imGuiMenu::widthSeparatorInt, imGuiMenu::heightSeparatorInt);

		ImGui::BeginChild("Feature options", ImVec2(0, imGuiMenu::heightSeparatorInt), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Feature options");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::subTitleText);
		ImGui::Text("Main options");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Visibility check", &espConf.checkSpotted);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::subTitleText);
		ImGui::Text("Health options");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("HP counter", &espConf.hpCounter);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::subTitleText);
		ImGui::Text("Box options");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Colour fill", &espConf.filledBox);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::SliderFloat("Width", &espConf.width, 1.f, 5.f);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::SliderFloat("Thickness", &espConf.boundBoxThickness, 1.f, 3.f);
		if (espConf.c4State) {
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
			ImGui::SliderFloat("C4 Thickness", &espConf.c4Thickness, 1.f, 3.f);
		}
		ImGui::EndChild();

		horizontalSplitter(HEIGHT);

		ImGui::BeginChild("Colours", ImVec2(0, 0), true);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Colours");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::ColorEdit4("Box spotted", (float*)&espConf.spottedColours);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::ColorEdit4("Box not spotted", (float*)&espConf.notSpottedColours);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::ColorEdit4("Atrributes colour", (float*)&espConf.attributeColours);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::ColorEdit4("Corner colours", (float*)&espConf.cornerColours);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		if (espConf.gradient) {
			ImGui::ColorEdit4("Corner gradient", (float*)&espConf.cornerGradient);
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		}
		ImGui::ColorEdit4("Skeleton colour", (float*)&espConf.skeletonColours);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::ColorEdit4("Head colours", (float*)&espConf.headColours);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::ColorEdit4("Joint colours", (float*)&espConf.jointColours);
		if (espConf.c4State) {
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
			ImGui::ColorEdit4("C4 Colors", (float*)&espConf.c4Colors);
			if (espConf.c4Gradient) {
				ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
				ImGui::ColorEdit4("C4 Gradient", (float*)&espConf.c4ColorsGradient);
			}
		}

		ImGui::EndChild();
	}
}

void imGuiMenu::aimRender() {
	if (tabCount == 2) {

		ImGui::BeginChild("Aimbot", ImVec2(imGuiMenu::widthSeparatorInt, imGuiMenu::heightSeparatorInt), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Aimbot");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Aimbot", &aimConf.state);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Fov circle", &aimConf.fovCircle);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Visibility check", &aimConf.checkSpotted);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::SliderFloat("FOV", &aimConf.fov, 1.f, 25.f);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::SliderFloat("Smoothing", &aimConf.smoothing, 1.f, 5.f);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::InputFloat("Aim Sensibility", &aimConf.sens, 0.01f, 8.f);
		ImGui::EndChild();

		verticalSplitter(imGuiMenu::widthSeparatorInt, imGuiMenu::heightSeparatorInt);

		ImGui::BeginChild("Misc", ImVec2(0, imGuiMenu::heightSeparatorInt), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Miscellaneous aim functions");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Recoil Control", &aimConf.rcs);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Player lock", &aimConf.playerLock);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Trigger Bot", &aimConf.trigger);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Trigger bot hot key", &aimConf.isHotTrigger);
		if (aimConf.isHotTrigger) {
			ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
			if (ImGui::BeginCombo("Hot key", aimConf.hotKey[aimConf.hotSelectTrigger].c_str())) {
				for (int i = 0; i < aimConf.hotKey.size(); ++i) {
					const bool isSelected = (aimConf.hotTrigger == i);

					if (ImGui::Selectable(aimConf.hotKey[i].c_str(), isSelected)) {
						aimConf.hotSelectTrigger = i;
					}

					if (isSelected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
		}
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		if (ImGui::BeginCombo("Aimbot Preference", aimConf.aimModes[aimConf.aimMode].c_str())) {
			for (int i = 0; i < aimConf.aimModes.size(); ++i) {
				const bool isSelected = (aimConf.aimMode == i);

				if (ImGui::Selectable(aimConf.aimModes[i].c_str(), isSelected)) {
					aimConf.aimMode = i;
				}

				if (isSelected) {
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
		ImGui::EndChild();

		horizontalSplitter(HEIGHT);

		ImGui::BeginChild("Hitboxes", ImVec2(0, 0), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Hitboxes");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		if (ImGui::BeginCombo("Hit box", aimConf.bones[aimConf.boneSelect].c_str())) {
			for (int i = 0; i < aimConf.bones.size(); ++i) {
				const bool isSelected = (aimConf.bone == i);

				if (ImGui::Selectable(aimConf.bones[i].c_str(), isSelected)) {
					aimConf.boneSelect = i;
				}

				if (isSelected) {
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Aim bot hot key", &aimConf.isHotAim);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		if (aimConf.isHotAim) {
			if (ImGui::BeginCombo("Hot key", aimConf.hotKey[aimConf.hotSelectAim].c_str())) {
				for (int i = 0; i < aimConf.hotKey.size(); ++i) {
					const bool isSelected = (aimConf.hotAim == i);

					if (ImGui::Selectable(aimConf.hotKey[i].c_str(), isSelected)) {
						aimConf.hotSelectAim = i;
					}

					if (isSelected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
		}
		ImGui::EndChild();
	}
}

void imGuiMenu::miscRender() {
	if (tabCount == 3) {
		ImGui::BeginChild("Movement", ImVec2(imGuiMenu::widthSeparatorInt, imGuiMenu::heightSeparatorInt), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Utilities");
		ImGui::PopFont();
		ImGui::Checkbox("Console Visibility", &miscConf.consoleVisible);
		if (miscConf.consoleVisible != utils::intToBool(Shared::lastConsoleState)) {
			ShowWindow(GetConsoleWindow(), miscConf.consoleVisible ? SW_RESTORE : SW_HIDE);
			Shared::lastConsoleState = miscConf.consoleVisible ? SW_RESTORE : SW_HIDE;
		}
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("OBS BYPASS", &miscConf.obsBypass);
		if (miscConf.obsBypass != utils::intToBool(Shared::lastAffinity)) {
			SetWindowDisplayAffinity(GetForegroundWindow(), miscConf.obsBypass ? WDA_EXCLUDEFROMCAPTURE : WDA_NONE);
			Shared::lastAffinity = miscConf.obsBypass ? WDA_EXCLUDEFROMCAPTURE : WDA_NONE;
		}
		ImGui::EndChild();

		verticalSplitter(imGuiMenu::widthSeparatorInt, imGuiMenu::heightSeparatorInt);

		ImGui::BeginChild("Colours", ImVec2(0, imGuiMenu::heightSeparatorInt), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Colours");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::ColorEdit4("Spectator List", (float*)&miscConf.spectatorColours);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::ColorEdit4("Bomb Timer", (float*)&miscConf.bombTimerColours);
		ImGui::EndChild();

		horizontalSplitter(HEIGHT);

		ImGui::BeginChild("Visual", ImVec2(0, 0), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Visual");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("DeathMatch Mode", &miscConf.deathmatchMode);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Dropped Item ESP", &miscConf.itemESP);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Spectator List", &miscConf.spectator);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Bomb Timer", &miscConf.bombTimer);
		ImGui::EndChild();
	}
}

void imGuiMenu::aboutMeRender() {
	if (tabCount == 4) {
		ImGui::BeginChild("About the project", ImVec2(0, 0), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Github");
		ImGui::PopFont();
		ImGui::TextLinkOpenURL("Dexterion Github", "https://github.com/Skwrr/Dexterion");
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::TextLinkOpenURL("Tim Apple Github Fork", "https://github.com/kristofhracza/tim_apple");
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("HackVsHack");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::subTitleText);
		ImGui::Text("Release thread");
		ImGui::PopFont();
		ImGui::TextLinkOpenURL("Dexterion", "https://hackvshack.net/threads/dexterion-semi-external-cs2-cheat-updated-10-07-2024.4978/");
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("UnknownCheats");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::subTitleText);
		ImGui::Text("Release thread");
		ImGui::PopFont();
		ImGui::TextLinkOpenURL("Dexterion", " https://www.unknowncheats.me/forum/counter-strike-2-a/647464-dexterion-semi-external-cs2-cheat.html");
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::TextLinkOpenURL("Tim Apple", "https://www.unknowncheats.me/forum/counter-strike-2-releases/609206-cs2-external-cheat-tim-apple.html");
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::subTitleText);
		ImGui::Text("Developer Profile");
		ImGui::PopFont();
		ImGui::TextLinkOpenURL("UC Author Profile", "https://www.unknowncheats.me/forum/members/6169955.html");
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::TextLinkOpenURL("Discord", "https://www.unknowncheats.me/forum/members/6169955.html");
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Discord");
		ImGui::PopFont();
		ImGui::TextLinkOpenURL("Click me!", "https://discord.gg/jwueZBpnyY");
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text(("Version: " + utils::version).c_str());
		ImGui::EndChild();
	}
}


void imGuiMenu::configRender() {
	if (tabCount == 5) {
		ImGui::BeginChild("Configuration File", ImVec2(0, 0), true);
		std::vector<std::string> configNamesNarrow;
		// wide strings to narrow strings
		for (const auto& name : CONFIG_NAMES) {
			configNamesNarrow.push_back(std::string(name.begin(), name.end()));
		}
		// vector for combo
		std::vector<const char*> configNamesCStr;
		for (const auto& name : configNamesNarrow) {
			configNamesCStr.push_back(name.c_str());
		}

		ImGui::Combo("Select Config", &currentConfigIndex, configNamesCStr.data(), configNamesCStr.size());

		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		if (ImGui::Button("Refresh Config", ImVec2(210, 50))) {
			config::refresh();
			for (const auto& name : CONFIG_NAMES) {
				configNamesNarrow.push_back(std::string(name.begin(), name.end()));
			}
			for (const auto& name : configNamesNarrow) {
				configNamesCStr.push_back(name.c_str());
			}
		}
		if (ImGui::Button("Save", ImVec2(100, 50))) config::save(currentConfigIndex);
		ImGui::SameLine();
		if (ImGui::Button("Load", ImVec2(100, 50))) config::load(currentConfigIndex);

		ImGui::EndChild();
	}
}

void imGuiMenu::accountRender() {
	if (tabCount == 6) {
		ImGui::BeginChild("Account", ImVec2(0, 0), true);

		if (ImGui::Button("Copy My Token", ImVec2(150, 40))) {
			ImGui::LogToClipboard();
			ImGui::LogText(DiscordVerify::getToken(Shared::steamId).c_str());
			ImGui::LogFinish();
			ImGui::OpenPopup("CopyToken");
		}

		if (ImGui::BeginPopupModal("CopyToken", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
			ImGui::Text("Your token has been copied to your clipboard!");
			ImGui::Separator();
			if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			ImGui::EndPopup();
		}

		ImGui::EndChild();
	}
}

void imGuiMenu::menuBar() {
	ImGui::BeginMenuBar();

	if (ImGui::MenuItem("ESP")) tabCount = 1;
	if (ImGui::MenuItem("Aim")) tabCount = 2;
	if (ImGui::MenuItem("Misc")) tabCount = 3;
	if (ImGui::MenuItem("About")) tabCount = 4;
	if (ImGui::MenuItem("Config")) tabCount = 5;
	if (ImGui::MenuItem("Account")) tabCount = 6;

	ImGui::EndMenuBar();
}


void imGuiMenu::renderMenu(bool state) {
	ImGui::PushFont(normalText);
	ImGui::SetNextWindowSize({WIDTH,HEIGHT}, ImGuiCond_FirstUseEver);
	ImGui::Begin("Dexterion", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);
	
	// Config
	setStyle();
	menuBar();

	// Menus
	espRender();
	aimRender();
	miscRender();
	aboutMeRender();
	configRender();
	accountRender();

	ImGui::PopFont();
	ImGui::End();
}
