//#ifdef _DEBUG
//#ifndef ENGINE_PREFAB_LIST_VIEWER_HPP
//#define ENGINE_PREFAB_LIST_VIEWER_HPP
//#include <Windows.h>
//#include <map>
//#include <commctrl.h>
//
//#include "../../../Vector.h"
//#include "../../../Game/LoadAndSave/Prefab.hpp"
//#include "../ItemCreator/EngineItemCreatorWindow.hpp"
//#include "../QuestCreator/EngineQuestCreatorWindow.hpp"
//#include "../../../Game/Item/Item.hpp"
//class Quest;
//class EnginePrefabListViewer
//{
//public:
//	~EnginePrefabListViewer();
//	void start();
//	EngineItemCreator itemCreator;
//	EngineQuestCreator questCreator;
//	HMENU rightClickMenu;
//	HWND hWnd;
//	Vector2 size;
//
//	void addPrefab(Prefab& prefab);
//	void removePrefab(Prefab& prefab);
//
//	void addItem(Items::Item* item);
//	void removeItem(Items::Item& item);
//
//	void addQuest(Quest& quset);
//	void removeQuet(Quest& quest);
//
//	void parentWindowNotify(LPNMHDR note, LPARAM lParam);
//
//	void onMouseMove(HWND parent,LONG x, LONG y);
//	void onMouseLUp(HWND parent);
//	// disables viewer during load
//	void Disable();
//	// enables viewer after load
//	void Enable();
//
//	std::map<Items::Item*, HTREEITEM>& allItemsInGame();
//	std::map<Prefab*, HTREEITEM>& allPrefabsInGame();
//
//private:
//
//	void removeSelected();
//	void editSelected();
//	void previewSelected();
//
//	void onBeginDrag(LPNMTREEVIEW idrag);
//	bool isDragging;
//	HMENU wierdHackMenu;
//	void addItem(HTREEITEM parent, Prefab& prefab);
//	void addItem(HTREEITEM parent, Items::Item& prefab);
//	void addLabel(HTREEITEM parent, std::string labelName, bool subTree);
//	void addITem(HTREEITEM parent, Quest& quest);
//	std::map<std::string, HTREEITEM> labels;
//	std::map<Prefab*, HTREEITEM> prefabs;
//	std::map<Items::Item*, HTREEITEM> items;
//	std::map<Quest*, HTREEITEM> quests;
//	HTREEITEM parent;
//
//	TV_INSERTSTRUCT inserter;
//};
//
//#endif
//#endif