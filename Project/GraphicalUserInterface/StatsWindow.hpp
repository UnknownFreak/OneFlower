#ifndef StatsWindow_HPP
#define StatsWindow_HPP
#include "BaseWindow.hpp"
#include "ScrollBar.hpp"

class GameObject;
class EquipmentComponent;
class StatsWindow : public BaseWindow
{
public:

	bool updateStats = true;
	bool updateEquipment = true;
	ScrollBar stats;
	ScrollBar items;
	StatsWindow(float x, float y, int sizeX, int SizeY);

	void draw();
	void WindowHandle();
	void drawGearIcons();
private:
	
	ToolTip toolTip;

	sf::Sprite noEquippedItemIcon;

	void createStats();
	void createEquipmentList();
	void IconSelectHandle();

	void swap(sf::Sprite& icon, GameObject* go, EquipmentComponent* equip, std::string armorType);

	bool mouseInsideIcon(sf::Sprite& sprite);
};


#endif