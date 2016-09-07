#ifdef _EDITOR_
#include "NativeContainer.hpp"
#include "Game\Component\InventoryComponent.hpp"
#include "Game\World\Zone.hpp"
#include "Game\GUI\MainMenu\MainMenu.hpp"
Gfx Engine::Graphic;
sf::Event Engine::event;
Game Engine::game;
Time Engine::time;
PhysicsEngine Engine::Physics;
InputHandler Engine::Input;
GUI::GraphicalUserInterface Engine::GUI;
WorldManagement Engine::World;
SpriterModelContainer Engine::ModelContainer;
Settings Engine::settings;

#include "Engine\GUI\Window\Window.hpp"

GUI::Window wndTest;

NativeContainer::NativeContainer(HWND handle) : t("default")
{
	Engine::Graphic.view.create(handle);
	tooltipPreview = CreateWindowEx(0, "STATIC", "", WS_POPUP | WS_VISIBLE | WS_SYSMENU, 0, 0, 500, 250, NULL, NULL, NULL, NULL);
	tooltipPreviewRender.create(tooltipPreview);
	tooltipPreviewRender.setActive(false);

	gameObjectPreview = CreateWindowEx(0, "STATIC", "", WS_POPUP | WS_VISIBLE | WS_SYSMENU, 0, 0, 512, 512, NULL, NULL, NULL, NULL);
	gameObjectPreviewRender.create(gameObjectPreview);
	gameObjectPreviewRender.setActive(false);
}
void mainMenuUpdate()
{
	Engine::time.elapsed += Engine::time.clock.restart();
	
	while (Engine::time.elapsed >= Engine::time.update_ms)
	{
		Engine::Input.mouse.update();
		Engine::GUI.updateMouseIcon();
		Engine::time.elapsed -= Engine::time.update_ms;
	}
	
	Engine::Graphic.drawBG();
	Engine::Graphic.view.render.draw(wndTest);
	Engine::Graphic.view.render.display();

}
void NativeContainer::quit()
{
	running = false;
}
void NativeContainer::setTooltipPreviewHandle(HWND handle)
{
	SetParent(tooltipPreview, handle);
}
void NativeContainer::setGameObjectPreviewHandle(HWND handle)
{
	SetParent(gameObjectPreview, handle);
}
void NativeContainer::setGameObjectRenderPreview(RenderComponent* inputrender)
{
	if (!inputrender)
		drawPreviewRender = false;
	else
		drawPreviewRender = true;
	if (!previewObject)
	{
		previewObject = new GameObject();
		previewObject->GetComponent<TransformComponent>()->position.x = 200;
		previewObject->GetComponent<TransformComponent>()->position.y = 400;
	}
	if (previewObject->GetComponent<RenderComponent>())
	{
		if (!creatingNewRender)
		{
			creatingNewRender = true;
			tmprender = inputrender;
			creatingNewRender = false;
		}
		else
			delete inputrender;
	}
	else
	{
		if (inputrender)
		{
			previewObject->AddComponent(inputrender);
			Engine::Graphic.removeFromdrawList(previewObject);
		}
	}
}
void NativeContainer::setGameObjectHitboxPreview(HitboxComponent* inputhitbox)
{
	if (!inputhitbox)
		drawPreviewHitbox = false;
	else
		drawPreviewHitbox = true;
	if (!previewObject)
	{
		previewObject = new GameObject();
		previewObject->GetComponent<TransformComponent>()->position.x = 200;
		previewObject->GetComponent<TransformComponent>()->position.y = 400;
	}
	if (previewObject->GetComponent<HitboxComponent>())
	{
		if (!creatingNewRender)
		{
			creatingNewRender = true;
			tmpHitbox = inputhitbox;
			creatingNewRender = false;
		}
		else
			delete inputhitbox;
	}
	else
	{
		if (inputhitbox)
		{
			previewObject->AddComponent(inputhitbox);
			Engine::game.removePhysics(inputhitbox);
		}
	}
}
void NativeContainer::setTooltipPreview(std::string a, std::string b)
{
	if (!creatingTooltip)
	{
		creatingTooltip = true;
		t.setToolTipText(a, b);
		creatingTooltip = false;
	}
}
std::pair<std::pair<std::string, size_t>, DBZonePrefabStruct> NativeContainer::addGameObjectToZone(std::string modName, size_t ID)
{
	auto var = Engine::World.editorPrefabContainer.getMap();
	auto prefab = var.find(std::pair<std::string, size_t>(modName, ID));
	std::cout << prefab->second.name << " " << prefab->second.ID;
	GameObject* go = prefab->second.createFromPrefab();
	Engine::game.addGameObject(go);
	go->GetComponent<TransformComponent>()->position = Engine::Input.mouse.pos;
	return Engine::World.EditorAddGameObjectToZone(prefab->second, go);
}
void NativeContainer::loadZone(unsigned int myZoneID)
{
	Engine::World.loadZone(Engine::World.openedMod, myZoneID);
}
void NativeContainer::TestAdd()
{
	GameObject& go = Engine::game.addGameObject();
	//go->AddComponent<ProjectilePatternComponent>();
	go.AddComponent<RenderComponent>("PlayerDemo.png");
	go.GetComponent<RenderComponent>()->animation = RenderComponent::Armature;
	RenderComponent* render = go.GetComponent<RenderComponent>();
	go.GetComponent<RenderComponent>()->instance = Engine::ModelContainer.requestEntityInstance("Spriter\\player.scml", "Player");
	go.GetComponent<RenderComponent>()->instance.myTextureMap = { "Demo.main", "DemoTest" };
	go.AddComponent<InventoryComponent>();
	//go->GetComponent<RenderComponent>()->setAnimation("anime2.png", 32, 32);
	go.AddComponent<RigidComponent>();
	go.GetComponent<RigidComponent>()->bounding.size = Vector2(32, 32);
	go.GetComponent<TransformComponent>()->position.x = 300;
	go.GetComponent<TransformComponent>()->position.y = 300;
	go.AddComponent<EquipmentComponent>();
	go.AddComponent<PlayerComponent>();
	go.AddComponent<Component::Combat>();
	
	//Engine::game.player = &go;
}
//temp test
void NativeContainer::lock()
{
	mutex.lock();
}
void NativeContainer::unlock()
{
	mutex.unlock();
}
void NativeContainer::setAnimation(std::string animation)
{
	if (previewEntityInstance)
	{
		previewEntityInstance->setCurrentAnimation(animation);
		previewEntityInstance->setCurrentTime(0);
	}
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
	Engine::GUI.draw();
	Engine::Graphic.view.render.draw(wndTest);
	Engine::Graphic.view.render.display();

}
void NativeContainer::showHideHitboxes()
{
	Engine::Graphic.drawHitboxes = !Engine::Graphic.drawHitboxes;
}
int NativeContainer::windowMessage()
{
	Engine::World.loadZone("Demo.main", 1);

	shape.setFillColor(sf::Color(0, 150, 0, 100));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(sf::Color(0, 220, 0));
	shape.setSize(sf::Vector2f(0, 0));
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

	while (running)
	{
		//mutex.lock();
		try
		{
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
		}
		catch (...)
		{
			std::cout << "error while polling event" << std::endl;
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
	DestroyWindow(Engine::Graphic.view.hWnd);
	DestroyWindow(tooltipPreview);
	DestroyWindow(gameObjectPreview);
	return 0;
}
#endif