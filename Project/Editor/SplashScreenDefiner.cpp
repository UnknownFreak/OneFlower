#ifdef _EDITOR_
#include "SplashScreen.hpp"

SplashScreen::SplashScreen()
{
	splsh = gcnew EditorResources::Windows::SplashScreen();
	editorEvents = gcnew Editor::Events();
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
	splsh->setProgressValue(1);
	MainEditorWindow^ mainWindow = gcnew MainEditorWindow();
	splsh->setProgressValue(10);
	splsh->setProgressValue(20);

	editorEvents->registerEvents();

	splsh->setProgressValue(100);
	splsh->Hide();
	mainWindow->show();
	return mainWindow;

}
#endif
