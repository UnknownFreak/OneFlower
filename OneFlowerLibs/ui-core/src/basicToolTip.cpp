#include <imgui/basicToolTip.hpp>

#include <imgui/imgui.h>

namespace of::imgui
{
	void BasicToolTip(const of::common::String& string)
	{
		ImGui::SameLine();
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 40.0f);


			ImGui::TextUnformatted(string.c_str());
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
}