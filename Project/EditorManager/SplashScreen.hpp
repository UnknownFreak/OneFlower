#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP
#ifdef _EDITOR_

#include <Windows.h>
#using <WindowsBase.dll>
#using <PresentationCore.dll>
#using <PresentationFramework.dll>
#include "ParentWindowWrapper.hpp"
ref class SplashScreen
{
	EditorResources::SplashScreen::SplashScreen^ splsh;

	IntPtr^ splashScreenHandle;

	ParentWndWrapper^ wrapper;

public:

	SplashScreen(HWND parent);
	~SplashScreen();
	void InitializeEditor();
};
#endif
#endif