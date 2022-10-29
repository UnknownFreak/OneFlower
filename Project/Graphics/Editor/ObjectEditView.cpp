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
				ImGui::SetNextWindowPos({ 0, 20.f });
				ImGui::SetNextWindowSize({ 500.f, 600 });
				if (ImGui::Begin("EditView", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings))
				{

				}
				ImGui::End();
			}
		}
	}
}
