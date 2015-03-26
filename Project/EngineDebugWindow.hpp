#ifndef EngineDebugWindow_HPP
#define EngineDebugWindow_HPP
#include <Windows.h>
#include <map>
class EngineDebugWindow
{
public:
	EngineDebugWindow();
	~EngineDebugWindow();

	std::map<HWND,std::string> list;

private:
};

EngineDebugWindow::EngineDebugWindow()
{
}

EngineDebugWindow::~EngineDebugWindow()
{
}

#endif