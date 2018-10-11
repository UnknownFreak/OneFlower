#ifdef _EDITOR_
#include "MainEditorWindow.hpp"
#include "ParentWindowWrapper.hpp"

#include <Core/EngineModule/EngineModuleManager.hpp>
#include <Graphic/Gfx.h>

MainEditorWindow::MainEditorWindow()
{
	window = gcnew EditorResources::Windows::EditorWindow();
	Engine::GetModule<Gfx>().view.init(getEditorGameWindowView());
}

MainEditorWindow::MainEditorWindow(const MainEditorWindow% cpy)
{
	window = gcnew EditorResources::Windows::EditorWindow();
	Engine::GetModule<Gfx>().view.init(getEditorGameWindowView());
	window->Show();
}

MainEditorWindow::~MainEditorWindow()
{
	window->Close();
}

HWND MainEditorWindow::getEditorGameWindowView()
{
	return (HWND)window->GetGameHost().ToPointer();
}

void MainEditorWindow::show()
{
	window->Show();
}
bool MainEditorWindow::isClosed()
{
	return window->IsClosed;
}

#endif