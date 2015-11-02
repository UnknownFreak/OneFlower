#ifndef EngineDebugWindow_HPP
#define EngineDebugWindow_HPP
#include <Windows.h>
#include <vector>
#include <string>
class EngineDebugMessage
{
public:
	EngineDebugMessage(std::string msg);
	~EngineDebugMessage();
	std::string msg;
	HWND hWnd;
};

class EngineDebugWindow
{
public:
	void init(HWND);
	std::vector<EngineDebugMessage> list;
	//Type write __LINE__ as the second parameter and __FILE__ on third
	void print(std::string msg,int __LINE___,std::string __FILE___);
	void clear();
private:
	HWND hWnd;
	int messageSize = 64;
	int height = 256;
	int width = 512;
};
#endif