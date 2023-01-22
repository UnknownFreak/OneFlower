#include "ObjectEditView.hpp"

#include "ViewModels/IRequestableRenderView.hpp"

#include <imgui/imgui.h>
#include <utils/expose/expose.hpp>
#include <combat/Element.hpp>

#include <imgui/imgui.h>
#include <Graphics/Editor/ViewModels/IObjectViewModel.hpp>
#include <Graphics/Editor/EditorBasicToolTip.hpp>
#include <Graphics/Editor/ModFileUuidHelperDropDown.hpp>

#include <file/Handler.hpp>

namespace of::expose
{
	//namespace
	//{
		template<>
		class ExposeToEditor<of::combat::Element>
		{
		public:
			static void edit(of::combat::Element& e)
			{
				//if(Graphics::Editor::ViewModels::renderInfo(r, true))
				//	e.mode = of::file::archive::ObjectSaveMode::EDIT;

				ImGui::Text("Damage To Unknown Element Type:");
				if (ImGui::InputDouble("###ElementDamageToUnknownType", &e.damageToUnknownType))
				{
					e.mode = of::file::archive::ObjectSaveMode::EDIT;
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

					std::vector<of::file::FileId> temp;
					for (auto& it : e.elementAttributes)
					{
						temp.push_back(it.first);
					}
					auto x = Graphics::Editor::Selectors::dropDownSelection("Select element to add...", of::file::ObjectType::Element, temp);
					if (x.isValid())
					{
						e.elementAttributes[x] = 0.0;
						e.mode = of::file::archive::ObjectSaveMode::EDIT;
					}
					ImGui::TableNextColumn();
					ImGui::Text("N/A");

					for (auto& item : e.elementAttributes)
					{
						ImGui::TableNextRow();
						ImGui::TableNextColumn();
						if (item.first.name == e.fromMod && item.first.uuid == e.ID)
						{
							ImGui::SetNextItemWidth(-1);
							ImGui::TextColored({0, 220, 0, 255}, "self");
							Graphics::Editor::BasicToolTip("Self should always have factor set to 1, unless it's a very specific element... You've been warned!");
						}
						else
						{
							if (of::engine::GetModule<of::file::Handler>().archive.editorKeyExists(item.first))
							{
								of::common::String tmp_name = of::engine::GetModule<of::file::Handler>().archive.editorGetObjectName(item.first);
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
							e.elementAttributes.erase(item.first);
							e.mode = of::file::archive::ObjectSaveMode::EDIT;
							break;
						}
						ImGui::TableNextColumn();
						ImGui::SetNextItemWidth(-1);
						of::common::String s = "###" + item.first.operator()();
						if (ImGui::InputDouble(s.c_str(), &item.second))
						{
							e.mode = of::file::archive::ObjectSaveMode::EDIT;
						}
					}

					ImGui::EndTable();
				}
			}

		};
		template<>
		class ExposeToEditor<of::file::archive::Requestable>
		{
		public:
			static void edit(of::file::archive::Requestable& r)
			{
				if (r.objectType == of::file::ObjectType::Element)
					ExposeToEditor<of::combat::Element>::edit((of::combat::Element&)r);
			}
		};
	//}
}


namespace Graphics
{
	namespace Editor
	{
		ObjectEditView::ObjectEditView()
		{

		}

		void ObjectEditView::render()
		{
			if (ptr)
			{
				ImGui::SetNextWindowPos({ 500, 20.f });
				ImGui::SetNextWindowSize({ 500.f, 600 });
				if (ImGui::Begin("EditView", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings))
				{
					ImGui::Text("Object Info: ");
					ViewModels::renderInfo(ptr);
					ImGui::Separator();
					of::expose::ExposeToEditor<of::file::archive::Requestable>::edit(*ptr);
				}
				ImGui::End();
			}
		}
	}
}
