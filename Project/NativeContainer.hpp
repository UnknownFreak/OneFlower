#ifndef NativeContainer_HPP
#define NativeContainer_HPP
#ifdef _EDITOR_
#include "Engine.hpp"
#include "Game\GUI\ToolTip.hpp"
#include "Game\GUI\Text\FloatingText.hpp"
#include "Game\GUI\Text\Message.hpp"
#include "Game\Component\GameObject.h"
#include "Game\Component\HitboxComponent.hpp"
#include "Game\Component\RenderComponent.h"
#include "Game\Component\TransformComponent.hpp"
#include "Game\Component\DialogComponent.hpp"
#include "Game\Component\ProjectilePatternComponent.hpp"
#include "Game\Component\EquipmentComponent.hpp"
#include "Game\Component\PlayerComponent.hpp"
#include "Game\Component\RigidComponent.hpp"
#include "Game\LoadAndSave\DatabaseIndex.hpp"
#include <SFML\Graphics\Text.hpp>
#include "Game\GUI\Text\Font.hpp"

class NativeContainer
{
public:
	sf::RenderWindow rw;
	GUI::ToolTip t;
	NativeContainer(HWND handle);
	~NativeContainer() = default;
	int windowMessage();
	void TestAdd();
	void setPreviewHandle(HWND handle);
	void setTooltipPreview(std::string a, std::string b);
	void quit();
	void loadZone(unsigned int myZoneID);
	std::pair<std::pair<std::string, size_t>, DBZonePrefabStruct> addGameObjectToZone(std::string modName, size_t ID);
private:
	HWND m;
	bool creatingTooltip = false;
	bool running = true;

};
#endif
#endif