#include "ModFileUuidHelperDropDown.hpp"

#include <asset/asset.hpp>
#include <imgui/imgui.h>

namespace Graphics::Editor::Selectors
{
	std::vector<std::pair<of::common::String, of::asset::AssetId>> dropDownComboRefresh(const of::asset::ObjectType& type, const std::vector<of::asset::AssetId>& filter)
	{
		std::vector<std::pair<of::common::String, of::asset::AssetId>> list;
		auto& manager = of::asset::getAssetRequestor();
		auto x = manager.listAllCurrentLoadedObjects(type);

		for (auto it = x.begin(); it != x.end(); it++)
		{
			if (std::find(filter.begin(), filter.end(), *it) == filter.end())
			{
				list.push_back({ manager.editorGetObjectName(*it), *it});
			}
		}
		return list;
	}
	of::asset::AssetId dropDownSelection(const of::common::String& prompt, const of::asset::ObjectType& type, const std::vector<of::asset::AssetId>& filter)
	{
		if (cached[type].size() == 0)
		{
			cached[type] = dropDownComboRefresh(type, filter);
		}

		ImGui::SetNextItemWidth(300);
		of::common::String s = "### " + of::asset::to_string(type);
		if (ImGui::BeginCombo(s.c_str(), prompt.c_str()))
		{
			for (auto& it : cached[type])
			{
				of::common::String name = it.first + ", " + it.second.operator()();
				if (ImGui::Selectable(name.c_str()))
				{
					of::asset::AssetId tmp = it.second;
					ImGui::EndCombo();
					cached.clear();
					return tmp;
				}
			}
			ImGui::EndCombo();
		}
		ImGui::SameLine();
		if (ImGui::Button("R"))
		{
			cached[type] = dropDownComboRefresh(type, filter);
		}
		return of::asset::AssetId();
	}
}