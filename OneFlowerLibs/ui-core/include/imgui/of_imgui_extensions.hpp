#pragma once

#include <imgui/imgui.h>
#include <imgui/imconfig.h>

#include <string>

namespace of::imgui
{
	struct ProgressBarSettings
	{
		ImVec2 uvBackground0;
		ImVec2 uvBackground1;
		ImVec2 uvForeground0;
		ImVec2 uvForeground1;
		bool showText;
		int showMode = 0;
	};
	inline void Progressbar(ImTextureID progressBarTexture, const ImVec2& size, const float& min, const float& max, const float& currentValue, const ProgressBarSettings& settings)
	{
		const auto cursor = ImGui::GetCursorPos();

		ImGui::Image(progressBarTexture, size, settings.uvBackground0, settings.uvBackground1);
		const auto cursorEnd = ImGui::GetCursorPos();
		ImGui::SetCursorPos(cursor);

		// MATHO GOES HERE

		const float topValue = max - min;
		const float normalizedCurrent = currentValue - min;
		const float factor = normalizedCurrent / topValue;

		ImGui::Image(progressBarTexture, ImVec2{ size.x * factor, size.y }, settings.uvForeground0, ImVec2{ settings.uvForeground1.x * factor, settings.uvForeground1.y });

		if (settings.showText)
		{
			ImGui::SetCursorPos(cursor);
			std::string s;
			s.reserve(32);
			switch (settings.showMode)
			{
			case 0:
				s = std::to_string(normalizedCurrent) + "/" + std::to_string(topValue);
				break;
			case 1:
				s = std::to_string((currentValue / max) * 100.f) + "%";
				break;
			case 2:
				s = std::to_string(currentValue) + "/" + std::to_string(max);
				s += " (" + std::to_string((currentValue / max) * 100.f) + "%" + ")";
				break;
			default:
				s = "ERROR_INVALID_SHOW_MODE";
				break;
			}
			ImGui::Text(s.c_str());

		}
		ImGui::SetCursorPos(cursorEnd);
	}
}
