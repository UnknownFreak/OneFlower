#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
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

	ImVec2 getXY(const ImVec4& vec)
	{
		return { vec.x, vec.y };
	}

	ImVec2 getWH(const ImVec4& vec)
	{
		return { vec.z, vec.w };
	}

	ImVec2 operator+(const ImVec2& a, const ImVec2& b)
	{
		return { a.x + b.x, a.y + b.y };
	}

	ImVec2& operator+=(ImVec2& a, const ImVec2& b)
	{
		a = a + b;
		return a;
	}

	struct BuffIconSettings
	{
		bool showIconDuration = true;
		int stackSize = 0;
		bool flashIconWhenAboutToExpire;
		std::string title;
		std::string body;

	};

	enum class ObjectiveState
	{
		Active,
		Complete,
		Failed
	};


	void RenderX(ImDrawList* draw_list, ImVec2 pos, ImU32 col, float sz)
	{
		using namespace ImGui;
		float thickness = ImMax(sz / 5.0f, 1.0f);
		sz -= thickness * 0.5f;
		pos += ImVec2(thickness * 0.25f, thickness * 0.25f);

		float half = sz / 2.0f;
		float bx = pos.x + half;
		float by = pos.y + sz - half;
		draw_list->PathLineTo(ImVec2(bx - half, by + half));
		draw_list->PathLineTo(ImVec2(bx + half , by - half));
		draw_list->PathStroke(col, 0, thickness);

		draw_list->PathLineTo(ImVec2(bx + half, by + half));
		draw_list->PathLineTo(ImVec2(bx - half, by - half));
		draw_list->PathStroke(col, 0, thickness);

	}

	void Progressbar(const ImVec2& size_arg, const float& min, const float& max, const float& currentValue, const ImColor& background, const ImColor& foreground)
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBg, background.operator ImVec4());
		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, foreground.operator ImVec4());
		ImGui::ProgressBar((currentValue - min) / (max - min), size_arg, "");
		ImGui::PopStyleColor(2);

	}

	void ProgressbarHitEffect(const ImVec2& size_arg, const float& min, const float& max, const float& currentValue, float& animateToValue, const ImColor& background, const ImColor& foreground, const ImColor& diminishBarColor, const bool& delay=true, const float& diminishSpeed=0.01f)
	{

		using namespace ImGui;
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;
		
		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), g.FontSize + style.FramePadding.y * 2.0f);
		ImRect bb(pos, pos + size);

		Progressbar(size_arg, min, max, currentValue, background, foreground);

		float fraction = (currentValue-min) / (max - min);

		if (animateToValue < 0.f || animateToValue < fraction)
			animateToValue = fraction;

		if (animateToValue > fraction)
		{
			RenderRectFilledRangeH(window->DrawList, bb, diminishBarColor, fraction, animateToValue, style.FrameRounding);
			if (delay == false)
				animateToValue -= diminishSpeed;
		}
	}

	void Progressbar(ImTextureID progressBarTexture, const ImVec2& size_arg, const float& min, const float& max, const float& currentValue, const ProgressBarSettings& settings)
	{
		/*
		using namespace ImGui;
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), g.FontSize + style.FramePadding.y * 2.0f);
		ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, 0))
			return;



		//Details top

		//Progressbar(size_arg, min, max, currentValue, ImColor(0, 0, 0), ImColor(255, 0, 0));
		*/

		const auto cursor = ImGui::GetCursorPos();
		ImGui::Image(progressBarTexture, size_arg, settings.uvBackground0, settings.uvBackground1);
		const auto cursorEnd = ImGui::GetCursorPos();
		ImGui::SetCursorPos(cursor);

		// MATHO GOES HERE

		const float topValue = max - min;
		const float normalizedCurrent = currentValue - min;
		const float factor = normalizedCurrent / topValue;

		ImGui::Image(progressBarTexture, ImVec2{ size_arg.x * factor, size_arg.y }, settings.uvForeground0, ImVec2{ settings.uvForeground1.x * factor, settings.uvForeground1.y });

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
		if (settings.flashIconWhenAboutToExpire && current < 5.f && current > 0.f && (int)((ImGui::GetTime() + current)/ 0.2f) % 2 == 0)
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
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 40.0f);

			const float old_size = ImGui::GetFont()->Scale;
			ImGui::GetFont()->Scale *= 1.5f;
			ImGui::PushFont(ImGui::GetFont());
			ImGui::TextUnformatted(settings.title.c_str());

			ImGui::GetFont()->Scale = old_size;
			ImGui::PopFont();

			ImGui::TextUnformatted(settings.body.c_str());

			{
				//ImGui::SetCursorPosX(cursor.x + size.x - 12.f);
				//ImGui::SetCursorPosY(cursorEnd.y - 18.f);
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

			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
		auto cursorEnd = ImGui::GetCursorPos();

		{
			ImGui::SetCursorPosX(cursor.x + size.x - 12.f);
			ImGui::SetCursorPosY(cursorEnd.y - 12.f);
			ImGui::Text(std::to_string(settings.stackSize).c_str());
		}

		ImGui::SetCursorPos(cursorEnd);
	}

	void objectiveIcon(const std::string& objectiveText, const ObjectiveState& state)
	{
		using namespace ImGui;

		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(objectiveText.c_str());
		const ImVec2 label_size = CalcTextSize(objectiveText.c_str(), NULL, true);

		const float square_sz = GetFrameHeight();
		const ImVec2 pos = window->DC.CursorPos;
		const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));
		ItemSize(total_bb, style.FramePadding.y);

		if (!ItemAdd(total_bb, id))
			return;

		const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));
		ImGui::RenderFrame(check_bb.Min, check_bb.Max, GetColorU32(ImGuiCol_FrameBg), true);
		ImVec2 label_pos = ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y);
		const float pad = ImMax(1.0f, IM_FLOOR(square_sz / 6.0f));

		switch (state)
		{
		case ObjectiveState::Active:
			RenderText(label_pos, objectiveText.c_str());
			break;
		case ObjectiveState::Complete:
		{
			RenderCheckMark(window->DrawList, check_bb.Min + ImVec2(pad, pad), GetColorU32(ImGuiCol_CheckMark), square_sz - pad * 2.0f);
			RenderText(label_pos, objectiveText.c_str());
		}
		break;
		case ObjectiveState::Failed:
		{

			ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 0, 0).operator ImVec4());
			ImGui::PushStyleColor(ImGuiCol_CheckMark, ImColor(255, 0, 0).operator ImVec4());
			RenderX(window->DrawList, check_bb.Min + ImVec2(pad, pad), GetColorU32(ImGuiCol_CheckMark), square_sz - pad * 2.0f);
			RenderText(label_pos, objectiveText.c_str());
			ImGui::PopStyleColor(2);
		}
		break;
		default:
			break;
		}
	}
}
