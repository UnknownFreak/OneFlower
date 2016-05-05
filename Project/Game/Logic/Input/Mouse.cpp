#include "Mouse.hpp"
#include "../../../Engine.hpp"
#include "../../Component/HitboxComponent.hpp"
#include "../../Component/RigidComponent.hpp"
#include "../../Component/TransformComponent.hpp"
#include "../../Component/DialogComponent.hpp"
#include "../../Component/CombatComponenet.hpp"
void scrollupdate();
Mouse::Mouse() : pos(0, 0), offset(0, 0), LMBPressed(false), RMBPressed(true)
{
}

void Mouse::update()
{
#ifdef _DEBUG
	sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::Graphic.view.render);
	sf::Vector2f worldPos = Engine::Graphic.view.render.mapPixelToCoords(pixelPos);

	pos.x = worldPos.x;
	pos.y = worldPos.y;
	if (Engine::Graphic.view.render.hasFocus())
	{
#else
	if(Engine::Graphic.view.render.hasFocus())
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::Graphic.view.render);
		sf::Vector2f worldPos = Engine::Graphic.view.render.mapPixelToCoords(pixelPos);

		pos.x = worldPos.x;
		pos.y = worldPos.y;
#endif

		if (Engine::event.type == Engine::event.MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (mySelected)
			{
				TransformComponent* transform = mySelected->GetComponent<TransformComponent>();
				RenderComponent* rc = mySelected->GetComponent<RenderComponent>();
				int localStartX = transform->position.x;
				int localStartY = transform->position.y;
				int localEndX = transform->position.x + rc->sprite.getTextureRect().width;
				int localEndY = transform->position.y + rc->sprite.getTextureRect().height;

				if (pos.x >= localStartX && pos.x <= localEndX || moving)
					if (pos.y >= localStartY && pos.y <= localEndY || moving)
					{
						if (resetDxDy)
						{ 
							moving = true;
							dxDy.x = pos.x - localStartX;
							dxDy.y = pos.y - localStartY;
							resetDxDy = false;
						}
						Engine::World.EditorFlagGameObjectForEdit(mySelected);
						transform->position.x = pos.x - dxDy.x;
						transform->position.y = pos.y - dxDy.y;
					}
					else
						mySelected = NULL;
				else
					mySelected = NULL;
			}
		}
		if (Engine::event.type == Engine::event.MouseButtonPressed)
		{
			if (Engine::event.mouseButton.button == sf::Mouse::Button::Left)
			{
				//Engine::game.player->GetComponent<Component::Combat>()->execute();
			}
		}
		if(Engine::event.type == Engine::event.MouseButtonReleased)
		{
#pragma region Left
			if(Engine::event.mouseButton.button == sf::Mouse::Button::Left)
			{
				resetDxDy = true;
				moving = false;
				if(LMBPressed)
					LMBPressed = false;

				int top = 0;
				if(Engine::GUI.mouseOutsideOpenWindow())
				{
					for(int i = 0; i < Engine::game.allGameObjectPointers.size(); i++)
					{
						RenderComponent* rc = 0;
						GameObject* ab = 0;
						HitboxComponent* hitbox = 0;
						TransformComponent* transform = 0;
						DialogComponent* dialog = 0;
						RigidComponent* rig = 0;
						hitbox = Engine::game.allGameObjectPointers.at(i)->GetComponent<HitboxComponent>();
						transform = Engine::game.allGameObjectPointers.at(i)->GetComponent<TransformComponent>();
						rig = Engine::game.allGameObjectPointers.at(i)->GetComponent<RigidComponent>();
						rc = Engine::game.allGameObjectPointers.at(i)->GetComponent<RenderComponent>();
						ab = Engine::game.allGameObjectPointers.at(i);
						dialog = Engine::game.allGameObjectPointers.at(i)->GetComponent<DialogComponent>();
						if (hitbox || rig || rc)
						{
							if (rc)
							{
								int localStartX = transform->position.x;
								int localStartY = transform->position.y;
								int localEndX = transform->position.x + rc->sprite.getTextureRect().width;
								int localEndY = transform->position.y + rc->sprite.getTextureRect().height;

								if (pos.x >= localStartX && pos.x <= localEndX)
									if (pos.y >= localStartY && pos.y <= localEndY)
									{
										Engine::Graphic.selectedDrawList.push_back(ab);
										if (dialog)
											dialog->show();
									}
							}
						}
						
					}
					if(Engine::Graphic.selectedDrawList.size() > 0)
					{
						for(size_t i = 0; i < Engine::Graphic.selectedDrawList.size(); i++)
						{
							if(Engine::Graphic.selectedDrawList[i]->ReadComponent<RenderComponent>()->renderlayer > Engine::Graphic.selectedDrawList[top]->ReadComponent<RenderComponent>()->renderlayer)
							{
								top = i;
							}
						}
						mySelected = Engine::Graphic.selectedDrawList[top];
						Engine::Graphic.selectedDrawList.clear();
						return;
					}
					else
					{
						mySelected = NULL;
					}
				}
			}
#pragma endregion
#pragma region Right
			/*
			else if(Engine::event.mouseButton.button == sf::Mouse::Button::Right)
			{
			HWND wnd = GetDlgItem(Engine::Window.hWnd,90562);
			HWND awnd = GetDlgItem(Engine::Window.hWnd,90572);

			if (RMBPressed)
			RMBPressed = false;
			HWND wnd = GetDlgItem(Engine::Window.hWnd,90562);
			HWND awnd = GetDlgItem(Engine::Window.hWnd,90572);

			SetWindowTextA(wnd,std::to_string((int)pos.x).c_str());
			SetWindowTextA(awnd,std::to_string((int)pos.y).c_str());
			}
			//*/
#pragma endregion
		}

		if(deltaScrolls < 0)

		{
			if(Engine::GUI.windowHasFocus())
				Engine::GUI.scroll();
			else
			{
				Engine::Graphic.view.camera.zoom(1 + (scrollSpeed*-deltaScrolls));
				Engine::GUI.setGUIScale();
				deltaScrolls = 0;
			}
		}
		else if(deltaScrolls > 0)
		{
			if(Engine::GUI.windowHasFocus())
				Engine::GUI.scroll();
			else
			{
				sf::Vector2f size = Engine::Graphic.view.camera.getSize();
				Engine::Graphic.view.camera.zoom(1 - (scrollSpeed*deltaScrolls));
				Engine::GUI.setGUIScale();
				deltaScrolls = 0;
			}
		}
	}
}

bool Mouse::leftClick()
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !LMBPressed && Engine::time.time("LMBPress",25))
		return (LMBPressed = true);
	return false;
}

bool Mouse::rightClick()
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && !RMBPressed && Engine::time.time("RMBPress",25))
		return (RMBPressed = true);
	return false;
}