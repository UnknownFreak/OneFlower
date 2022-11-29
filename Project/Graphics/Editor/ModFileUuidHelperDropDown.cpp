#include "ModFileUuidHelperDropDown.hpp"

#include <File/Asset/Manager.hpp>
#include <imgui/imgui.h>

namespace Graphics::Editor::Selectors
{
	std::vector<std::pair<of::common::String, File::Mod::ModFileUUIDHelper>> dropDownComboRefresh(const Enums::ObjectType& type, const std::vector<File::Mod::ModFileUUIDHelper>& filter)
	{
		std::vector<std::pair<of::common::String, File::Mod::ModFileUUIDHelper>> list;
		auto& manager = Engine::GetModule<File::Asset::Manager>();
		auto x = manager.requestor.listAllCurrentLoadedObjects(type);

		for (auto it = x.begin(); it != x.end(); it++)
		{
			if (std::find(filter.begin(), filter.end(), *it) == filter.end())
			{
				list.push_back({ manager.requestor.editorGetObjectName(*it), *it});
			}
		}
		return list;
	}
	File::Mod::ModFileUUIDHelper dropDownSelection(const of::common::String& prompt, const Enums::ObjectType& type, const std::vector<File::Mod::ModFileUUIDHelper>& filter)
	{
		if (cached[type].size() == 0)
		{
			cached[type] = dropDownComboRefresh(type, filter);
		}

		ImGui::SetNextItemWidth(300);
		of::common::String s = "### " + Enums::to_string(type);
		if (ImGui::BeginCombo(s.c_str(), prompt.c_str()))
		{
			for (auto& it : cached[type])
			{
				of::common::String name = it.first + ", " + it.second.operator()();
				if (ImGui::Selectable(name.c_str()))
				{
					File::Mod::ModFileUUIDHelper tmp = it.second;
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
		return File::Mod::ModFileUUIDHelper();
	}
}