#ifdef _DEBUG
#include "EnginePrefabListViewer.hpp"
#include "../../../Engine.hpp"
#include "../../Resource.h"
#include "../../../Game/Item/Item.hpp"
#include "../../../Game/Item/Armor.hpp"
#include "../../../Game/Item/Ammo.hpp"
EnginePrefabListViewer::~EnginePrefabListViewer()
{
	DestroyWindow(hWnd);
	DestroyMenu(rightClickMenu);
	DestroyMenu(wierdHackMenu);
}
void EnginePrefabListViewer::start()
{
	//prolly move this.
	InitCommonControls();
	size.x = 256+128;
	size.y = 512;

	wierdHackMenu = CreatePopupMenu();
	rightClickMenu = LoadMenu(Engine::Window.hInstance, (LPCSTR)MENU_TREEVIEW_ID);
	AppendMenu(wierdHackMenu, MF_POPUP, (UINT_PTR)rightClickMenu, "Hack");

	hWnd = CreateWindowEx(0, WC_TREEVIEW, "Prefab Viewer",
		WS_VISIBLE | TVS_HASBUTTONS | TVS_TRACKSELECT | TVS_HASLINES | TVIS_DROPHILITED | TVS_LINESATROOT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		size.x, size.y, Engine::Window.hWnd, NULL, Engine::Window.hInstance, NULL);

	inserter.item.mask = TVIF_TEXT;
	addLabel(NULL, "Prefabs", false);
	addLabel(NULL, "Items", false);
	addLabel(NULL, "Effects", false);
	addLabel(NULL, "Quests", false);
	addLabel(NULL, "Sound", false);

	itemCreator.start();
	questCreator.start();
}

void EnginePrefabListViewer::addLabel(HTREEITEM p, std::string labelName, bool subTree)
{
	inserter.hParent = p;
	inserter.item.pszText = (LPSTR)labelName.c_str();
	inserter.hInsertAfter = (subTree == true) ? TVI_LAST : TVI_ROOT;
	parent = (HTREEITEM)SendMessage(hWnd, TVM_INSERTITEM, 0, (LPARAM)&inserter);
	labels.insert(std::pair<std::string,HTREEITEM>(labelName, parent));
}
void EnginePrefabListViewer::addPrefab(Prefab& prefab)
{
	std::map<std::string, HTREEITEM>::iterator it = labels.find(prefab.tag);
	if (it != labels.end())
	{
		addItem(it->second, prefab);
	}
	else
	{
		addLabel(labels.find("Prefabs")->second, prefab.tag, true);
		addItem(labels.find(prefab.tag)->second, prefab);
	}
}
void EnginePrefabListViewer::removePrefab(Prefab& prefab)
{
	std::map<Prefab*, HTREEITEM>::iterator it = prefabs.find(&prefab);
	if (it != prefabs.end())
	{
		SendMessage(hWnd, TVM_DELETEITEM, 0, (LPARAM)it->second);
		prefabs.erase(it);
	}
}
void EnginePrefabListViewer::addItem(HTREEITEM p, Prefab& prefab)
{
	inserter.hParent = p;
	inserter.item.pszText = (LPSTR)prefab.name.c_str();
	inserter.hInsertAfter = TVI_LAST;
	parent = (HTREEITEM)SendMessage(hWnd, TVM_INSERTITEM, 0, (LPARAM)&inserter);
	prefabs.insert(std::pair<Prefab*, HTREEITEM>(&prefab, parent));
	TreeView_SortChildren(hWnd, p, FALSE);
}
void EnginePrefabListViewer::addItem(HTREEITEM p, Item& item)
{
	std::string name = item.getName();
	inserter.hParent = p;
	inserter.item.pszText = (LPSTR)name.c_str();
	inserter.hInsertAfter = TVI_LAST;
	parent = (HTREEITEM)SendMessage(hWnd, TVM_INSERTITEM, 0, (LPARAM)&inserter);
	items.insert(std::pair<Item*, HTREEITEM>(&item, parent));
	TreeView_SortChildren(hWnd, p, FALSE);
}
void EnginePrefabListViewer::removeItem(Item& item)
{
	std::map<Item*, HTREEITEM>::iterator it = items.find(&item);
	if (it != items.end())
	{
		SendMessage(hWnd, TVM_DELETEITEM, 0, (LPARAM)it->second);
		items.erase(it);
	}
}
void EnginePrefabListViewer::addItem(Item* item)
{
	std::string secondTag = "NotDefined";
	std::map<std::string, HTREEITEM>::iterator it = labels.find(item->getTagAsString());
	if (item->getTagAsString() == "Armor")
	{
		Armor* arm = ((Armor*)item);
		secondTag = arm->armorType;
		it = labels.find(secondTag);
	}
	else if (item->getTagAsString() == "Weapon")
	{
		//secondTag = ((Weapon*)&item)->armorType;
		//it = labels.find(secondTag);
	}
	else if (item->getTagAsString() == "Ammo")
	{
		Ammo* a = ((Ammo*)item);
		secondTag = a->ammoType;
		it = labels.find(secondTag);
	}

	if (it != labels.end())
	{
		addItem(it->second, *item);
	}
	else
	{
		if (secondTag == "NotDefined")
		{
			addLabel(labels.find("Items")->second, item->getTagAsString(), true);
			addItem(labels.find(item->getTagAsString())->second, *item);
		}
		else
		{
			if (labels.find(item->getTagAsString()) != labels.end())
				addLabel(labels.find(item->getTagAsString())->second, secondTag, true);
			else
			{
				addLabel(labels.find("Items")->second, item->getTagAsString(), true);
				addLabel(labels.find(item->getTagAsString())->second, secondTag, true);
			}
			addItem(labels.find(secondTag)->second, *item);
		}
	}
}
void EnginePrefabListViewer::parentWindowNotify(LPNMHDR note, LPARAM lParam)
{
	if (note->hwndFrom == hWnd) // checks that it's the correct window
	{
		switch (note->code)
		{
			case NM_RCLICK:
			{
				POINT cursor;
				GetCursorPos(&cursor);
				BOOL rtn = TrackPopupMenu(rightClickMenu, TPM_RIGHTBUTTON | TPM_RETURNCMD, cursor.x, cursor.y, NULL, Engine::Window.hWnd, NULL);

				switch (rtn)
				{
				#pragma region Treeview_Menu
				case NEW_PREFAB:
					break;
				case NEW_ITEM:
				{
					itemCreator.show();
					break;
				}
				case NEW_QUEST:
				{
					questCreator.show();
					break;
				}
				case PREVIEW:
					break;
				default:
					break;
				}
				#pragma endregion
				break;
			}
			case TVN_BEGINDRAG:
			{
				onBeginDrag((LPNMTREEVIEW)lParam);
			}
			default:
				break;
		}
	}
}

void EnginePrefabListViewer::onBeginDrag(LPNMTREEVIEW itemDragged)
{
	HIMAGELIST himl;    // handle to image list 
	RECT rcItem;        // bounding rectangle of item 
	// Tell the tree-view control to create an image to use 
	// for dragging. 
	himl = TreeView_CreateDragImage(hWnd, itemDragged->itemNew.hItem);

	// Get the bounding rectangle of the item being dragged. 
	TreeView_GetItemRect(hWnd, itemDragged->itemNew.hItem, &rcItem, TRUE);
	TreeView_SelectItem(hWnd, itemDragged->itemNew.hItem);
	// Start the drag operation. 
	ImageList_BeginDrag(himl, 0, 0, 0);
	ImageList_DragEnter(hWnd, itemDragged->ptDrag.x, itemDragged->ptDrag.x);

	// Hide the mouse pointer, and direct mouse input to the 
	// parent window. 
	SetCapture(Engine::Window.hWnd);
	isDragging = true;
}
void EnginePrefabListViewer::onMouseMove(HWND parent, LONG x, LONG y)
{
	HTREEITEM hiTarget;
	TVHITTESTINFO test;
	if (isDragging)
	{
		POINT p;
		p.x = x;
		p.y = y;
		ScreenToClient(hWnd, &p);
		ImageList_DragMove(p.x, p.y);
		ImageList_DragShowNolock(FALSE);

		test.pt.x = p.x;
		test.pt.y = p.y;
		ImageList_DragShowNolock(TRUE);
	}
}
void EnginePrefabListViewer::onMouseLUp(HWND parent)
{

	if (isDragging)
	{
		HTREEITEM destination = TreeView_GetSelection(hWnd);
		if (destination != NULL)
		{
			//Todo
			std::map<Prefab*, HTREEITEM>::iterator pit = prefabs.begin();
			std::map<Prefab*, HTREEITEM>::iterator peit = prefabs.end();
			POINT p;
			RECT r;
			GetCursorPos(&p);
			//ScreenToClient(Engine::Graphic.view.render.getSystemHandle(), &p);
			GetWindowRect(Engine::Graphic.view.render.getSystemHandle(), &r);

			if (r.left < p.x && p.x < r.right && r.top < p.y && p.y < r.bottom)
			{ 
				for (pit; pit != peit; pit++)
				{
					if (pit->second == destination)
					{
						GameObject* go = pit->first->createFromPrefab();
						Engine::game.addGameObject(go);
						go->GetComponent<TransformComponent>()->position = Engine::Input.mouse.pos;
						Engine::World.EditorAddGameObjectToZone(*pit->first,go);
					}
				}
			}
		}
		ImageList_EndDrag();
		TreeView_SelectDropTarget(hWnd, NULL);
		ReleaseCapture();
		isDragging = false;
	}
}
void EnginePrefabListViewer::Enable()
{
	EnableWindow(hWnd, TRUE);
}
void EnginePrefabListViewer::Disable()
{
	EnableWindow(hWnd, FALSE);
}
#endif