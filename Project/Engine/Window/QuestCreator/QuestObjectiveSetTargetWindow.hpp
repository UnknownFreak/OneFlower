#ifdef _DEBUG
#ifndef QUESTOBJECTIVESETTARGETWINDOW_HPP
#define QUESTOBJECTIVESETTARGETWINDOW_HPP
#include <Windows.h>
#include <string>
#include <vector>

struct ListViewItemStruct
{

	enum e_type {
		GameObject,
		Item,
		Zone,
	};
	ListViewItemStruct(size_t ID, std::string name, size_t type) : ID(ID), name(name), type(type) {};
	// ID of the represented itemx
	size_t ID;
	//Name of the represented item
	std::string name;
	//Type of the represented item (GameObject, Item or zone.
	size_t type;
};


class SetTargetWindow
{

public:

	SetTargetWindow();
	~SetTargetWindow();

	static LRESULT CALLBACK WndProc(HWND hWnd,UINT msg, WPARAM wParam, LPARAM lParam);

	void show(HWND hWnd, HINSTANCE hInst, std::string type);
	std::vector<ListViewItemStruct> items;
private:

	HWND set;

	HWND hWnd;

	HWND listBox;

	WNDCLASSEX wc;
	HINSTANCE hInstance;
	LPCTSTR windowDefinedName;

	static unsigned int registered;

};
#endif
#endif