
#ifdef _EDITOR_

#include <Windows.h>
#include <string>

#include <SFML\Window\Event.hpp>

#include <Core\Core.hpp>
#include <AssetManager\AssetManagerCore.hpp>
#include <Animations\AnimationCore.hpp>
#include <Graphic\GraphicsCore.hpp>
#include <Input\InputCore.hpp>
#include <Physics\PhysicsCore.hpp>
#include <World\WorldCore.hpp>

#include <Core\Component\GameObject.h>
#include <Graphic\Component\RenderComponent.h>

#include <EditorManager\EditorCore.hpp>

#include <SFML\System\Thread.hpp>
#include <SFML\System\String.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Font.hpp>

#include <Logger\Logger.hpp>

//#include "Engine\Core\Components.hpp"
//#include "Engine\Logic\Time\Time.hpp"
//#include "Game\World\WorldManagement.hpp"
//#include "Game\LoadAndSave\LoadAndSave.hpp"
//
//#include "Game\Animations\SpriterOverride\SFMLObjectFactory.h"
//#include "Game\Animations\SpriterOverride\SFMLFileFactory.h"
//
//#include "Game\Animations\SpriterEngine\spriterengine.h"
//
//#include "Game\Animations\SpriterEntityInstance.hpp"
//#include "Game\Animations\SpriterModelContainer.hpp"

//#include "Game\World\Zone.hpp"
//#include "Engine\GUI\Text\FormatedText.hpp"
int windowMessage();
void RunMain();
int test();
void update();
void mainMenuUpdate();
void renderThread();

Core::StringConverter Core::Converter;
Settings::EngineSettings Engine::Settings;
Gfx Engine::Graphic;
TextureLoader Engine::Textureloader;
sf::Event Engine::event;
//Game Engine::game;
Time Engine::time;
PhysicsEngine Engine::Physics;
InputHandler Engine::Input;
WorldManager Engine::World;
SpriterModelContainer Engine::ModelContainer;
WorldManagerAddon Editor::addons;

// temp test stuff
//int a = 24;
//int b = 42;
//GUI::FormatedText t(*Engine::Graphic.font.requestFont("arial.ttf"), "752åäö {0}foobar\nwee blöblöblöb wee\nstuff{1}asddf{1}QQ {2}ListEnd\nCompare " + std::to_string(a) + "(old), " + std::to_string(b) + "(new): {3}", { ParseArg::BaseParseArgument::startList(), ParseArg::BaseParseArgument::newListLine(), ParseArg::BaseParseArgument::endList(), ParseArg::BaseParseArgument::IntCompareArgument(a, b) });
[System::STAThread]
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmnLine, int nShowCmd)
{
	Logger::initialize();
	//Engine::Window.hInstance = hInstance;
	!_DEBUG ? test() : windowMessage();
	//return 0;
	Logger::free();
	exit(0); 
}
int windowMessage()
{
	SplashScreen^ splash = gcnew SplashScreen();
	MainEditorWindow^ window = splash->InitializeEditor();
	Engine::Graphic.view.render.setActive(false);

	sf::Thread thread(&renderThread);
	thread.launch();

	//Engine::Graphic.view.render.setVisible(true);
	//testSave();
	//testLoad();
	//Engine::World.loadMod("Oneflower.main.test");
	//Engine::World.loadZone("Demo.main", 1);
	//Engine::World.loadZone("<__CORE__>", 1);

	GameObject* go = new GameObject("player");
	//go->AddComponent<ProjectilePatternComponent>();
	//go->AddComponent<Component::RenderComponent>("PlayerDemo.png");
	//go->GetComponent<RenderComponent>()->animation = RenderComponent::Armature;
	//Component::RenderComponent* render = go->GetComponent<Component::RenderComponent>();
	//go->GetComponent<RenderComponent>()->instance = Engine::ModelContainer.requestEntityInstance("Spriter\\player.scml", "Player");
	//go->GetComponent<RenderComponent>()->instance.myTextureMap = { "Demo.main", "DemoTest" };
	//go->GetComponent<RenderComponent>()->setAnimation("anime2.png", 32, 32);
	//go->AddComponent<Component::RigidComponent>();
	//go->GetComponent<Component::RigidComponent>()->bounding.size = Vector2i(32, 32);
	//go->GetComponent<Component::TransformComponent>()->position.x = 300;
	//go->GetComponent<Component::TransformComponent>()->position.y = 300;
	//go->AddComponent<Component::EquipmentComponent>();
	//go->AddComponent<Component::PlayerComponent>();
	//go->AddComponent<Component::Combat>();
	//Engine::game.addGameObject(go);
	//Engine::game.player = go;

	//testSave();
	//Loads the mods required for the "editor", not required for release mode.
	//Engine::World.loadMod("OneFlower.main");
	//Engine::World.loadZone("OneFlower.main",1);
	/*
	GameObject* go = new GameObject("player");
	//go->AddComponent<ProjectilePatternComponent>();
	go->AddComponent<RenderComponent>("testTarget.png");
	go->GetComponent<RenderComponent>()->animation = RenderComponent::SpriteSheet;
	SpriteSheetAnimation anim;
	anim.AnimationTime = 1.0;
	anim.looping = true;
	anim.AnimationFrames.push_back(sf::IntRect(0, 0, 16, 16));
	anim.AnimationFrames.push_back(sf::IntRect(16, 0, 16, 16));
	anim.AnimationFrames.push_back(sf::IntRect(0, 16, 16, 16));
	anim.AnimationFrames.push_back(sf::IntRect(16, 16, 16, 16));
	anim.AnimationFrames.push_back(sf::IntRect(0, 32, 16, 16));
	anim.AnimationFrames.push_back(sf::IntRect(16, 32, 16, 16));
	go->GetComponent<RenderComponent>()->animations.insert(std::pair<std::string,SpriteSheetAnimation>("Default",anim));

	go->AddComponent<RigidComponent>();
	go->GetComponent<TransformComponent>()->position.x = 300;
	go->AddComponent<PlayerComponent>();
	go->AddComponent<EquipmentComponent>();
	go->AddComponent<Component::Combat>();
	sf::Color c(1,0,0,1);
	sf::Sprite sp = go->GetComponent<RenderComponent>()->sprite;
	Engine::game.player = go;
	//*/
	//else
	//Engine::Graphic.insertShader(shader,"test.glsl");
	//Engine::GUI.showHideGUI();
	//Engine::game.addGameObject(go);
	Time time;
	Engine::Graphic.view.render.setFramerateLimit(200);
	//Engine::Window.debug.print("Test",__LINE__,__FILE__);
	MSG message;
	while (GetMessage(&message, NULL, 0, 0) && !window->isClosed())
	{
	//while (Engine::Graphic.view.render.isOpen())
	//{
		
		TranslateMessage(&message);
		DispatchMessage(&message);
		while (Engine::Graphic.view.render.pollEvent(Engine::event))
		{
			if (Engine::event.type == sf::Event::Closed)
			{
				Engine::Graphic.view.render.close();
			}
			if (Engine::event.type == Engine::event.MouseWheelMoved)
				Engine::Input.mouse.deltaScrolls += Engine::event.mouseWheel.delta;
			/*
			std::cout << "alt:" << event.key.alt << std::endl;
			std::cout << "shift:" << event.key.shift << std::endl;
			std::cout << "system:" << event.key.system << std::endl;
			//*/
		}
		//if (Engine::World.getIsLoading())
		//{
		//	Engine::World.loadSome();
		//	Engine::World.drawLoadingScreen();
		//}
		//else
		//{
		//	update();
		//}
	}
	thread.terminate();
	thread.wait();
	Core::Converter.free();
	delete splash;
	delete window;
	delete go;
	return 1;
}

void renderThread()
{
	Engine::Graphic.view.render.setActive(true);
	while (Engine::Graphic.view.render.isOpen())
	{
		if (Engine::World.getIsLoading())
		{
			Engine::World.loadSome();
			Engine::World.drawLoadingScreen();
		}
		else
		{
			update();
		}
	}
}

void mainMenuUpdate()
{
	Engine::time.elapsed += Engine::time.clock.restart();

	while (Engine::time.elapsed >= Engine::time.update_ms)
	{
		Engine::Input.update();
		//Engine::GUI.updateMouseIcon();
		Engine::time.elapsed -= Engine::time.update_ms;
	}

	Engine::Graphic.drawBG();
	Engine::Graphic.view.render.display();
}
void update()
{
	Engine::time.elapsed += Engine::time.clock.restart();

	while (Engine::time.elapsed >= Engine::time.update_ms)
	{
		Engine::Input.update();
		//Engine::Physics.update();
		//Engine::game.update();

		Engine::time.elapsed -= Engine::time.update_ms;
	}

	Engine::Graphic.draw();
	//Engine::GUI.draw();
	Engine::Graphic.view.render.display();
}
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>
int test()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	// Load a sprite to display
	sf::Texture texture;
	if (!texture.loadFromFile("test.png"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);
	// Create a graphical text to display
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		return EXIT_FAILURE;
	sf::Text text("Hello SFML", font, 50);
	sf::Text text2("HellNoFucs", font, 50);
	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Clear screen
		window.clear();
		// Draw the sprite
		window.draw(sprite);
		// Draw the string
		//	window.hasFocus() ? window.draw(text) : window.draw(text2);
		// update the window
		window.display();
	}
	return EXIT_SUCCESS;
}
#endif
