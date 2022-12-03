#include "ModFileUuidHelperDropDown.hpp"

#include <file/Handler.hpp>
#include <imgui/imgui.h>

namespace Graphics::Editor::Selectors
{
	std::vector<std::pair<of::common::String, of::file::FileId>> dropDownComboRefresh(const of::file::ObjectType& type, const std::vector<of::file::FileId>& filter)
	{
		std::vector<std::pair<of::common::String, of::file::FileId>> list;
		auto& manager = of::engine::GetModule<of::file::Handler>();
		auto x = manager.archive.listAllCurrentLoadedObjects(type);

		for (auto it = x.begin(); it != x.end(); it++)
		{
			if (std::find(filter.begin(), filter.end(), *it) == filter.end())
			{
				list.push_back({ manager.archive.editorGetObjectName(*it), *it});
			}
		}
		return list;
	}
	of::file::FileId dropDownSelection(const of::common::String& prompt, const of::file::ObjectType& type, const std::vector<of::file::FileId>& filter)
	{
		if (cached[type].size() == 0)
		{
			cached[type] = dropDownComboRefresh(type, filter);
		}

		ImGui::SetNextItemWidth(300);
		of::common::String s = "### " + of::file::to_string(type);
		if (ImGui::BeginCombo(s.c_str(), prompt.c_str()))
		{
			for (auto& it : cached[type])
			{
				of::common::String name = it.first + ", " + it.second.operator()();
				if (ImGui::Selectable(name.c_str()))
				{
					of::file::FileId tmp = it.second;
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
		return of::file::FileId();
	}
}