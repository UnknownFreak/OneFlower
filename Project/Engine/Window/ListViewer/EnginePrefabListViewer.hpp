#ifdef _DEBUG
#ifndef ENGINE_PREFAB_LIST_VIEWER_HPP
#define ENGINE_PREFAB_LIST_VIEWER_HPP
#include <Windows.h>
#include <map>
#include <commctrl.h>

#include "../../../Vector.h"
#include "../../../Game/LoadAndSave/Prefab.hpp"
class EnginePrefabListViewer
{
public:
	~EnginePrefabListViewer();
	void start();

	HMENU rightClickMenu;
	HWND hWnd;
	Vector2 size;

	void addPrefab(Prefab& prefab);
	void removePrefab(Prefab& prefab);
	void parentWindowNotify(LPNMHDR note, LPARAM lParam);

	void onMouseMove(HWND parent,LONG x, LONG y);
	void onMouseLUp(HWND parent);
	// disables viewer during load
	void Disable();
	// enables viewer after load
	void Enable();
private:
	void onBeginDrag(LPNMTREEVIEW idrag);
	bool isDragging;
	HMENU wierdHackMenu;
	void addItem(HTREEITEM parent, Prefab& prefab);
	void addLabel(HTREEITEM parent, std::string labelName, bool subTree);
	std::map<std::string, HTREEITEM> labels;
	std::map<Prefab*, HTREEITEM> prefabs;
	HTREEITEM parent;

	TV_INSERTSTRUCT inserter;
};

#endif
#endif