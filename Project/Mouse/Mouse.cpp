#include "Mouse.hpp"
#include "../Engine.hpp"
#include "../Component/DialogComponent.hpp"
void scrollUpdate();

Mouse::Mouse(): pos(0,0),offset(0,0)
{
}

void Mouse::update()
{
	if(Engine::View.render.hasFocus())
	{
		if(Engine::event.type == Engine::event.MouseButtonReleased)
		{
#pragma region Left
			if(Engine::event.mouseButton.button == sf::Mouse::Button::Left)
			{
				int top = 0;
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
					if(hitbox || rig || rc)
					{
						sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::View.render);
						sf::Vector2f worldPos = Engine::View.render.mapPixelToCoords(pixelPos);

						pos.x = worldPos.x;
						pos.y = worldPos.y;

						rc = Engine::game.allGameObjectPointers.at(i)->GetComponent<RenderComponent>();
						ab = Engine::game.allGameObjectPointers.at(i);
						dialog = Engine::game.allGameObjectPointers.at(i)->GetComponent<DialogComponent>();

						int localStartX = transform->position.x;
						int localStartY = transform->position.y;
						int localEndX = transform->position.x + rc->sprite.getTextureRect().width;
						int localEndY = transform->position.y + rc->sprite.getTextureRect().height;

						if(pos.x >= localStartX && pos.x <= localEndX)
							if(pos.y >= localStartY && pos.y <= localEndY)
							{
								Engine::Graphic.selectedDrawList.push_back(ab);
								if(dialog)
									dialog->show();
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
					GameObject* theChoosenOne = Engine::Graphic.selectedDrawList[top];
					std::cout << "\nSelected Object: " << theChoosenOne->name << std::endl << "Game Object Position: " << Engine::Graphic.selectedDrawList[top]->GetComponent<TransformComponent>()->position.x << " " << Engine::Graphic.selectedDrawList[top]->GetComponent<TransformComponent>()->position.y;
					Engine::Window.setGameObject(theChoosenOne);
					Engine::Graphic.selectedDrawList.clear();
				}
			}
#pragma endregion
#pragma region Right
			else if(Engine::event.mouseButton.button == sf::Mouse::Button::Right)
			{
				HWND wnd = GetDlgItem(Engine::Window.hWnd,90562);
				HWND awnd = GetDlgItem(Engine::Window.hWnd,90572);

				SetWindowTextA(wnd,std::to_string((int)pos.x).c_str());
				SetWindowTextA(awnd,std::to_string((int)pos.y).c_str());
			}
#pragma endregion
		}

		if(deltaScrolls < 0)
		{
			Engine::View.camera.zoom(1 + (scrollSpeed*-deltaScrolls));
			deltaScrolls = 0;
		}
		else if(deltaScrolls > 0)
		{
			sf::Vector2f size = Engine::View.camera.getSize();
			Engine::View.camera.zoom(1 - (scrollSpeed*deltaScrolls));
			deltaScrolls = 0;
		}
	}
}