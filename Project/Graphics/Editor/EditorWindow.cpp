#include "EditorWindow.hpp"

#include <File/GameConfig.hpp>

Graphics::Editor::MainEditorWindow::MainEditorWindow() : UI::UIContext(swizzle::input::Keys::KeyNone, "MainWindow", true)
{
	auto gc = Engine::GetModule<EngineModule::GameConfig>();
	width = gc.videoMode.first;
	height = gc.videoMode.second;
}

void Graphics::Editor::MainEditorWindow::onMouseHover(const glm::vec2&)
{
}

void Graphics::Editor::MainEditorWindow::readInput()
{
}

void Graphics::Editor::MainEditorWindow::render()
{
	if (visible)
	{
		ImGui::SetNextWindowPos({ 0.f,0.f });
		ImGui::SetNextWindowSize({(float)width, (float)height});
		bool openPopup = false;
		ImGui::Begin(this->uiName.c_str(), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav |ImGuiWindowFlags_NoBringToFrontOnFocus |ImGuiWindowFlags_MenuBar);
		{
			if(ImGui::BeginMainMenuBar())
			{
				if(ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New", "Ctrl + N"))
					{
						openPopup = true;
//						ImGui::OpenPopup("New Mod");
					}
					ImGui::Separator();
					if (ImGui::MenuItem("Exit", "Alt + F4"))
					{
						std::exit(0);
					}
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}
			if (openPopup)
				ImGui::OpenPopup("New Mod");
			ImGui::SetNextWindowSize({ 600.f, 400.f });
			if (ImGui::BeginPopupModal("New Mod", nullptr, ImGuiWindowFlags_NoResize))
			{
				char c;
				ImGui::InputText("Mod Name", &c, 1);
				ImGui::Text("Dependencies");
				if (ImGui::BeginListBox("###Dependencies"))
				{
					ImGui::Selectable("###1", &test, 0, {0.f, 19.f});
					ImGui::SameLine();
					ImGui::Checkbox("Dep1", &test);
					ImGui::Selectable("###2", &test2, 0, { 0.f, 19.f });
					ImGui::SameLine();
					ImGui::Checkbox("Dep2", &test2);

					ImGui::Selectable("###Dep3", (bool*)&c, ImGuiSelectableFlags_::ImGuiSelectableFlags_Disabled, { 0,19 });
					ImGui::SameLine(30);
					ImGui::Checkbox("Dep2", &test2);
					ImGui::EndListBox();
				}

				if (ImGui::Button("Create"))
				{
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button("Cancel"))
				{
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
			ImGui::Text("MainEditorWindow: Hello World!");
		}
		ImGui::End();

	}
}
