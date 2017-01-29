#include "SplashScreen.hpp"
#include <Graphic\GraphicsCore.hpp>
#include <Animations\AnimationCore.hpp>
#ifdef _EDITOR_

SplashScreen::SplashScreen()
{
	splsh = gcnew EditorResources::SplashScreen::SplashScreen();

	auto gc = gcnew System::Windows::Interop::WindowInteropHelper(splsh);
	splashScreenHandle = gc->Handle;

	//SetParent(parent, (HWND)splashScreenHandle->ToPointer());
}

SplashScreen::~SplashScreen()
{
	splsh->Close();
}

MainEditorWindow^ SplashScreen::InitializeEditor()
{
	splsh->Show();
	auto gc = gcnew System::Windows::Interop::WindowInteropHelper(splsh);
	splsh->setProgressValue(1);
	MainEditorWindow^ mainWindow = gcnew MainEditorWindow();
	splsh->setProgressValue(10);
	Engine::ModelContainer.setRenderWindow(Engine::Graphic.view.render);
	splsh->setProgressValue(20);

	splsh->setProgressValue(100);
	splsh->Hide();
	mainWindow->show();
	return mainWindow;

}
#endif