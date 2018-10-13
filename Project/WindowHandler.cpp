#ifndef _UNITTESTS_
// Windows.h has to be included first. Due to how clr works (only affects editormode).
#ifdef _EDITOR_
#include <Windows.h>
#endif
#include <SFML\Window\Event.hpp>

#include <GameEntry.hpp>

sf::Event Game::event;

#ifdef _EDITOR_
[System::STAThread]
#endif
int __stdcall WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*prevInstance*/, LPSTR /*lpCmnLine*/, int /*nShowCmd*/)
{

	GameEntry g;
	int return_value = g.main();
	Engine::GetModule<OneLogger>().DisableEditorLogging();
	Engine::Dispose();
#ifdef _EDITOR_
	exit(return_value);
#else
	return return_value;
#endif
}

#endif
