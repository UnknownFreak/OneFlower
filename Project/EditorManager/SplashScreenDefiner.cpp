#include "SplashScreen.hpp"
#ifdef _EDITOR_

SplashScreen::SplashScreen(HWND parent)
{
	wrapper = gcnew ParentWndWrapper((long)parent);

	splsh = gcnew EditorResources::SplashScreen::SplashScreen();

	auto gc = gcnew System::Windows::Interop::WindowInteropHelper(splsh);
	splashScreenHandle = gc->Handle;

	SetParent(parent, (HWND)splashScreenHandle->ToPointer());
}

SplashScreen::~SplashScreen()
{
	splsh->Close();
}

void SplashScreen::InitializeEditor()
{
	splsh->Show();
}
#endif