#ifdef _EDITOR_
#include "NativeContainer.hpp"
Gfx Engine::Graphic;
sf::Event Engine::event;
Game Engine::game;
Time Engine::time;
PhysicsEngine Engine::Physics;
InputHandler Engine::Input;
GUI::GraphicalUserInterface Engine::GUI;
WorldManagement Engine::World;
SpriterModelContainer Engine::ModelContainer;
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
		previewObject->AddComponent(inputrender);
		Engine::Graphic.removeFromdrawList(previewObject);
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
	GameObject* go = new GameObject("player");
	//go->AddComponent<ProjectilePatternComponent>();
	go->AddComponent<RenderComponent>("testTarget.png");
	//go->GetComponent<RenderComponent>()->setAnimation("anime2.png", 32, 32);
	go->AddComponent<RigidComponent>();
	go->GetComponent<RigidComponent>()->bounding.size = Vector2(32,32);
	go->GetComponent<TransformComponent>()->position.x = 300;
	go->GetComponent<TransformComponent>()->position.y = 300;
	go->AddComponent<EquipmentComponent>();
	go->AddComponent<Component::Combat>();
	Engine::game.addGameObject(go);
	Engine::game.player = go;
}
//temp test
void NativeContainer::lock()
{
	std::cout << "locking" << std::endl;
	mutex.lock();
	std::cout << "locking Done" << std::endl;
}
void NativeContainer::unlock()
{
	std::cout << "unlocking" << std::endl;
	mutex.unlock();
	std::cout << "unlocking Done" << std::endl;
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
	Engine::Graphic.view.render.display();

}
int NativeContainer::windowMessage()
{
	TestAdd();
	MSG message;
	ZeroMemory(&message, sizeof(MSG));
	//testSave();
	sf::Color c(1, 0, 0, 1);
	//else
	//Engine::Graphic.insertShader(shader,"test.glsl");
	Engine::GUI.showHideGUI();
	Time time;
	Engine::Graphic.view.render.setFramerateLimit(200);
	Engine::Graphic.rex.create(800, 600);
	//Engine::Window.debug.print("Test",__LINE__,__FILE__);
	while (running)
	{
//		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
//		{
//			if (message.message == WM_KEYDOWN)
//			{
//				if (message.wParam == VK_ESCAPE)
//					std::cout << "\nEsc";//SetFocus(Engine::Window.hWnd);
//				if (message.wParam == VK_DELETE)
//				{
//#ifdef _DEBUG
//					//Engine::World.RemoveGameObjectFromZone(Engine::Window.focus.gameObject);
//					//Engine::game.requestRemoveal(Engine::Window.focus.gameObject);
//#endif
//				}
//				if (message.wParam == VK_OEM_PLUS)
//					Engine::Input.mouse.deltaScrolls += 5;
//				if (message.wParam == VK_OEM_MINUS)
//					Engine::Input.mouse.deltaScrolls -= 5;
//			}
//			// If a message was waiting in the message queue, process it
//			TranslateMessage(&message);
//			DispatchMessage(&message);
//		}
		//*/
		mutex.lock();
		Engine::Graphic.view.render.setActive(true);
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
			update();
		}
		Engine::Graphic.view.render.setActive(false);
		tooltipPreviewRender.setActive(true);
		while (tooltipPreviewRender.pollEvent(Engine::event))
		{
		}
		tooltipPreviewRender.clear();
		t.draw(tooltipPreviewRender);
		tooltipPreviewRender.display();
		tooltipPreviewRender.setActive(false);

		gameObjectPreviewRender.setActive(true);
		while (gameObjectPreviewRender.pollEvent(Engine::event))
		{
		}
		gameObjectPreviewRender.clear();
		if (previewObject)
		{
			RenderComponent* render = previewObject->GetComponent<RenderComponent>();
			if (render)
			{
				if (tmprender)
				{
					render->animation = tmprender->animation;
					render->sprite.setTexture(*Engine::Graphic.requestTexture(tmprender->textureName),true);
					render->textureName = tmprender->textureName;
					std::cout << "tex name: " << render->textureName << std::endl;
					render->animations = tmprender->animations;
					render->instance = tmprender->instance;
					if (tmprender->instance.entityName != "")
					{
						if (render->instance.MyEntityInstance)
							delete render->instance.MyEntityInstance;
						std::cout << tmprender->instance.sceneFile;
						render->instance = Engine::ModelContainer.requestEntityInstance(tmprender->instance.sceneFile, tmprender->instance.entityName);
						render->instance.sceneFile = tmprender->instance.sceneFile;
						render->instance.entityName = tmprender->instance.entityName;
						render->instance.myTextureMap = tmprender->instance.myTextureMap;
						previewEntityInstance = render->instance.MyEntityInstance;
					}
					else
						previewEntityInstance = NULL;
					render->outline = tmprender->outline;
					delete tmprender;
					tmprender = 0;
				}
				switch (render->animation)
				{
				case RenderComponent::AnimationType::SpriteSheet:
					render->updateFrame();
				case RenderComponent::AnimationType::Static:
					gameObjectPreviewRender.draw(render->sprite);
					break;
				case RenderComponent::AnimationType::Armature:
				{
					if (render->instance.MyEntityInstance && render->instance.textureMaps)
					{
						Vector2 pos(previewObject->GetComponent<TransformComponent>()->position);
						render->instance.MyEntityInstance->setTimeElapsed(Engine::time.deltaTime() * 1000);
						render->instance.MyEntityInstance->setPosition(SpriterEngine::point(pos.x, pos.y));
						render->instance.textureMaps->renderWindow = &gameObjectPreviewRender;
						render->instance.render(&render->sprite);
						if(previewEntityInstance->animationJustFinished())
						{
							previewEntityInstance->setCurrentTime(0);
						}
					}
					break;
				}
				default:
					break;
				}
			}
		}
		gameObjectPreviewRender.display();
		gameObjectPreviewRender.setActive(false);

		mutex.unlock();
	}
	DestroyWindow(Engine::Graphic.view.hWnd);
	DestroyWindow(tooltipPreview);
	DestroyWindow(gameObjectPreview);
	return 0;
}
#endif