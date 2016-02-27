#ifdef _DEBUG
#ifndef ENGINEITEMCREATORTYPEFIELD_HPP
#define ENGINEITEMCREATORTYPEFIELD_HPP
#include <windows.h>
#include <string>
#include <vector>
#include "../../../Vector.h"
class EngineItemCreatorTypeField
{
public:
	// no dtor needed since parent have destroywindow in dtor
	void start(HWND parent, HINSTANCE hInstance, Vector2 pos, Vector2 size,size_t ID, std::vector<std::string>items);
	std::string getCheckedType();
	size_t getRadiobuttonCount();
	void setItems(std::vector<std::string> items);
	void enable(bool value);
	void setText(std::string text);
private:
	std::vector<std::string> items;
	std::vector<HWND> radiobuttons;
	HWND panel;				//Panel
	size_t defID;

};
#endif
#endif