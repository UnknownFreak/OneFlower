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
NativeContainer::NativeContainer(HWND handle) : t("default")
{
	Engine::Graphic.view.create(handle);
	m = CreateWindowEx(0, "STATIC", "", WS_POPUP | WS_VISIBLE | WS_SYSMENU, 0, 0, 500, 250, NULL, NULL, NULL, NULL);
	rw.create(m);
	rw.setActive(false);
}
void NativeContainer::quit()
{
	running = false;
}
void NativeContainer::setPreviewHandle(HWND handle)
{
	SetParent(m, handle);
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
	go->GetComponent<RenderComponent>()->setAnimation("anime2.png", 32, 32);
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
			Engine::Input.update();

			Engine::game.update();

			Engine::Physics.update();

			Engine::Graphic.Draw();

			//Engine::GUI.Draw();
			Engine::Graphic.view.render.display();

			//LOW: Fix this, By moving it somewhere else? and have it return a constant variable
			Engine::time.restartDelta();
			time.FPS();
		}
		Engine::Graphic.view.render.setActive(false);
		rw.setActive(true);
		while (rw.pollEvent(Engine::event))
		{
			std::cout << "polling event for preview window" << std::endl;
		}
		rw.clear();
		t.draw(rw);
		rw.display();
		rw.setActive(false);
		mutex.unlock();
	}
	DestroyWindow(Engine::Graphic.view.hWnd);
	return 0;
}
#endif