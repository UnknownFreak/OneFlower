#include "EditorWindow.hpp"

#include <File/GameConfig.hpp>

Graphics::Editor::MainEditorWindow::MainEditorWindow() : UI::UIContext(swizzle::input::Keys::KeyNone, "MainWindow", true), newFileModal("New File")
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
		ImGui::Begin(this->uiName.c_str(), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav |ImGuiWindowFlags_NoBringToFrontOnFocus |ImGuiWindowFlags_MenuBar);
		{
			if(ImGui::BeginMainMenuBar())
			{
				if (ImGui::IsKeyPressed(ImGuiKeyModFlags_Ctrl |ImGuiKey_N) && newFileModal.isClosed())
				{
					newFileModal.open();
				}
				if(ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New", "Ctrl + N"))
					{
						newFileModal.open();
					}
					if (ImGui::MenuItem("Save", "Ctrl + S"))
					{
					}
					if (ImGui::MenuItem("Load"))
					{
					}
					if (ImGui::MenuItem("Save & Reload Dependencies", "Ctrl + Shift + R"))
					{

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
			if (newFileModal.isOpen())
				newFileModal.show();
			newFileModal.ImGuiRenderModal();

			ImGui::Text("MainEditorWindow: Hello World!");
		}
		ImGui::End();

	}
}
