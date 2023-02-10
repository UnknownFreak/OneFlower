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

	struct BuffIconSettings
	{
		bool showIconDuration = true;
		bool showIconDurationInSeconds;
		bool flashIconWhenAboutToExpire;

	};

	void Progressbar(ImTextureID progressBarTexture, const ImVec2& size, const float& min, const float& max, const float& currentValue, const ProgressBarSettings& settings)
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

	void BuffIcon(ImTextureID texture, const ImVec2& size, const float& maxDuration, const float&current, const BuffIconSettings& settings={})
	{
		auto cursor = ImGui::GetCursorPos();
		if (settings.flashIconWhenAboutToExpire && current < 5.f && (int)(ImGui::GetTime() / 0.5f) % 2)
		{
			ImGui::Dummy(size);
		}
		else
		{
			ImGui::Image(texture, size);
			
			auto drawList = ImGui::GetWindowDrawList();
			auto windowPos = ImGui::GetWindowPos();

			ImVec2 pos = { windowPos.x + cursor.x, windowPos.y + cursor.y };

			auto fraction = current / maxDuration;

			if (settings.showIconDuration)
			{

				if (fraction > 0.75)
				{
					auto fractionMod = (fraction - 0.75f) * 4;

					drawList->PathLineTo(
						{
							pos.x + size.x / 2 + (size.x / 2 * (1 - fractionMod)),
							pos.y + (size.y / 2 * (1 - fractionMod))
						});
				}

				if (fraction > 0.5f)// && fraction <= 0.75f)
				{
					auto fractionMod = std::min((fraction - 0.5f) * 4, 1.f);

					drawList->PathLineTo(
						{
							pos.x + size.x - (size.x / 2 * (1 - fractionMod)),
							pos.y + size.y / 2 + (size.y / 2 * (1 - fractionMod))
						});
				}

				if (fraction > 0.25f)
				{
					auto fractionMod = std::min((fraction - 0.25f) * 4, 1.f);
					drawList->PathLineTo(
						{
							pos.x + (size.x / 2.f * fractionMod),
							pos.y + size.y / 2.f + (size.y / 2.f * fractionMod)
						});
				}

				if (fraction > 0.f)
				{
					auto fractionMod = std::min(fraction * 4, 1.f);

					drawList->PathLineTo(
						{
							pos.x + (size.x / 2.f) * (1.f - fractionMod),
							pos.y + (size.y / 2.f * fractionMod)
						});
				}
				drawList->PathLineTo({ pos.x + size.x / 2, pos.y });
				drawList->PathStroke(ImColor(255, 255, 255), ImDrawFlags_None);
			}
		}
		auto cursorEnd = ImGui::GetCursorPos();
		if (settings.showIconDurationInSeconds)
		{
			ImGui::SetCursorPosX(cursor.x + size.x - 12.f);
			ImGui::SetCursorPosY(cursorEnd.y - 18.f);
			float temp = current;
			int hours = (int)current / 3600;
			temp -= hours * 3600;
			int minutes = (int)(temp) / 60;
			temp -= minutes * 60;
			std::string s = "";
			s.reserve(12);
			if (hours > 0)
				s += std::to_string(hours) + "h";
			if (minutes > 0)
				s += std::to_string(minutes) + "m";
			if (int(temp) > 0)
				s += std::to_string((int)temp) + "s";

			ImGui::Text(s.c_str());
		}
		ImGui::SetCursorPos(cursorEnd);
	}
}
