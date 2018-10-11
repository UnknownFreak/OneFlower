#ifdef _EDITOR_
#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP

#include <Windows.h>
#include "ParentWindowWrapper.hpp"
#include "MainEditorWindow.hpp"
#include "EditorEvents.hpp"
ref class SplashScreen
{
	Editor::Events^ editorEvents;
	EditorResources::Windows::SplashScreen^ splsh;

	System::IntPtr^ splashScreenHandle;

public:

	SplashScreen();
	~SplashScreen();
	MainEditorWindow^ InitializeEditor();

};
#endif
#endif