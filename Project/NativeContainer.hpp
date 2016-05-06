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
#include "Game\Component\CombatComponenet.hpp"
#include "Game\LoadAndSave\DatabaseIndex.hpp"
#include <SFML\Graphics\Text.hpp>
#include "Game\GUI\Text\Font.hpp"

class NativeContainer
{
public:
	sf::Mutex mutex;

	sf::RenderWindow gameObjectPreviewRender;
	sf::RenderWindow tooltipPreviewRender;
	GUI::ToolTip t;
	NativeContainer(HWND handle);
	~NativeContainer() = default;
	int windowMessage();
	void TestAdd();
	void setTooltipPreviewHandle(HWND handle);
	void setTooltipPreview(std::string a, std::string b);

	void setGameObjectPreviewHandle(HWND handle);
	void setGameObjectRenderPreview(RenderComponent* render);
	void setAnimation(std::string animation);
	void quit();
	void loadZone(unsigned int myZoneID);
	std::pair<std::pair<std::string, size_t>, DBZonePrefabStruct> addGameObjectToZone(std::string modName, size_t ID);

	void lock();
	void unlock();
	void showHideHitboxes();
private:

	GameObject* previewObject = NULL;
	RenderComponent* tmprender = NULL;
	SpriterEngine::EntityInstance* previewEntityInstance = NULL;
	HWND gameObjectPreview;
	HWND tooltipPreview;
	bool creatingTooltip = false;
	bool creatingNewRender = false;
	bool running = true;
	bool drawPreviewRender;

	bool addNewZone = false;
};
#endif
#endif