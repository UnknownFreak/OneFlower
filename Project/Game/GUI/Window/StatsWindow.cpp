#include "StatsWindow.hpp"
#include "../../../Engine.hpp"
#include "../Window/Addon/WindowIcon.hpp"
#include "../../Component/StatsComponent.hpp"
#include "../../Component/EquipmentComponent.hpp"
#include "../../Component/InventoryComponent.hpp"
#include "../../Item/Armor.hpp"
#include "../../Item/Bag.hpp"

namespace GUI
{
	namespace Window
	{
		StatsWindow::StatsWindow(float x, float y, int sizeX, int sizeY) : BaseWindow(x, y, sizeX, sizeY, false, "Equipment"), stats(x - 64, y + 32, 64, 32, Vector2(16, 16), Vector2(64, 5), this, false), noEquippedItemIcon(*Engine::Graphic.requestTexture("InventoryEmptyIcon.png")), items(0, 0, 64, 32, Vector2(32, 32), Vector2(5, 5), this, true), toolTip("None")
		{
		}

		void StatsWindow::draw()
		{
			if (open)
			{
				if (updateStats)
					createStats();
				if (updateEquipment)
					createEquipmentList();
				move();
				WindowHandle();
				BaseWindow::draw();
				drawGearIcons();
				stats.draw();
				items.draw();
				//IconSelectHandle();
				if (items.tooltip.first && !items.movingItem && Engine::GUI.showToolTip && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == (BaseWindow*)this ||
					items.tooltip.first && !items.movingItem && Engine::GUI.showToolTip && !Engine::GUI.focusedWindow->checkMouseInside())
					if (items.mouseInsideIcon(*items.tooltip.first) && items.tooltip.second.getToolTipBody() != "")
					{
						Engine::GUI.openedWindowToolTip.setToolTipText(items.tooltip.second.getToolTipTitle(), items.tooltip.second.getToolTipBody());
						Engine::GUI.drawOpenedWindowToolTip = true;
					}
					else if (stats.tooltip.first && !stats.movingItem && Engine::GUI.showToolTip && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == (BaseWindow*)this ||
						stats.tooltip.first && !stats.movingItem && Engine::GUI.showToolTip  && !Engine::GUI.focusedWindow->checkMouseInside())
						if (items.mouseInsideIcon(*stats.tooltip.first) && stats.tooltip.second.getToolTipBody() != "")
						{
							Engine::GUI.openedWindowToolTip.setToolTipText(stats.tooltip.second.getToolTipTitle(), stats.tooltip.second.getToolTipBody());
							Engine::GUI.drawOpenedWindowToolTip = true;
						}
			}
		}
		void StatsWindow::WindowHandle()
		{
			stats.setPosition(position.x + 340 + offsetX, position.y + 64 + offsetY);
			stats.setSizeY(256);
			stats.setSizeX(136);

			items.setPosition(position.x - 32 + offsetX, position.y + 64 + offsetY);
			items.setSizeY(300);
			items.setSizeX(180);
			BaseWindow::WindowHandle();
		}
		void StatsWindow::createStats()
		{
			for (std::vector<BaseWindowObject*>::iterator it = stats.sprites.begin(); it != stats.sprites.end(); it++)
			{
				delete *it;
				*it = NULL;
			}
			stats.sprites.clear();
			//TODO: REWORK THIS
			GameObject* go = NULL;// Engine::Window.focus.gameObject;
			if (go)
			{
				StatsComponent* stat = go->GetComponent<StatsComponent>();
				if (stat)
				{
					stats.sprites.push_back(new Addon::WindowIcon(sf::Sprite(*Engine::Graphic.requestTexture("GUIIcons.png"), sf::IntRect(0, 0, 16, 16)), "Health", "Maximum health.", std::to_string(stat->maxHealth), Vector2(18, 0), std::pair<int, int>(0, 0), sf::Color(255, 255, 255)));
					stats.sprites.push_back(new Addon::WindowIcon(sf::Sprite(*Engine::Graphic.requestTexture("GUIIcons.png"), sf::IntRect(16, 0, 16, 16)), "Mana", "Maximum mana.", std::to_string(stat->maxMana), Vector2(18, 0), std::pair<int, int>(0, 0), sf::Color(255, 255, 255)));
					stats.sprites.push_back(new Addon::WindowIcon(sf::Sprite(*Engine::Graphic.requestTexture("GUIIcons.png"), sf::IntRect(32, 0, 16, 16)), "Stamina", "Maximum stamina.", std::to_string(stat->maxStamina), Vector2(18, 0), std::pair<int, int>(0, 0), sf::Color(255, 255, 255)));
					stats.sprites.push_back(new Addon::WindowIcon(sf::Sprite(*Engine::Graphic.requestTexture("GUIIcons.png"), sf::IntRect(48, 0, 16, 16)), "Agility", "Current agility, <TODO>", std::to_string(stat->agility), Vector2(18, 0), std::pair<int, int>(0, 0), sf::Color(255, 255, 255)));
					stats.sprites.push_back(new Addon::WindowIcon(sf::Sprite(*Engine::Graphic.requestTexture("GUIIcons.png"), sf::IntRect(64, 0, 16, 16)), "Defense", "Current defense.\nReduces incoming damage.", "0", Vector2(18, 0), std::pair<int, int>(0, 0), sf::Color(255, 255, 255)));
					stats.sprites.push_back(new Addon::WindowIcon(sf::Sprite(*Engine::Graphic.requestTexture("GUIIcons.png"), sf::IntRect(80, 0, 16, 16)), "Attack", "Current attack.\nIncreases outgoing damage.", "0", Vector2(18, 0), std::pair<int, int>(0, 0), sf::Color(255, 255, 255)));
					updateStats = false;
				}
			}
		}
		void StatsWindow::createEquipmentList()
		{
			for (std::vector<BaseWindowObject*>::iterator it = items.sprites.begin(); it != items.sprites.end(); ++it)
			{
				delete *it;
				*it = NULL;
			}
			items.sprites.clear();
			//TODO: REWORK THIS
			GameObject* go = NULL;// Engine::Window.focus.gameObject;
			if (go)
			{
				InventoryComponent* inv = go->GetComponent<InventoryComponent>();
				if (inv)
				{
					for (size_t i = 0; i < inv->bags.size(); ++i)
					{
						int ii = 0;
						std::vector<std::pair<Items::Item*, int>>::iterator it = inv->bags[i]->items.begin();
						for (it; it != inv->bags[i]->items.end(); ++it)
						{
							if (it->first)
								if (it->first->getTag() == Items::Item::armor || it->first->getTag() == Items::Item::weapon)
									items.sprites.push_back(new Addon::WindowIcon(it->first->icon, it->first->getName(), it->first->toToolTipString(), "", Vector2(0, 0), std::pair<int, int>(i, ii)));
							ii++;
						}
					}
					updateEquipment = false;
				}
			}
		}
		void StatsWindow::drawGearIcons()
		{
			//TODO: REWORK THIS
			GameObject* go = NULL;// Engine::Window.focus.gameObject;
			if (go)
			{
				EquipmentComponent* equip = go->GetComponent<EquipmentComponent>();
				if (equip)
				{
					for (int i = 0; i < 5; i++)
					{
						switch (i)
						{
						case 0:
#pragma region Helm
							if (equip->helm)
							{
								equip->helm->icon.setPosition(position.x + 240, position.y + 64 + 64 * i);
								swap(equip->helm->icon, go, equip, "Helm");
								if (mouseInsideIcon(equip->helm->icon) && !items.movingItem && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == (BaseWindow*)this ||
									mouseInsideIcon(equip->helm->icon) && !items.movingItem && !Engine::GUI.focusedWindow->checkMouseInside())
								{
									Engine::GUI.openedWindowToolTip.setToolTipText(equip->helm->getName(), equip->helm->toToolTipString());
									Engine::GUI.drawOpenedWindowToolTip = true;
								}
							}
							else
							{
								noEquippedItemIcon.setPosition(position.x + 240, position.y + 64 + 64 * i);
								swap(noEquippedItemIcon, go, equip, "Helm");
							}
#pragma endregion
							break;
						case 1:
#pragma region Chest
							if (equip->chest)
							{
								equip->chest->icon.setPosition(position.x + 240, position.y + 64 + 64 * i);
								swap(equip->chest->icon, go, equip, "Chest");
								if (mouseInsideIcon(equip->chest->icon) && !items.movingItem)
								{
									Engine::GUI.openedWindowToolTip.setToolTipText(equip->chest->getName(), equip->chest->toToolTipString());
									Engine::GUI.drawOpenedWindowToolTip = true;
								}
							}
							else
							{
								noEquippedItemIcon.setPosition(position.x + 240, position.y + 64 + 64 * i);
								swap(noEquippedItemIcon, go, equip, "Chest");
							}
#pragma endregion
							break;
						case 2:
#pragma region Gloves
							if (equip->gloves)
							{
								equip->gloves->icon.setPosition(position.x + 240, position.y + 64 + 64 * i);
								swap(equip->gloves->icon, go, equip, "Gloves");
								if (mouseInsideIcon(equip->gloves->icon) && !items.movingItem)
								{
									Engine::GUI.openedWindowToolTip.setToolTipText(equip->gloves->getName(), equip->gloves->toToolTipString());
									Engine::GUI.drawOpenedWindowToolTip = true;
								}
							}
							else
							{
								noEquippedItemIcon.setPosition(position.x + 240, position.y + 64 + 64 * i);
								swap(noEquippedItemIcon, go, equip, "Gloves");
							}
#pragma endregion
							break;
						case 3:
#pragma region Leggings
							if (equip->leggings)
							{
								equip->leggings->icon.setPosition(position.x + 240, position.y + 64 + 64 * i);
								swap(equip->leggings->icon, go, equip, "Leggings");
								if (mouseInsideIcon(equip->leggings->icon) && !items.movingItem)
								{
									Engine::GUI.openedWindowToolTip.setToolTipText(equip->leggings->getName(), equip->leggings->toToolTipString());
									Engine::GUI.drawOpenedWindowToolTip = true;
								}
							}
							else
							{
								noEquippedItemIcon.setPosition(position.x + 240, position.y + 64 + 64 * i);
								swap(noEquippedItemIcon, go, equip, "Leggings");
							}
#pragma endregion
							break;
						case 4:
#pragma region Boots
							if (equip->boots)
							{
								equip->boots->icon.setPosition(position.x + 240, position.y + 64 + 64 * i);
								swap(equip->boots->icon, go, equip, "Boots");
								if (mouseInsideIcon(equip->boots->icon) && !items.movingItem)
								{
									Engine::GUI.openedWindowToolTip.setToolTipText(equip->boots->getName(), equip->boots->toToolTipString());
									Engine::GUI.drawOpenedWindowToolTip = true;
								}
							}
							else
							{
								noEquippedItemIcon.setPosition(position.x + 240, position.y + 64 + 64 * i);
								swap(noEquippedItemIcon, go, equip, "Boots");
							}
#pragma endregion
							break;
						}
					}
				}
			}
		}
		bool StatsWindow::mouseInsideIcon(sf::Sprite& sprite)
		{
			if (Engine::GUI.mouseAim.position.x <= sprite.getLocalBounds().width + sprite.getPosition().x &&
				Engine::GUI.mouseAim.position.x >= sprite.getLocalBounds().left + sprite.getPosition().x)
				if (Engine::GUI.mouseAim.position.y <= sprite.getLocalBounds().height + sprite.getPosition().y &&
					Engine::GUI.mouseAim.position.y >= sprite.getLocalBounds().top + sprite.getPosition().y)
					return true;
			return false;
		}
		//Not being used atm.
		void StatsWindow::IconSelectHandle()
		{
			//TODO: REWORK THIS
			GameObject* go = NULL;// Engine::Window.focus.gameObject;
			if (go)
			{
				InventoryComponent* icp = go->GetComponent<InventoryComponent>();
				if (icp)
				{
				}
			}
		}
		void StatsWindow::swap(sf::Sprite& icon, GameObject* go, EquipmentComponent* equip, std::string armorType)
		{
			if (mouseInsideIcon(icon) && items.movingItem)
			{
#pragma region swapFromThisWindow
				InventoryComponent* icp = go->GetComponent<InventoryComponent>();
				Addon::WindowIcon* _item = (Addon::WindowIcon*)items.sprites[items.selectedBag];
				Items::Armor* arm = (Items::Armor*)icp->bags[_item->index.first]->items[_item->index.second].first;
				if (arm)
					if (arm->armorType == armorType)
					{
						icon.setColor(sf::Color(25, 150, 25));
						if (Engine::event.type == Engine::event.MouseButtonReleased)
						{
							if (Engine::event.mouseButton.button == sf::Mouse::Button::Left)
							{
								bool done = false;
								size_t ii = 0;
								for (size_t i = 0; i < icp->bags.size(); i++)
								{
									for (ii = 0; ii < icp->bags[i]->items.size(); ++ii)
									{
										if (icp->bags[i]->items[ii].first == arm)
										{
											done = true;
											break;
										}
									}
									if (done)
										break;
								}
								icp->bags[_item->index.first]->items[_item->index.second].first = equip->equipArmor(arm);
								if (icp->bags[_item->index.first]->items[_item->index.second].first)
								{
									icon.setColor(sf::Color(255, 255, 255));
									icp->bags[_item->index.first]->items[_item->index.second].second = 1;
									std::pair<int, int> pair = ((Addon::WindowIcon*)items.sprites[items.selectedBag])->index;

									delete items.sprites[items.selectedBag];
									items.sprites[items.selectedBag] = new Addon::WindowIcon(icp->bags[pair.first]->items[pair.second].first->icon,
										icp->bags[pair.first]->items[pair.second].first->getName(),
										icp->bags[pair.first]->items[pair.second].first->toToolTipString(), "", Vector2(0, 0), pair);
									if (Engine::GUI.inventory.createdInventory)
									{
										toolTip.setToolTipText("1", "1");

										Addon::WindowIcon* tmp = (Addon::WindowIcon*)Engine::GUI.inventory.scroll.sprites[ii];
										std::pair<int, int> pair = tmp->index;
										delete Engine::GUI.inventory.scroll.sprites[ii];
										Engine::GUI.inventory.scroll.sprites[ii] = new Addon::WindowIcon(icon,
											icp->bags[pair.first]->items[pair.second].first->getName(),
											icp->bags[pair.first]->items[pair.second].first->toToolTipString(), "1", Vector2(0, 16), pair);
									}
								}
								else
								{
									icp->bags[_item->index.first]->items[_item->index.second].second = 0;
									++icp->bags[_item->index.first]->freeSlots;
									delete items.sprites[items.selectedBag];
									items.sprites[items.selectedBag] = NULL;
									items.sprites.erase(items.sprites.begin() + items.selectedBag);
									if (Engine::GUI.inventory.createdInventory)
									{
										Addon::WindowIcon* tmp = (Addon::WindowIcon*)Engine::GUI.inventory.scroll.sprites[ii];
										std::pair<int, int> pair = tmp->index;
										delete Engine::GUI.inventory.scroll.sprites[ii];
										icon.setColor(sf::Color(255, 255, 255));
										Engine::GUI.inventory.scroll.sprites[ii] = new Addon::WindowIcon(icon, "", "", "", Vector2(0, 16), pair);
									}
								}
							}
						}
					}
					else
						icon.setColor(sf::Color(150, 25, 25));
#pragma endregion
			}
			else if (mouseInsideIcon(icon) && Engine::GUI.inventory.scroll.movingItem && !Engine::GUI.inventory.bagSlotSelected)
			{
#pragma region swapFromInventoryWindow
				InventoryComponent* icp = go->GetComponent<InventoryComponent>();
				Addon::WindowIcon* _item = (Addon::WindowIcon*)Engine::GUI.inventory.scroll.sprites[Engine::GUI.inventory.scroll.selectedBag];
				if (icp->bags[_item->index.first]->items[_item->index.second].first->getTag() == Items::Item::armor)
				{
					Items::Armor* arm = (Items::Armor*)icp->bags[_item->index.first]->items[_item->index.second].first;
					icon.setColor(sf::Color(25, 150, 25));
				}
				else
					icon.setColor(sf::Color(150, 25, 25));
			}
#pragma endregion
			else
				icon.setColor(sf::Color(255, 255, 255));
			Engine::Graphic.view.render.draw(icon);
			icon.setColor(sf::Color(255, 255, 255));
		}
	}
}