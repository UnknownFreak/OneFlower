#ifdef _EDITOR_
#include "MainEditorWindow.hpp"
#include "ParentWindowWrapper.hpp"

#include <Graphic\GraphicsCore.hpp>

MainEditorWindow::MainEditorWindow()
{
	window = gcnew EditorResources::Windows::EditorWindow();
	Engine::Get<Gfx>().view.init(getEditorGameWindowView());
}

MainEditorWindow::MainEditorWindow(const MainEditorWindow% cpy)
{
	window = gcnew EditorResources::Windows::EditorWindow();
	Engine::Get<Gfx>().view.init(getEditorGameWindowView());
	window->Show();
}

MainEditorWindow::~MainEditorWindow()
{
	window->Close();
}

HWND MainEditorWindow::getEditorGameWindowView()
{
	return (HWND)window->getGameHost().ToPointer();
}

void MainEditorWindow::show()
{
	window->Show();
}
bool MainEditorWindow::isClosed()
{
	return window->isClosed();
}

#endif