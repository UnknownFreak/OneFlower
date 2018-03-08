#ifndef _UNITTESTS_
// Windows.h has to be included first. Due to how clr works (only affects editormode).
#include <Windows.h>

#include <Core\Core.hpp>
#include <GameEntry.hpp>

sf::Event Engine::event;

#ifdef _EDITOR_
[System::STAThread]
#endif
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmnLine, int nShowCmd)
{

	GameEntry g;
	int return_value = g.main();
	Engine::Get<OneLogger>().DisableEditorLogging();
	Engine::Dispose();
	exit(return_value);
	return return_value;
}

#endif
