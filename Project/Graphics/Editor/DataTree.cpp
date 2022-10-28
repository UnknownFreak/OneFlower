#include "DataTree.hpp"

#include <imgui/imgui.h>

namespace Graphics::Editor
{

	DataTree::DataTree()
	{
	}
	void DataTree::render()
	{
		ImGui::SetNextWindowPos({0, 20});
		ImGui::SetNextWindowSize({400, 1080});
		if(ImGui::Begin("DataTree", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus))
		{

		}
		ImGui::End();

	}
}
