#ifdef _EDITOR_
// This file does not actually work as of now. Need to replace and rewrite some of the code to get the editor to work again
#include <Windows.h>
#include <string>
#include "..\Engine.hpp"
#include "..\Game\Component\GameObject.h"
#include "..\Game\Component\HitboxComponent.hpp"
#include "..\Game\Component\RenderComponent.h"
#include "..\Game\Component\TransformComponent.hpp"
#include "..\Game\Component\DialogComponent.hpp"
#include "..\Game\Component\ProjectilePatternComponent.hpp"
#include "..\Game\Component\EquipmentComponent.hpp"
#include "..\Game\Component\PlayerComponent.hpp"
#include "..\Game\Component\CombatComponenet.hpp"
#include "..\Game\Component\RigidComponent.hpp"
#include "..\Engine\Logic\Time\Time.hpp"
//#include "..\Game\World\WorldManagement.hpp"
#include "..\Game\LoadAndSave\LoadAndSave.hpp"

#include "..\Game\Animations\SpriterOverride\SFMLObjectFactory.h"
#include "..\Game\Animations\SpriterOverride\SFMLFileFactory.h"

#include "..\Game\Animations\SpriterEngine\spriterengine.h"

#include "..\Game\Animations\SpriterEntityInstance.hpp"
#include "..\Game\Animations\SpriterModelContainer.hpp"

#include "..\Engine\GUI\Text\FormatedText.hpp"
#include "..\Engine\GUI\GUIElement\BaseHandler.hpp"

#include "SplashScreen.hpp"

int windowMessage();

void update();
void mainMenuUpdate();
Gfx Engine::Graphic;
sf::Event Engine::event;
Game Engine::game;
Time Engine::time;
PhysicsEngine Engine::Physics;
InputHandler Engine::Input;
WorldManagement Engine::World;
SpriterModelContainer Engine::ModelContainer;
Settings Engine::settings;
// temp test stuff
int a = 24;
int b = 42;
GUI::FormatedText t(*Engine::Graphic.font.requestFont("arial.ttf"), "752åäö {0}foobar\nwee blöblöblöb wee\nstuff{1}asddf{1}QQ {2}ListEnd\nCompare " + std::to_string(a) + "(old), " + std::to_string(b) + "(new): {3}", { ParseArg::BaseParseArgument::startList(), ParseArg::BaseParseArgument::newListLine(), ParseArg::BaseParseArgument::endList(), ParseArg::BaseParseArgument::IntCompareArgument(a, b) });
[System::STAThread]
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmnLine, int nShowCmd)
{
	//Engine::Window.hInstance = hInstance;
	windowMessage();
	return 0;
}
int windowMessage()
{
	SplashScreen splsh(Engine::Graphic.view.render.getSystemHandle());
	splsh.InitializeEditor();
	GUI::BaseHandler::registerCallbacks();
	Engine::World.loadZone("Demo.main", 1);
	Engine::World.loadZone("MainMenu", 0);
	//shape.setFillColor(sf::Color(0, 150, 0, 100));
	//shape.setOutlineThickness(2.f);
	//shape.setOutlineColor(sf::Color(0, 220, 0));
	//shape.setSize(sf::Vector2f(0, 0));
	//TestAdd();
	//Engine::GUI.showHideGUI();
	////testSave();
	//sf::Color c(1, 0, 0, 1);
	////else
	////Engine::Graphic.insertShader(shader,"test.glsl");
	//Engine::GUI.showHideGUI();
	//Time time;
	Engine::Graphic.view.render.setFramerateLimit(200);
	//Engine::Graphic.rex.create(800, 600);

	Engine::Graphic.view.render.setActive(true);

	while (Engine::Graphic.view.render.isOpen())
	{
		//mutex.lock();

		// if exception thrown here, have yet to find fix for deque error (Editor Only)
		while (Engine::Graphic.view.render.pollEvent(Engine::event))
		{
			if (Engine::event.type == sf::Event::Closed)
			{
				Engine::Graphic.view.render.close();
			}
			if (Engine::event.type == Engine::event.MouseWheelMoved)
				Engine::Input.mouse.deltaScrolls += Engine::event.mouseWheel.delta;
		}

		if (Engine::World.getIsLoading())
		{
			Engine::World.loadSome();
			Engine::World.drawLoadingScreen();
		}
		else
		{
			//if (Engine::World.getCurrentZone()->ID == 0 && Engine::World.getCurrentZone()->modOrigin == "MainMenu")
			//	mainMenuUpdate();
			//else
			update();
		}
		//Engine::Graphic.view.render.setActive(false);
		//tooltipPreviewRender.setActive(true);
		//while (tooltipPreviewRender.pollEvent(Engine::event))
		//{
		//}
		//tooltipPreviewRender.clear();
		//t.draw(tooltipPreviewRender);
		//tooltipPreviewRender.display();
		//tooltipPreviewRender.setActive(false);
		//
		//gameObjectPreviewRender.setActive(true);
		//while (gameObjectPreviewRender.pollEvent(Engine::event))
		//{
		//}
		//gameObjectPreviewRender.clear();
		//if (previewObject)
		//{
		//	RenderComponent* render = previewObject->GetComponent<RenderComponent>();
		//	HitboxComponent* hitbox = previewObject->GetComponent<HitboxComponent>();
		//	Vector2 pos(previewObject->GetComponent<TransformComponent>()->position);
		//	if (render && drawPreviewRender)
		//	{
		//	#pragma region render
		//		if (tmprender)
		//		{
		//			render->animation = tmprender->animation;
		//			render->sprite.setTexture(*Engine::Graphic.requestTexture(tmprender->textureName),true);
		//			render->textureName = tmprender->textureName;
		//			render->animations = tmprender->animations;
		//			render->instance = tmprender->instance;
		//			if (tmprender->instance.entityName != "")
		//			{
		//				if (render->instance.MyEntityInstance)
		//					delete render->instance.MyEntityInstance;
		//				render->instance = Engine::ModelContainer.requestEntityInstance(tmprender->instance.sceneFile, tmprender->instance.entityName);
		//				render->instance.myTextureMap = tmprender->instance.myTextureMap;
		//				previewEntityInstance = render->instance.MyEntityInstance;
		//			}
		//			else
		//				previewEntityInstance = NULL;
		//			render->outline = tmprender->outline;
		//			delete tmprender;
		//			tmprender = 0;
		//		}
		//		switch (render->animation)
		//		{
		//			case RenderComponent::AnimationType::SpriteSheet:
		//				render->updateFrame();
		//			case RenderComponent::AnimationType::Static:
		//				render->sprite.setPosition(pos.x,pos.y);
		//				gameObjectPreviewRender.draw(render->sprite);
		//				break;
		//			case RenderComponent::AnimationType::Armature:
		//			{
		//				if (render->instance.MyEntityInstance && render->instance.textureMaps)
		//				{
		//					render->instance.MyEntityInstance->setTimeElapsed(Engine::time.update_ms.asSeconds()*500);
		//					render->instance.MyEntityInstance->setPosition(SpriterEngine::point(pos.x, pos.y));
		//					render->instance.textureMaps->renderWindow = &gameObjectPreviewRender;
		//					render->instance.render(&render->sprite);
		//					if(previewEntityInstance->animationJustFinished())
		//					{
		//						previewEntityInstance->setCurrentTime(0);
		//					}
		//				}
		//				break;
		//			}
		//			default:
		//				break;
		//		}
		//	#pragma endregion
		//	}
		//	if (hitbox && drawPreviewHitbox)
		//	{
		//		if (tmpHitbox)
		//		{
		//			hitbox->bounding = tmpHitbox->bounding;
		//			delete tmpHitbox;
		//			tmpHitbox = 0;
		//		}
		//
		//		shape.setSize(sf::Vector2f(hitbox->bounding.size.x,hitbox->bounding.size.y));
		//		shape.setPosition(pos.x + hitbox->bounding.position.x, pos.y + hitbox->bounding.position.y);
		//		gameObjectPreviewRender.draw(shape);
		//	}
		//}
		//gameObjectPreviewRender.display();
		//gameObjectPreviewRender.setActive(false);

		//mutex.unlock();
	}
	//DestroyWindow(Engine::Graphic.view.hWnd);
	//DestroyWindow(tooltipPreview);
	//DestroyWindow(gameObjectPreview);
	return 0;
}

void update()
{
	Engine::time.elapsed += Engine::time.clock.restart();

	while (Engine::time.elapsed >= Engine::time.update_ms)
	{
		Engine::Input.update();
		//Engine::Physics.update();
		Engine::game.update();

		Engine::time.elapsed -= Engine::time.update_ms;
	}

	Engine::Graphic.draw();
	Engine::Graphic.view.render.draw(t);
	//Engine::GUI.draw();
	Engine::Graphic.view.render.display();
}

#endif