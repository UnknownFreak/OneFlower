#include "DataTree.hpp"

#include <imgui/imgui.h>
#include <imgui/basicToolTip.hpp>

#include <file/Handler.hpp>
#include "ModFileUuidHelperDropDown.hpp"

namespace Graphics::Editor
{

	DataTree::DataTree(float& height) : height(height), map(of::engine::GetModule<of::file::Handler>().archive.getLoadedMap())
	{
	}

	void DataTree::buildTree()
	{
		std::unordered_map<of::file::ObjectType, DataTreeItem> tmp_map;
		objectTree.items.clear();
		
		for (unsigned x = (unsigned)of::file::ObjectType::Header+1; x < (unsigned)of::file::ObjectType::EndIteration; x++)
		{
			if (of::file::hide_from_view((of::file::ObjectType)x) == false)
			{
				tmp_map[(of::file::ObjectType)x].name = of::file::to_string((of::file::ObjectType)x);
				tmp_map[(of::file::ObjectType)x].type = (of::file::ObjectType)x;
			}
		}
		
		for (auto& it : map)
		{
			auto* ir = it.second.get();
			if (ir && of::file::hide_from_view(ir->objectType) == false)
			{
				tmp_map[ir->objectType].items.push_back({ ir->getName(), ir});
			}
		}
		objectTree.name = "### ROOT";
		for (auto x : tmp_map)
			objectTree.items.push_back(x.second);

		std::sort(objectTree.items.begin(), objectTree.items.end());

	}

	void DataTree::drawTree(DataTreeItem& item)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;
	
		if (item.items.size() == 0)
		{
			flags |= ImGuiTreeNodeFlags_Bullet;
		}
	
		of::common::String itemName = item.name;
		if (itemName.empty())
		{
			if (item.ptr == nullptr)
				return;
			itemName = item.ptr->getModfile().operator()();
			//Engine::GetModule<of::logger::Logger>().Warning("Object has no display name, using the uuid for it instead.");
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
			bool recurse = false;
			if (item.ptr == nullptr)
			{
				recurse = ImGui::TreeNodeEx(itemName.c_str(), flags);
				ImGui::SameLine();
				ImGui::SetCursorPosX(400.f);
				if (ImGui::Button("+", { 18.f, 0 }))
				{
					//auto& manager = of::engine::GetModule<of::file::Handler>();
					of::logger::get().Always("Adding new item not yet supported in refactored code");
					//have of::editor::construct_from_type(item.type) that handles the creation of items instead.
					// The editor should handle all types not the requestor, it should just know how to add Requestables
					//manager.archive.add(item.type, manager.openedFile.name);
				}
			}
			else
			{

				recurse = ImGui::TreeNodeEx(itemName.c_str(), flags);
				of::imgui::BasicToolTip("From Mod: " + item.ptr->getModfile()() + "\nSaveMode: " + of::file::archive::to_string(item.ptr->mode));

				ImGui::SameLine();
				ImGui::SetCursorPosX(420.f);
				if(ImGui::Button("e", { 18.f, 0 }))
				{
					Selectors::cached.clear();
					editView.ptr = item.ptr;
				}
				if (editView.ptr == item.ptr)
				{
					item.name = item.ptr->getName();
				}
				ImGui::SameLine();
				ImGui::SetCursorPosX(440.f);
				if(ImGui::Button("-", { 18.f, 0 }))
				{
					item.ptr->mode = of::file::archive::ObjectSaveMode::REMOVE;
				};
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
			editView.render();
		}
		ImGui::End();

	}
	void DataTree::clear()
	{
		Selectors::cached.clear();
		editView.ptr = nullptr;
		objectTree.items.clear();
		mapSize = 0;
	}
}
