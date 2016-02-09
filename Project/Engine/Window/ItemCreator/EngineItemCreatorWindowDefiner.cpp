#ifdef _DEBUG
#include "EngineItemCreatorWindow.hpp"
#include "../../../Engine.hpp"
#include "../../Resource.h"
#include "../DirectoryBrowser/DirectoryBrowser.hpp"
#include "../../../Game/Item/Item.hpp"
#include "../../../Game/Item/Armor.hpp"
#include "../../../Game/Item/Bag.hpp"
#include "../../../Game/Item/Ammo.hpp"
#include "../../../Game/Item/Consumable.hpp"

#include <CommCtrl.h>
LRESULT CALLBACK WndProcItemCreator(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK panelSubclassProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIDSubClass, DWORD_PTR dwRefData);

EngineItemCreator::~EngineItemCreator()
{
	RemoveWindowSubclass(itemTypeControl, panelSubclassProc, 1);
	DestroyWindow(hWnd);
	UnregisterClass(windowDefinedName, hInstance);
}

void EngineItemCreator::start()
{
	hInstance = Engine::Window.hInstance;
	DirectoryBrowser::init();
	size = Vector2(500, 700);
	windowDefinedName = "Item Creator";

	wc.lpszClassName = windowDefinedName;
	wc.lpfnWndProc = WndProcItemCreator;						// This function is called by windows
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;													// No menu
	wc.cbClsExtra = 0;														// No extra bytes after the window class
	wc.cbWndExtra = 0;														// structure or the window instance
	wc.hbrBackground = HBRUSH(COLOR_BTNFACE+1);

	if (!RegisterClassEx(&wc))
		MessageBox(NULL, "Error Registering The Window Class", "Error", MB_OK | MB_ICONERROR);

	hWnd = CreateWindowEx
		(
		0,							// Extended possibilites for variation
		windowDefinedName,			// Classname
		"Item Creator",				// Title Text
		WS_CAPTION |  WS_SYSMENU | WS_MINIMIZEBOX,					// default window
		CW_USEDEFAULT,				// Windows decides the position
		CW_USEDEFAULT,				// where the window ends up on the screen
		(int)size.x,						// The programs width
		(int)size.y,						// and height in pixels
		Engine::Window.hWnd,						// The window is a child-window to desktop
		NULL,						// No menu
		hInstance,					// Program Instance handler
		NULL						// No Window Creation data
		//this
		);
	strcpy_s(texturePath,DirectoryBrowser::windowDefaultDirectory);
	strcat_s(texturePath, "\\Texture");
	setTexturePathHWnd = CreateWindowEx(0, "BUTTON", "...", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 410, 20, 22, 20, hWnd, (HMENU)ID_SET_TEXTURE_PATH, hInstance, NULL);
	setTexturePathEditHWnd = CreateWindowEx(0, "EDIT", texturePath, WS_CHILD | WS_VISIBLE | ES_READONLY | WS_BORDER, 100, 20, 300, 20, hWnd, (HMENU)ID_TEXTURE_PATH_EDIT, hInstance, NULL);
	setTexturePathLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Texture Path", WS_CHILD | WS_VISIBLE, 10, 20, 90, 20, hWnd, HMENU(ID_CREATOR_LABELS), hInstance, NULL);

	itemNameHWnd = CreateWindowEx(0, "EDIT", "...", WS_CHILD | WS_VISIBLE | WS_BORDER, 100, 50, 170, 20, hWnd, (HMENU)ID_ITEMNAME, hInstance, NULL);
	itemNameLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Name", WS_CHILD | WS_VISIBLE, 50, 50, 90, 20, hWnd, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);

	itemIDHWnd = CreateWindowEx(0, "EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 126, 70, 49, 20, hWnd, (HMENU)ID_ITEMID, hInstance, NULL);
	itemIDPrefixHWnd = CreateWindowEx(0, "EDIT", Engine::World.getLoadedMod().c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_READONLY, 100, 70, 25, 20, hWnd, (HMENU)ID_ITEMID_PREFIX, hInstance, NULL);
	itemIDLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "ID", WS_CHILD | WS_VISIBLE, 75, 70, 14, 20, hWnd, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);
	itemIDButtonHWnd = CreateWindowEx(0, "BUTTON", "Get Valid ID", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 176, 70, 94, 20, hWnd, (HMENU)ID_ITEMID_NEXT_VALID_ID, hInstance, NULL);

	itemTooltipLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Item Tooltip", WS_CHILD | WS_VISIBLE, 15, 90, 90, 20, hWnd, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);
	itemToolTipHWnd = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOHSCROLL | WS_VSCROLL , 100, 90, 170, 80, hWnd, (HMENU)ID_ITEMTOOLTIP, hInstance, NULL);

	inventoryIconField.start(hWnd, hInstance, Vector2(300, 50), Vector2(32, 32), (HMENU)ID_ITEMICON_BUTTON, "Inventory Icon");

	itemWeightHWnd = CreateWindowEx(0, "EDIT", "0.0", WS_CHILD | WS_VISIBLE | WS_BORDER, 360, 130, 80, 20, hWnd, (HMENU)ID_ITEMWEIGHT, hInstance, NULL);
	itemWeightLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Weight", WS_CHILD | WS_VISIBLE, 300, 130, 50, 20, hWnd, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);

	itemPriceHWnd  = CreateWindowEx(0, "EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 360, 150, 80, 20, hWnd, (HMENU)ID_ITEMPRICE, hInstance, NULL);
	itemPriceLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Price", WS_CHILD | WS_VISIBLE, 314, 150, 50, 20, hWnd, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);

	itemTypeControl = CreateWindowEx(0, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_SUNKEN, 2, 180, 476, 475, hWnd, (HMENU)NULL, hInstance, NULL);
	itemStackableHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "BUTTON", "Stackable", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 130, 300, 100, 20, itemTypeControl, (HMENU)ID_ITEMSTACKABLE, hInstance, NULL);
	EnableWindow(itemStackableHWnd, false);
	itemCreateHWnd = CreateWindowEx(0, "BUTTON", "Create", WS_CHILD | WS_VISIBLE, 390, 620, 80, 20, hWnd, (HMENU)ID_ITEM_CREATE, hInstance, NULL);


	infoTip = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Disabled controls does not apply\nto/ modify item type", WS_CHILD | WS_VISIBLE, 130, 438, 240, 40, itemTypeControl, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);
	isTwoHanded = CreateWindowEx(WS_EX_TRANSPARENT, "BUTTON", "Two-Handed", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 130, 320, 100, 20, itemTypeControl, (HMENU)ID_ITEMSTACKABLE, hInstance, NULL);

	defenseLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Defense", WS_CHILD | WS_VISIBLE, 130, 340, 55, 20, itemTypeControl, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);
	defenseHWnd = CreateWindowEx(0, "EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 230, 340, 80, 20, itemTypeControl, (HMENU)ID_ITEM_DEFENSE, hInstance, NULL);

	damageLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Damage", WS_CHILD | WS_VISIBLE, 130, 360, 55, 20, itemTypeControl, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);
	damageHWnd = CreateWindowEx(0, "EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 230, 360, 80, 20, itemTypeControl, (HMENU)ID_ITEM_DAMAGE, hInstance, NULL);

	bagslotLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Bag Slots", WS_CHILD | WS_VISIBLE, 130, 380, 70, 20, itemTypeControl, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);
	bagslotHWnd = CreateWindowEx(0, "EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 230, 380, 80, 20, itemTypeControl, (HMENU)ID_ITEM_BAGSLOTS, hInstance, NULL);

	attachmentPointLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Attach Points", WS_CHILD | WS_VISIBLE, 130, 400, 100, 20, itemTypeControl, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);
	attachmentPointHWnd = CreateWindowEx(0, "BUTTON", "Set points", WS_CHILD | WS_VISIBLE, 230, 400, 80, 20, itemTypeControl, (HMENU)ID_ITEM_ATTACHPOINT, hInstance, NULL);

	effectEnchantLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Effect and\nEnchants", WS_CHILD | WS_VISIBLE, 310, 340, 70, 40, itemTypeControl, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);
	effectEnchantHWnd = CreateWindowEx(0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE, 380, 340, 80, 20, itemTypeControl, (HMENU)ID_ITEM_EFFECT, hInstance, NULL);

	SetWindowSubclass(itemTypeControl, panelSubclassProc, 1, panelDwRefData);

	itemtypes.start(itemTypeControl, hInstance, Vector2(2, 2), Vector2(122, 200),ID_ITEMTYPE, { "Ammo", "Armor", "Bag", "Consumable", "Crafting Mat",
		"Junk", "Trophy", "Weapon", "Undefined" });
	itemSpriteField.start(itemTypeControl, hInstance, Vector2(130, 2), Vector2(256, 256), (HMENU)ID_ITEMSPRITE_BUTTON, "Item Sprite");
	
	secondaryType.start(itemTypeControl, hInstance, Vector2(2, 208), Vector2(122, 260),ID_ITEMSECONDARYTYPE, {});
	
	updateFields();
	updateSecondaryFields();
}
void EngineItemCreator::setTexturePath()
{
	DirectoryBrowser::setDirectory(hWnd, texturePath);
	SendMessage(setTexturePathEditHWnd, WM_SETTEXT, NULL, (LPARAM)texturePath);
}
void EngineItemCreator::setNextValidID()
{
	if (ID == 0)
		ID++;
	while (Engine::World.EditorAllItems.find(ID) != Engine::World.EditorAllItems.end())
	{
		ID++;
	} 
	SendMessage(itemIDHWnd, WM_SETTEXT, NULL, (LPARAM)std::to_string(ID).c_str());
}

void EngineItemCreator::getSecondaryTypeChange()
{
	std::string newVal = secondaryType.getCheckedType();
	if (newVal != secondaryTypeSelected)
	{
		secondaryTypeSelected = newVal;
		updateSecondaryFields();
	}
}
void EngineItemCreator::getCheckedStateChange()
{
	std::string newVal = itemtypes.getCheckedType();
	if (newVal != selected)
	{
		selected = newVal;
		updateFields();
	}
}
void EngineItemCreator::updateSecondaryFields()
{
	if (secondaryTypeSelected == "Sword" || secondaryTypeSelected == "Axe")
		EnableWindow(isTwoHanded, true);
	else
		EnableWindow(isTwoHanded, false);
	if (selected == "Armor")
	{
		EnableWindow(defenseHWnd, true);
		EnableWindow(damageHWnd, false);
	}
	else if (selected == "Weapon")
	{
		if (secondaryTypeSelected == "Shield")
			EnableWindow(defenseHWnd, true);
		else
			EnableWindow(defenseHWnd, false);
		EnableWindow(damageHWnd, true);
	}
	else if (selected == "Ammo")
	{
		EnableWindow(defenseHWnd, false);
		EnableWindow(damageHWnd, true);
	}
	else
	{
		EnableWindow(defenseHWnd, false);
		EnableWindow(damageHWnd, false);
	}
	itemSpriteField.redraw();
}
void EngineItemCreator::updateFields()
{
	if (selected == "Armor")
	{
		itemSpriteField.enable(true);
		secondaryType.setItems({"Helm","Chest","Gloves","Leggings","Boots"});
		SendMessage(itemStackableHWnd, BM_SETCHECK, BST_UNCHECKED, NULL);
		secondaryType.enable(true);
		EnableWindow(bagslotHWnd, false);
		EnableWindow(attachmentPointHWnd, true);
		EnableWindow(effectEnchantHWnd, true);
	}
	else if (selected == "Weapon")
	{
		itemSpriteField.enable(true);
		secondaryType.setItems({ "Bow", "Crossbow", "Axe", "Dagger", "Fist", "Mace", "Polearm", "Shield", "Sword", "Grimiore", "Staff", "Stick/ Wand" });
		SendMessage(itemStackableHWnd, BM_SETCHECK, BST_UNCHECKED, NULL);
		secondaryType.enable(true);
		EnableWindow(bagslotHWnd, false);
		EnableWindow(attachmentPointHWnd, true);
		EnableWindow(effectEnchantHWnd, true);
	}
	else if (selected == "Ammo")
	{
		secondaryType.setItems({ "Arrow", "Bolt"});
		SendMessage(itemStackableHWnd, BM_SETCHECK, BST_CHECKED, NULL);
		secondaryType.enable(true);
		itemSpriteField.enable(true);
		EnableWindow(attachmentPointHWnd, true);
		EnableWindow(effectEnchantHWnd, true);
	}
	else if (selected == "Bag")
	{
		itemSpriteField.enable(false);
		SendMessage(itemStackableHWnd, BM_SETCHECK, BST_UNCHECKED, NULL);
		secondaryType.setItems({});
		secondaryType.enable(false);
		EnableWindow(bagslotHWnd, true);
		EnableWindow(attachmentPointHWnd, false);
		EnableWindow(effectEnchantHWnd, false);
	}
	else if (selected == "Consumable")
	{
		itemSpriteField.enable(false);
		SendMessage(itemStackableHWnd, BM_SETCHECK, BST_CHECKED, NULL);
		secondaryType.setItems({});
		secondaryType.enable(false);
		EnableWindow(bagslotHWnd, false);
		EnableWindow(attachmentPointHWnd, false);
		EnableWindow(effectEnchantHWnd, true);
	}
	else
	{
		itemSpriteField.enable(false);
		SendMessage(itemStackableHWnd, BM_SETCHECK, BST_CHECKED, NULL);
		secondaryType.setItems({});
		secondaryType.enable(false);
		EnableWindow(bagslotHWnd, false);
		EnableWindow(attachmentPointHWnd, false);
		EnableWindow(effectEnchantHWnd, false);
	}
}
std::string EngineItemCreator::getInventoryIcon()
{
	return inventoryIconField.getTextureName();
}
void EngineItemCreator::setInventoryIcon()
{
	inventoryIconField.drawImage(getInventoryIcon());
}
void EngineItemCreator::setSprite()
{
	itemSpriteField.drawImage(itemSpriteField.getTextureName());
}
void EngineItemCreator::repaint()
{
	itemSpriteField.redraw();
	inventoryIconField.redraw();
}
void EngineItemCreator::setEffect()
{
	effects.show(hWnd, hInstance);
}
void EngineItemCreator::setAttachmentPoints()
{
	if (itemSpriteField.hasTexture())
		attachpoint.show(&itemSpriteField, hWnd, hInstance);
	else
		MessageBox(hWnd, "No Texture set", "Err", NULL);
}
bool EngineItemCreator::createItem()
{
	if (ID)
	{
		std::string type = itemtypes.getCheckedType();
		std::string invIco = getInventoryIcon();
		std::string name;
		char ch[128];
		char tool[1024];
		std::string tooltip;
		SendMessage(itemNameHWnd, WM_GETTEXT, 128, (LPARAM)ch);
		SendMessage(itemToolTipHWnd, WM_GETTEXT, 1024, (LPARAM)tool);
		name = ch;
		tooltip = tool;
		char numbers[15];
		double weight;
		size_t price;
		bool stackable;
		int defense;
		int damage;
		int slots;
		stackable = (BST_CHECKED==SendMessage(itemStackableHWnd, BM_GETCHECK, NULL, NULL));

		SendMessage(itemWeightHWnd, WM_GETTEXT, 15, (LPARAM)numbers);
		weight = std::stod(numbers);
		SendMessage(itemPriceHWnd, WM_GETTEXT, 15, (LPARAM)numbers);
		price = std::stoi(numbers);
		SendMessage(defenseHWnd, WM_GETTEXT, 15, (LPARAM)numbers);
		defense = std::stoi(numbers);
		SendMessage(damageHWnd, WM_GETTEXT, 15, (LPARAM)numbers);
		damage = std::stoi(numbers);
		SendMessage(bagslotHWnd, WM_GETTEXT, 15, (LPARAM)numbers);
		slots = std::stoi(numbers);
		Item* tmp;
		if (type == "Undefined")
		{
			tmp = new Item(ID, stackable, name, invIco, Item::undefined, weight, price, tooltip);
			Engine::World.EditorAllItems.insert(std::pair<size_t, Item*>(ID, tmp));
		}
		else if (type == "Trophy")
		{
			tmp = new Item(ID, stackable, name, invIco, Item::trophy, weight, price, tooltip);
			Engine::World.EditorAllItems.insert(std::pair<size_t, Item*>(ID, tmp));
		}
		else if (type == "Junk")
		{
			tmp = new Item(ID, stackable, name, invIco, Item::junk, weight, price, tooltip);
			Engine::World.EditorAllItems.insert(std::pair<size_t, Item*>(ID, tmp));
		}
		else if (type == "Crafting Mat")
		{
			tmp = new Item(ID, stackable, name, invIco, Item::craftingMaterial, weight, price, tooltip);
			Engine::World.EditorAllItems.insert(std::pair<size_t, Item*>(ID, tmp));
		}
		else if (type == "Ammo")
		{
			tmp = new Ammo(ID,name,invIco,weight,price,tooltip,itemSpriteField.getTextureName(),damage,Ammo::Arrow);
			Engine::World.EditorAllItems.insert(std::pair<size_t, Item*>(ID, tmp));
		}
		else if (type == "Bag")
		{
			tmp = new Bag(ID,name,invIco,weight,price,tooltip,slots);
			Engine::World.EditorAllItems.insert(std::pair<size_t, Item*>(ID, tmp));
		}
		else if (type == "Armor")
		{
			tmp = new Armor(ID, defense, name, invIco, weight, price, tooltip, secondaryType.getCheckedType(),itemSpriteField.getTextureName(), attachpoint.attachpoints);
			Engine::World.EditorAllItems.insert(std::pair<size_t, Item*>(ID, tmp));
		}
		else if (type == "Consumable")
		{
			tmp = new Consumable(ID,name,invIco,weight,price,tooltip);
			Engine::World.EditorAllItems.insert(std::pair<size_t, Item*>(ID, tmp));
		}
		else
			return false;
		Engine::Window.prefabList.addItem(tmp);
		effects.clearEffect();
		return true;
	}
	else
	{
		MessageBox(hWnd, "ID cannot be 0", "err", NULL);
	}
	return false;
}
LRESULT CALLBACK panelSubclassProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIDSubClass,DWORD_PTR dwRefData)
{
	if (msg == WM_COMMAND || msg == WM_CTLCOLORSTATIC || msg == WM_NOTIFY)
		SendMessage(GetParent(hWnd), msg, wParam, lParam);
	return DefSubclassProc(hWnd,msg,wParam,lParam);
}
LRESULT CALLBACK WndProcItemCreator(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MOVE:
	{
		Engine::Window.prefabList.itemCreator.repaint();
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		switch (GetDlgCtrlID((HWND)lParam))
		{
		//case ID_ITEMTYPE:
		case ID_CREATOR_LABELS:
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (LRESULT)GetStockObject(NULL_BRUSH);
		default:
			break;
		}
	}
	case WM_COMMAND:
	{
		Engine::Window.prefabList.itemCreator.getCheckedStateChange();
		Engine::Window.prefabList.itemCreator.getSecondaryTypeChange();
		switch (LOWORD(wParam))
		{
			case ID_ITEM_EFFECT:
				Engine::Window.prefabList.itemCreator.setEffect();
				return 0;
			case ID_ITEM_ATTACHPOINT:
				Engine::Window.prefabList.itemCreator.setAttachmentPoints();
				return 0;
			case ID_ITEMSPRITE_BUTTON:
				Engine::Window.prefabList.itemCreator.setSprite();
				return 0;
			case ID_ITEMICON_BUTTON:
				Engine::Window.prefabList.itemCreator.setInventoryIcon();
				return 0;
			case ID_SET_TEXTURE_PATH:
				Engine::Window.prefabList.itemCreator.setTexturePath();
				return 0;
			case ID_ITEMID_NEXT_VALID_ID:
				Engine::Window.prefabList.itemCreator.setNextValidID();
				return 0;
			case ID_ITEM_CREATE:
			{
				if (Engine::Window.prefabList.itemCreator.createItem())
					SendMessage(hWnd, WM_CLOSE, NULL, NULL);
				return 0;
			}
			default:
				break;
		}
		break;
	}
	case WM_CLOSE:
		ShowWindow(hWnd, FALSE);
		return 0;
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void EngineItemCreator::show()
{
	ShowWindow(hWnd, TRUE);
}

#endif