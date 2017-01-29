#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP
#ifdef _EDITOR_

#include <Windows.h>
#include "ParentWindowWrapper.hpp"
#include "MainEditorWindow.hpp"

ref class SplashScreen
{
	EditorResources::SplashScreen::SplashScreen^ splsh;

	IntPtr^ splashScreenHandle;

public:

	SplashScreen();
	~SplashScreen();
	MainEditorWindow^ InitializeEditor();

};
#endif
#endif