#ifndef InventoryWindow_HPP
#define InventoryWindow_HPP

#include <SFML\Graphics\Sprite.hpp>
#include "Addon/Button.hpp"
#include "../../../Vector.h"
#include "Addon/ScrollBar.hpp"
#include "BaseWindow.hpp"
#include "../Text/FloatingText.hpp"
#include "../../Item/Bag.hpp"
class EquipmentComponent;
class InventoryComponent;
namespace GUI
{
	namespace Window
	{
		class InventoryWindow : public BaseWindow
		{
		public:

			InventoryWindow(float x1, float y1, int x2, int y2);

			bool bagSlotSelected = false;
			bool createdInventory = false;
			bool updateStats = true;

			Addon::ScrollBar scroll;
			Addon::ScrollBar stats;

			void draw();
			sf::Sprite getEmptyInventorySlotIcon();
		private:

			int iconSize = 32;
			int iconOffset = 5;
			int selectedIndex = 0;
			int bagIndex = 0;

			sf::Sprite emptyInventorySlot;
			Items::Item* item;
			ToolTip toolTip;
			Text::FloatingText gold;
			Text::Message weight;

			bool mouseInsideIcon(sf::Sprite&);

			void drawGold();
			void drawWeight(InventoryComponent* inv);
			void onClose();
			void swap();
	void IcondrawHandle();
			void IconSelectHandle();
			void CreateScrollItems();
			void WindowHandle();
			void drawGearIcons();

			void createStats();

			void ClickOnBagSlot(Items::Bag* bag);
			void swap(sf::Sprite& icon, GameObject* go, EquipmentComponent* equip, std::string armorType);

			bool tryEquipBag(Vector2& off);
		};
	}
}
#endif