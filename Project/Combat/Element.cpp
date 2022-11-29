#include "Element.hpp"

#include <File/Asset/Manager.hpp>
#include <Module/EngineModuleManager.hpp>
#include <Module/Logger/OneLogger.hpp>

#include <imgui/imgui.h>
#include <Graphics/Editor/ViewModels/IObjectViewModel.hpp>
#include <Graphics/Editor/EditorBasicToolTip.hpp>
#include <Graphics/Editor/ModFileUuidHelperDropDown.hpp>

of::common::uuid Interfaces::Trait<Combat::Element>::typeId = of::common::uuid("1423d23c-e7d0-493a-9e03-0c68a1714703");

namespace Combat
{
	Element::Element() : IRequestable(Enums::ObjectType::Element), IObject()
	{

	}

	Element::Element(const Element& copy) : IRequestable(copy), IObject(copy), elementAttributes(copy.elementAttributes), damageToUnknownType(copy.damageToUnknownType)
	{

	}

	double Element::getElementModifier() const
	{
		return 1.0;
	}

	double Element::getElementModifier(const File::Mod::ModFileUUIDHelper& element) const
	{
		if (elementAttributes.find(element) != elementAttributes.end())
			return elementAttributes.at(element);
		else
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Combat::Element").Warning("Unknown Element type[" + element.name + "," + element.uuid.to_string() + "] called [<TODO>] defaulting "
				"to internal damageToUnknownType(" + std::to_string(damageToUnknownType).c_str() + ")");
			return damageToUnknownType;
		}
	}
	
	of::common::String Element::getElementAttributeName(const File::Mod::ModFileUUIDHelper& element) const
	{
		return Engine::GetModule<File::Asset::Manager>().requestor.requestUniqueInstance<Element>(element).name;
	}
	
	Interfaces::TypeInfo Element::getTrait() const
	{
		return { Interfaces::Trait<Element>::typeId };
	}

	void Element::render()
	{
		if(Graphics::Editor::ViewModels::renderInfo(this, true))
			mode = Enums::ObjectSaveMode::EDIT;

		ImGui::Text("Damage To Unknown Element Type:");
		if (ImGui::InputDouble("###ElementDamageToUnknownType", &damageToUnknownType))
		{
			mode = Enums::ObjectSaveMode::EDIT;
		}
		ImGui::Text("Elemental Modifiers");
		Graphics::Editor::BasicToolTip(
			"Elemental Modifiers are based on a factor towards that opposite element.\n"
			"E.g a factor of -1 would cause an \"healing\" effect based on 100% of the damage dealt.\n"
			"A factor of 1 would mean it does the 100% damage, a factor of 2 200%, etc.\n"
			"A factor of 0 would make that element have no impact whatsoever.");
		if (ImGui::BeginTable("####Element ID", 2, ImGuiTableFlags_Borders |ImGuiTableFlags_ScrollY, {0, 200.f}))
		{
			ImGui::TableSetupColumn("Element Id", ImGuiTableColumnFlags_WidthStretch, 3.3f);
			ImGui::TableSetupColumn("Factor");
			ImGui::TableHeadersRow();

			ImGui::TableNextRow();
			ImGui::TableNextColumn();

			std::vector<File::Mod::ModFileUUIDHelper> temp;
			for (auto& it : elementAttributes)
			{
				temp.push_back(it.first);
			}
			auto x = Graphics::Editor::Selectors::dropDownSelection("Select element to add...", Enums::ObjectType::Element, temp);
			if (x.isValid())
			{
				elementAttributes[x] = 0.0;
				mode = Enums::ObjectSaveMode::EDIT;
			}
			ImGui::TableNextColumn();
			ImGui::Text("N/A");

			for (auto& item : elementAttributes)
			{
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				if (item.first.name == fromMod && item.first.uuid == ID)
				{
					ImGui::SetNextItemWidth(-1);
					ImGui::TextColored({0, 220, 0, 255}, "self");
					Graphics::Editor::BasicToolTip("Self should always have factor set to 1, unless it's a very specific element... You've been warned!");
				}
				else
				{
					if (Engine::GetModule<File::Asset::Manager>().requestor.editorKeyExists(item.first))
					{
						of::common::String tmp_name = Engine::GetModule<File::Asset::Manager>().requestor.editorGetObjectName(item.first);
						if (tmp_name == "")
						{
							ImGui::Text(item.first.operator()(true).c_str());
							Graphics::Editor::BasicToolTip("Name str is empty, falling back to Id.");
						}
						else
						{
							ImGui::Text(tmp_name.c_str());
							Graphics::Editor::BasicToolTip("ID: " + item.first.operator()());
						}

					}
					else
					{
						ImGui::TextColored({ 255, 0, 0, 255 }, item.first.operator()(true).c_str());
						Graphics::Editor::BasicToolTip("Object is unavailable, either deleted or missing data file(s)");
					}

				}
				ImGui::SameLine();
				ImGui::SetCursorPosX(350.f);
				if (ImGui::Button("-"))
				{
					elementAttributes.erase(item.first);
					mode = Enums::ObjectSaveMode::EDIT;
					break;
				}
				ImGui::TableNextColumn();
				ImGui::SetNextItemWidth(-1);
				of::common::String s = "###" + item.first.operator()();
				if (ImGui::InputDouble(s.c_str(), &item.second))
				{
					mode = Enums::ObjectSaveMode::EDIT;
				}
			}
			
			ImGui::EndTable();
		}
	}
	
	of::common::String Element::getName() const
	{
		return name;
	}

	bool Element::operator==(const Element& other) const
	{
		return other.ID == ID;
	}
}