#include "ObjectSelector.hpp"

#include <Object/ObjectInstanceHandler.hpp>

namespace Graphics
{
	namespace Editor
	{

		ObjectSelector::ObjectSelector() : UIContext(swizzle::input::Keys::KeyNone, "ObjectSelector", true)
		{
			auto& x = Engine::GetModule<EngineModule::ObjectInstanceHandler>();

			auto onAdd = [&](GameObject* go) {
				objects[go] = false;
			};
			auto onDelete = [&](GameObject* go) {
				if (selected == go)
					selected = nullptr;
				objects.erase(go);
			};
			x.onAddAction(onAdd);
			x.onDeleteAction(onDelete);
		}

		void ObjectSelector::render()
		{
			ImGui::Begin(this->uiName.c_str());
			{
				ImGui::Columns(2);
				ImGui::SetColumnWidth(0, 300.f);
				if (ImGui::Button("Add object"))
				{
					Engine::GetModule<EngineModule::ObjectInstanceHandler>().addObject();
				}
				ImGui::SameLine();
				if (ImGui::Button("Delete object"))
				{
					if (selected)
					{
						Engine::GetModule<EngineModule::ObjectInstanceHandler>().removeObject(selected->id);
					}
				}
				if(ImGui::BeginListBox(" ", ImVec2(300.f,-1.f)))
				{
					for (auto& x : objects)
					{

						if (ImGui::Selectable(x.first->id.to_string().c_str(), &x.second))
						{
							if (selected != nullptr)
							{
								objects[selected] = false;
							}
							selected = x.first;
						}
					}
					ImGui::EndListBox();
				}
				ImGui::NextColumn();
				ImGui::Text("foo");
			}
			ImGui::End();
		}
	}
}


