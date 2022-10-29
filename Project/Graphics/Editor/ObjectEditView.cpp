#include "ObjectEditView.hpp"

#include <imgui/imgui.h>

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
					ImGui::Text("EditorFrame");
					ImGui::Text(Core::toHex((size_t)ptr).c_str());
				}
				ImGui::End();
			}
		}
	}
}
