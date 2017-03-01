#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP
#ifdef _EDITOR_

#include <Windows.h>
#include "ParentWindowWrapper.hpp"
#include "MainEditorWindow.hpp"
#include "EditorEvents.hpp"
ref class SplashScreen
{
	Editor::Events^ editorEvents;
	EditorResources::SplashScreen::SplashScreen^ splsh;

	IntPtr^ splashScreenHandle;
	// should be held in an own class called ManagedEvents
	void EditorOnCreate(Object^ sender, EditorResources::Functionality::NewModCreateEventArgs^args)
	{
	}

public:

	SplashScreen();
	~SplashScreen();
	MainEditorWindow^ InitializeEditor();

};
#endif
#endif