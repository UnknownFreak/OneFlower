#include "DataTree.hpp"

#include <imgui/imgui.h>

#include <File/Asset/Manager.hpp>

namespace Graphics::Editor
{

	DataTree::DataTree(float& height) : height(height), map(Engine::GetModule<File::Asset::Manager>().requestor.getLoadedMap())
	{
	}

	void DataTree::buildTree()
	{
		std::unordered_map<Enums::ObjectType, DataTreeItem> tmp_map;
		objectTree.items.clear();
		
		for (unsigned x = (unsigned)Enums::ObjectType::Header+1; x < (unsigned)Enums::ObjectType::EndIteration; x++)
		{
			if (Enums::hide_from_view((Enums::ObjectType)x) == false)
			{
				tmp_map[(Enums::ObjectType)x].name = Enums::to_string((Enums::ObjectType)x);
			}
		}
		
		for (auto& it : map)
		{
			auto* ir = it.second.get();
			if (ir && Enums::hide_from_view(ir->objectType) == false)
			{
				tmp_map[ir->objectType].items.push_back({ ir->getName(), ir});
			}
		}
		objectTree.name = "### ROOT";
		for (auto x : tmp_map)
			objectTree.items.push_back(x.second);

	}

	void DataTree::drawTree(const DataTreeItem& item)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;
	
		if (item.items.size() == 0)
		{
			flags |= ImGuiTreeNodeFlags_Bullet;
		}
	
		Core::String itemName = item.name;
		if (itemName.empty())
		{
			if (item.ptr == nullptr)
				return;
			itemName = item.ptr->getModfile().operator()();
			Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Object has no display name, using the uuid for it instead.");
		}
		if (itemName == "### ROOT")
		{
			for (auto& i : item.items)
			{
				drawTree(i);
			}
		}
		else
		{
			const bool recurse = ImGui::TreeNodeEx(itemName.c_str(), flags);

			if (item.ptr == nullptr)
			{
				ImGui::SameLine();
				ImGui::SetCursorPosX(400.f);
				ImGui::Button("+", {18.f, 0});
			}
			else
			{
				ImGui::SameLine();
				ImGui::TextDisabled("(?)");
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
					Core::String s = "From Mod: " + item.ptr->getModfile()();
					
					ImGui::TextUnformatted(s.c_str());
					ImGui::PopTextWrapPos();
					ImGui::EndTooltip();
				}
				ImGui::SameLine();
				ImGui::SetCursorPosX(420.f);
				ImGui::Button("e",{18.f, 0});
				ImGui::SameLine();
				ImGui::SetCursorPosX(440.f);
				ImGui::Button("-", {18.f, 0});
			}

			if (recurse)
			{
				for (auto& i : item.items)
				{
					drawTree(i);
				}
				ImGui::TreePop();
			}
		}
	}

	bool DataTree::treeNeedsUpdate()
	{
		if (mapSize != map.size())
		{
			mapSize = map.size();
			return true;
		}
		return false;
	}

	void DataTree::render()
	{
		if (treeNeedsUpdate())
		{
			buildTree();
		}

		ImGui::SetNextWindowPos({0, 20.f});
		ImGui::SetNextWindowSize({500.f, height-30.f});
		if(ImGui::Begin("DataTree", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings/* | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus*/))
		{
			drawTree(objectTree);
		}
		ImGui::End();

	}
}
