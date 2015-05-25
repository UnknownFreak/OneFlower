#ifndef GraphicalInventory_HPP
#define GraphicalInventory_HPP

#include <SFML\Graphics\Sprite.hpp>
#include "Button.hpp"
#include "../Vector.h"
#include "ScrollBar.hpp"
#include "BaseWindow.hpp"
#include "../Text/FloatingText.hpp"
class Bag;
class Item;

class GraphicalInventory : public BaseWindow
{
public:

	GraphicalInventory(int x1, int y1, int x2, int y2);

	bool bagSlotSelected = false;
	bool createdInventory = false;

	ScrollBar scroll;

	void draw();

private:

	int iconSize = 32;
	int iconOffset = 5;
	int selectedIndex = 0;
	int bagIndex = 0;


	sf::Sprite emptyInventorySlot;
	Item* item;
	ToolTip toolTip;
	FloatingText gold;

	bool mouseInsideIcon(sf::Sprite&);
	
	void onClose();
	void swap();
	void IconDrawHandle();
	void IconSelectHandle();
	void CreateScrollItems();
	void WindowHandle();
	void ClickOnBagSlot(Bag* bag);
	
	bool tryEquipBag(Vector2& off);
};

#endif