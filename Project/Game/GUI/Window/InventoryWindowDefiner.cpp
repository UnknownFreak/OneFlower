//#include "InventoryWindow.hpp"
//#include <Windows.h>
//#include "../../../Engine.hpp"
//#include <vector>
//#include "../../Item/Bag.hpp"
//#include "../../Item/Armor.hpp"
//#include "../../Component/InventoryComponent.hpp"
//#include "../../Component/EquipmentComponent.hpp"
//#include "../../Component/StatsComponent.hpp"
//#include "Addon/WindowIcon.hpp"
//
//namespace GUI
//{
//	namespace Windows
//	{
//
//		InventoryWindow::InventoryWindow(float x1, float y1, int x2, int y2) : BaseWindow(x1, y1, x2, y2, false, "Inventory"),
//			emptyInventorySlot(*Engine::Graphic.requestTexture("InventoryEmptyIcon.png"), sf::IntRect(0, 0, 32, 32)),
//			scroll(x1, y1 + 24, 0, 4, Vector2(32, 32), Vector2(5, 5), this, true), stats(x1, y1 + 32, 0, 4, Vector2(16, 16), Vector2(64, 5), this, false, false),
//			toolTip("None"), item(NULL), gold("coins.png", *Engine::Graphic.font.requestFont("Arial.ttf"), false, 0, 0, -16, 0),
//			weight(*Engine::Graphic.font.requestFont("Arial.ttf"))
//		{
//			weight.setSize(13);
//			gold.setSize(13);
//			emptyInventorySlot.setColor(sf::Color(255, 255, 255));
//			window.setPosition(x1, y1);
//			sf::Texture * tx = Engine::Graphic.requestTexture("ToolTipIcon.png");
//			tx->setRepeated(true);
//		}
//		void InventoryWindow::draw()
//		{
//			if (open)
//			{
//				if (updateStats)
//					createStats();
//				if (!createdInventory)
//					CreateScrollItems();
//				move();
//				WindowHandle();
//				BaseWindow::draw();
//				stats.draw();
//				drawGearIcons();
//				IconDrawHandle();
//
//				if (scroll.tooltip.first && !scroll.movingItem && Engine::GUI.showToolTip && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == (BaseWindow*)this ||
//					scroll.tooltip.first && !scroll.movingItem && Engine::GUI.showToolTip && !Engine::GUI.focusedWindow->checkMouseInside())
//					if (scroll.mouseInsideIcon(*scroll.tooltip.first) && scroll.tooltip.second.getToolTipBody() != "")
//					{
//						Engine::GUI.openedWindowToolTip.setToolTipText(scroll.tooltip.second.getToolTipTitle(), scroll.tooltip.second.getToolTipBody());
//						Engine::GUI.drawOpenedWindowToolTip = true;
//					}
//					else;
//				else if (stats.tooltip.first && !stats.movingItem && Engine::GUI.showToolTip && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == (BaseWindow*)this ||
//					stats.tooltip.first && !stats.movingItem && Engine::GUI.showToolTip  && !Engine::GUI.focusedWindow->checkMouseInside())
//					if (stats.mouseInsideIcon(*stats.tooltip.first) && stats.tooltip.second.getToolTipBody() != "")
//					{
//						Engine::GUI.openedWindowToolTip.setToolTipText(stats.tooltip.second.getToolTipTitle(), stats.tooltip.second.getToolTipBody());
//						Engine::GUI.drawOpenedWindowToolTip = true;
//					}
//			}
//		}
//		void InventoryWindow::CreateScrollItems()
//		{
//			for (auto it = scroll.sprites.begin(); it != scroll.sprites.end(); ++it)
//			{
//				delete *it;
//				*it = NULL;
//			}
//			scroll.sprites.clear();
//			if (Engine::game.player)
//			{
//				InventoryComponent* inv = Engine::game.player->GetComponent<InventoryComponent>();
//				if (inv)
//				{
//					int max = inv->maxBags;
//					std::vector<Items::Bag*>& b = inv->bags;
//					for (int it = 0; it < max; ++it)
//					{
//						int i = 0;
//						if (it < b.size())
//						{
//							Items::Bag* bag = b[it];
//							for (std::vector<std::pair<Items::Item*, int>>::iterator iit = bag->items.begin(); iit != bag->items.end(); ++iit)
//							{
//								if (iit->first)
//									scroll.sprites.push_back(new Addon::WindowIcon(iit->first->icon, iit->first->getName(), iit->first->toToolTipString(), std::to_string(iit->second), Vector2(0, 16), std::pair<int, int>(it, i), sf::Color::Black, 12));
//								else
//									scroll.sprites.push_back(new Addon::WindowIcon(emptyInventorySlot, "", "", "", Vector2(0, 16), std::pair<int, int>(it, i), sf::Color::Black, 12));
//								++i;
//							}
//						}
//					}
//				}
//			}
//			if (scroll.sprites.size() > 0)
//				createdInventory = true;
//		}
//		void InventoryWindow::WindowHandle()
//		{
//			stats.setPosition(position.x + 40.0 + offsetX, position.y + 40.0 + offsetY);
//			stats.setSizeY(256);
//			stats.setSizeX(136);
//
//			scroll.setSizeY(window.getTextureRect().height - 108);
//			scroll.setSizeX(window.getTextureRect().width - 120);
//			scroll.setPosition(position.x + 100 + offsetX, position.y + 40.0 + offsetY);
//			gold.setPosition(window.getPosition().x + window.getTextureRect().width - 18, window.getPosition().y + window.getTextureRect().height - 20);
//			weight.setPosition(window.getPosition().x + 8, window.getPosition().y + window.getTextureRect().height - 20);
//			BaseWindow::WindowHandle();
//		}
//		bool InventoryWindow::mouseInsideIcon(sf::Sprite& sprite)
//		{
//			if (Engine::GUI.mouseAim.position.x <= sprite.getLocalBounds().width + sprite.getPosition().x &&
//				Engine::GUI.mouseAim.position.x >= sprite.getLocalBounds().left + sprite.getPosition().x)
//				if (Engine::GUI.mouseAim.position.y <= sprite.getLocalBounds().height + sprite.getPosition().y &&
//					Engine::GUI.mouseAim.position.y >= sprite.getLocalBounds().top + sprite.getPosition().y)
//					return true;
//			return false;
//		}
//		void InventoryWindow::IconDrawHandle()
//		{
//			if (Engine::game.player)
//			{
//				InventoryComponent* inv = Engine::game.player->GetComponent<InventoryComponent>();
//				if (inv)
//				{
//					drawGold();
//					drawWeight(inv);
//					swap();
//
//					int max = inv->maxBags;
//					std::vector<Items::Bag*>& b = inv->bags;
//					Vector2 off(window.getPosition().x + (window.getTextureRect().width / 2) - 74.f, window.getPosition().y + window.getTextureRect().height - 54);
//					for (int it = 0; it < max; ++it)
//					{
//						if (it < b.size())
//						{
//							Items::Bag* bag = b[it];
//							ClickOnBagSlot(bag);
//							bag->icon.setPosition(off.x, off.y);
//							if (mouseInsideIcon(bag->icon) && scroll.getIfMovingItem())
//							{
//								bag->icon.setColor(sf::Color(150, 25, 25));
//								Engine::Graphic.view.render.draw(bag->icon);
//								bag->icon.setColor(sf::Color(255, 255, 255));
//							}
//							else if (mouseInsideIcon(bag->icon))
//							{
//								bag->icon.setColor(sf::Color(150, 150, 150));
//								Engine::Graphic.view.render.draw(bag->icon);
//								bag->icon.setColor(sf::Color(255, 255, 255));
//							}
//							else
//								Engine::Graphic.view.render.draw(bag->icon);
//						}
//						else
//							tryEquipBag(off);
//						off.x += iconSize + iconOffset;
//					}
//					scroll.draw();
//				}
//			}
//		}
//		void InventoryWindow::ClickOnBagSlot(Items::Bag* bag)
//		{
//			if (mouseInsideIcon(bag->icon) && !scroll.movingItem)
//			{
//				if (windowLClick)
//				{
//					clickOffset.x = Engine::Input.mouse.pos.x - bag->icon.getPosition().x;
//					clickOffset.y = Engine::Input.mouse.pos.y - bag->icon.getPosition().y;
//					scroll.movingItem = true;
//					bagSlotSelected = true;
//					scroll.unequipBag = true;
//					scroll.selectedBag = bag->freeSlots;
//					item = bag;
//					scroll.selected = &bag->icon;
//				}
//				if (Engine::GUI.showToolTip && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == (BaseWindow*)this ||
//					Engine::GUI.showToolTip && !Engine::GUI.focusedWindow->checkMouseInside())
//				{
//					Engine::GUI.openedWindowToolTip.setToolTipText(bag->getName(), bag->toToolTipString());
//					Engine::GUI.drawOpenedWindowToolTip = true;
//				}
//			}
//		}
//		void InventoryWindow::swap()
//		{
//			if (Engine::event.type == Engine::event.MouseButtonReleased && focus)
//			{
//				if (Engine::event.mouseButton.button == sf::Mouse::Button::Left && scroll.selectedBag != -1 && scroll.swapBag != -1)
//				{
//					Addon::WindowIcon* selected = (Addon::WindowIcon*)(scroll.sprites[scroll.selectedBag]);
//					Addon::WindowIcon* swap = (Addon::WindowIcon*)(scroll.sprites[scroll.swapBag]);
//					InventoryComponent* icp = Engine::game.player->GetComponent<InventoryComponent>();
//
//					if (scroll.requestSwap && !bagSlotSelected && scroll.mouseInside() && !scroll.equipItem)
//					{
//						if (icp->swapItem(icp->bags[selected->index.first], selected->index.second, icp->bags[swap->index.first], swap->index.second))
//						{
//							scroll.requestSwap = false;
//							scroll.movingItem = false;
//
//							scroll.tooltip.first = NULL;
//
//							BaseWindowObject* tmp = scroll.sprites[scroll.selectedBag];
//							scroll.sprites[scroll.selectedBag] = scroll.sprites[scroll.swapBag];
//							scroll.sprites[scroll.swapBag] = tmp;
//
//							std::pair<int, int> tmp_two = ((Addon::WindowIcon*)scroll.sprites[scroll.selectedBag])->index;
//							((Addon::WindowIcon*)scroll.sprites[scroll.selectedBag])->index = ((Addon::WindowIcon*)scroll.sprites[scroll.swapBag])->index;
//							((Addon::WindowIcon*)scroll.sprites[scroll.swapBag])->index = tmp_two;
//							Engine::GUI.stats.updateEquipment = true;
//							Engine::GUI.tradingWindow.setScrollbarUpdate(true);
//						}
//					}
//					if (scroll.requestSwap && bagSlotSelected && scroll.mouseInside())
//					{
//						int start = 0;
//						int end = 0;
//						for (std::vector<Items::Bag*>::iterator it = icp->bags.begin(); it != icp->bags.end(); ++it)
//						{
//							Items::Bag* tmp = *it;
//							Items::Bag* itm = (Items::Bag*)item;
//							if (tmp == itm)
//							{
//								end += itm->size;
//								break;
//							}
//							end += tmp->size;
//							start += tmp->size;
//						}
//						if (icp->unequipBag((Items::Bag*)item, icp->bags[swap->index.first], swap->index.second))
//						{
//							int insertLocationBag = 0;
//							for (int i = 0; i < swap->index.first; ++i)
//							{
//								insertLocationBag += icp->bags[i]->size;
//							}
//							insertLocationBag += swap->index.second;
//
//							Addon::WindowIcon* itm = (Addon::WindowIcon*)scroll.sprites[insertLocationBag];
//							itm->icon = item->icon;
//							itm->messageText = "1";
//							itm->toolTipTitle = item->getName();
//							itm->toolTipBody = item->toToolTipString();
//							for (std::vector<BaseWindowObject*>::iterator it = scroll.sprites.begin() + start; it != scroll.sprites.begin() + end; ++it)
//							{
//								delete *it;
//								*it = NULL;
//							}
//							scroll.sprites.erase(scroll.sprites.begin() + start, scroll.sprites.begin() + end);
//
//							scroll.movingItem = false;
//							scroll.requestSwap = false;
//							scroll.unequipBag = false;
//							bagSlotSelected = false;
//
//							Engine::GUI.tradingWindow.setScrollbarUpdate(true);
//						}
//					}
//					if (!scroll.movingItem)
//					{
//						scroll.selectedBag = -1;
//						scroll.swapBag = -1;
//						scroll.requestSwap = false;
//						bagSlotSelected = false;
//						scroll.unequipBag = false;
//						item = NULL;
//					}
//				}
//			}
//		}
//		bool InventoryWindow::tryEquipBag(Vector2& off)
//		{
//			emptyInventorySlot.setTextureRect(sf::IntRect(0, 0, iconSize, iconSize));
//			emptyInventorySlot.setPosition(off.x, off.y);
//			if (scroll.getIfMovingItem() && mouseInsideIcon(emptyInventorySlot))
//			{
//				InventoryComponent* icp =Engine::game.player->GetComponent<InventoryComponent>();
//				Addon::WindowIcon* swap = (Addon::WindowIcon*)(scroll.sprites[scroll.selectedBag]);
//
//				if (icp->bags[swap->index.first]->items[swap->index.second].first)
//					if (icp->bags[swap->index.first]->items[swap->index.second].first->getTag() == Items::Item::bag)
//					{
//						emptyInventorySlot.setColor(sf::Color(25, 150, 25));
//						Engine::Graphic.view.render.draw(emptyInventorySlot);
//						emptyInventorySlot.setColor(sf::Color(255, 255, 255));
//						if (Engine::event.type == Engine::event.MouseButtonReleased)
//						{
//							if (Engine::event.mouseButton.button == sf::Mouse::Button::Left)
//							{
//								if (icp->equipBag(icp->bags[swap->index.first], swap->index.second))
//								{
//									scroll.movingItem = false;
//									scroll.requestSwap = false;
//									scroll.equipItem = false;
//									Addon::WindowIcon* itm = (Addon::WindowIcon*)scroll.sprites[scroll.selectedBag];
//									std::pair<int, int> pair = itm->index;
//									delete scroll.sprites[scroll.selectedBag];
//									scroll.sprites[scroll.selectedBag] = NULL;
//									scroll.sprites[scroll.selectedBag] = new Addon::WindowIcon(emptyInventorySlot, "", "", "", Vector2(0, 16), pair);
//									int bag = icp->bags.size();
//									for (int i = 0; i < icp->bags[icp->bags.size() - 1]->size; ++i)
//									{
//										scroll.sprites.push_back(new Addon::WindowIcon(emptyInventorySlot, "", "", "", Vector2(0, 16), std::pair<int, int>(bag, i), sf::Color::Black, 12));
//									}
//									if (!Engine::GUI.tradingWindow.getScrollbarUpdate())
//									{
//										for (size_t it = 0;
//											it != Engine::GUI.tradingWindow.scroll.sprites.size(); ++it)
//											if (((Addon::WindowIcon*)Engine::GUI.tradingWindow.scroll.sprites[it])->index == pair)
//											{
//												delete Engine::GUI.tradingWindow.scroll.sprites[it];
//												Engine::GUI.tradingWindow.scroll.sprites[it] = NULL;
//												Engine::GUI.tradingWindow.scroll.sprites.erase(Engine::GUI.tradingWindow.scroll.sprites.begin() + it);
//												break;
//											}
//									}
//									return true;
//								}
//							}
//						}
//					}
//					else
//					{
//						emptyInventorySlot.setColor(sf::Color(150, 25, 25));
//						Engine::Graphic.view.render.draw(emptyInventorySlot);
//						emptyInventorySlot.setColor(sf::Color(255, 255, 255));
//					}
//			}
//			else if (scroll.mouseInside() && scroll.getIfMovingItem() && !scroll.requestSwap || !checkMouseInside() && scroll.getIfMovingItem() && !scroll.requestSwap)
//				Engine::Graphic.view.render.draw(emptyInventorySlot);
//			else
//				Engine::Graphic.view.render.draw(emptyInventorySlot);
//			return false;
//		}
//		sf::Sprite InventoryWindow::getEmptyInventorySlotIcon()
//		{
//			return emptyInventorySlot;
//		}
//		void InventoryWindow::drawGold()
//		{
//			gold.draw();
//			std::string sgold = "0";// std::to_string(Engine::Window.focus.gameObject->GetComponent<InventoryComponent>()->coins);
//			gold = "§Icon|coins|0|0|" + sgold;
//		}
//
//		void InventoryWindow::drawWeight(InventoryComponent* inv)
//		{
//			weight = "Total weight: " + inv->getWeight();
//			weight.draw();
//		}
//
//		//Equipment part
//
//		void InventoryWindow::drawGearIcons()
//		{
//			if (Engine::game.player)
//			{
//				EquipmentComponent* equip = Engine::game.player->GetComponent<EquipmentComponent>();
//				if (equip)
//				{
//					for (int i = 0; i < 5; i++)
//					{
//						switch (i)
//						{
//						case 0:
//#pragma region Helm
//							if (equip->helm)
//							{
//								equip->helm->icon.setPosition(position.x + 10 + offsetX, position.y + offsetY + 46.f + 37 * i);
//								swap(equip->helm->icon, Engine::game.player, equip, "Helm");
//								if (mouseInsideIcon(equip->helm->icon) && !scroll.movingItem && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == (BaseWindow*)this ||
//									mouseInsideIcon(equip->helm->icon) && !scroll.movingItem && !Engine::GUI.focusedWindow->checkMouseInside())
//								{
//									Engine::GUI.openedWindowToolTip.setToolTipText(equip->helm->getName(), equip->helm->toToolTipString());
//									Engine::GUI.drawOpenedWindowToolTip = true;
//								}
//							}
//							else
//							{
//								emptyInventorySlot.setPosition(position.x + 10 + offsetX, position.y + offsetY + 46.f + 37 * i);
//								swap(emptyInventorySlot, Engine::game.player, equip, "Helm");
//							}
//#pragma endregion
//							break;
//						case 1:
//#pragma region Chest
//							if (equip->chest)
//							{
//								equip->chest->icon.setPosition(position.x + 10 + offsetX, position.y + offsetY + 46.f + 37 * i);
//								swap(equip->chest->icon, Engine::game.player, equip, "Chest");
//								if (mouseInsideIcon(equip->chest->icon) && !scroll.movingItem)
//								{
//									Engine::GUI.openedWindowToolTip.setToolTipText(equip->chest->getName(), equip->chest->toToolTipString());
//									Engine::GUI.drawOpenedWindowToolTip = true;
//								}
//							}
//							else
//							{
//								emptyInventorySlot.setPosition(position.x + 10 + offsetX, position.y + offsetY + 46.f + 37 * i);
//								swap(emptyInventorySlot, Engine::game.player, equip, "Chest");
//							}
//#pragma endregion
//							break;
//						case 2:
//#pragma region Gloves
//							if (equip->gloves)
//							{
//								equip->gloves->icon.setPosition(position.x + 10 + offsetX, position.y + offsetY + 46.f + 37 * i);
//								swap(equip->gloves->icon, Engine::game.player, equip, "Gloves");
//								if (mouseInsideIcon(equip->gloves->icon) && !scroll.movingItem)
//								{
//									Engine::GUI.openedWindowToolTip.setToolTipText(equip->gloves->getName(), equip->gloves->toToolTipString());
//									Engine::GUI.drawOpenedWindowToolTip = true;
//								}
//							}
//							else
//							{
//								emptyInventorySlot.setPosition(position.x + 10 + offsetX, position.y + offsetY + 46.f + 37 * i);
//								swap(emptyInventorySlot, Engine::game.player, equip, "Gloves");
//							}
//#pragma endregion
//							break;
//						case 3:
//#pragma region Leggings
//							if (equip->leggings)
//							{
//								equip->leggings->icon.setPosition(position.x + 10 + offsetX, position.y + offsetY + 46.f + 37 * i);
//								swap(equip->leggings->icon, Engine::game.player, equip, "Leggings");
//								if (mouseInsideIcon(equip->leggings->icon) && !scroll.movingItem)
//								{
//									Engine::GUI.openedWindowToolTip.setToolTipText(equip->leggings->getName(), equip->leggings->toToolTipString());
//									Engine::GUI.drawOpenedWindowToolTip = true;
//								}
//							}
//							else
//							{
//								emptyInventorySlot.setPosition(position.x + 10 + offsetX, position.y + offsetY + 46.f + 37 * i);
//								swap(emptyInventorySlot, Engine::game.player, equip, "Leggings");
//							}
//#pragma endregion
//							break;
//						case 4:
//#pragma region Boots
//							if (equip->boots)
//							{
//								equip->boots->icon.setPosition(position.x + 10 + offsetX, position.y + offsetY + 46.f + 37 * i);
//								swap(equip->boots->icon, Engine::game.player, equip, "Boots");
//								if (mouseInsideIcon(equip->boots->icon) && !scroll.movingItem)
//								{
//									Engine::GUI.openedWindowToolTip.setToolTipText(equip->boots->getName(), equip->boots->toToolTipString());
//									Engine::GUI.drawOpenedWindowToolTip = true;
//								}
//							}
//							else
//							{
//								emptyInventorySlot.setPosition(position.x + 10 + offsetX, position.y + offsetY + 46.f + 37 * i);
//								swap(emptyInventorySlot, Engine::game.player, equip, "Boots");
//							}
//#pragma endregion
//							break;
//						}
//					}
//				}
//			}
//		}
//
//		void InventoryWindow::swap(sf::Sprite& icon, GameObject* go, EquipmentComponent* equip, std::string armorType)
//		{
//			if (mouseInsideIcon(icon) && scroll.movingItem)
//			{
//#pragma region swapFromThisWindow
//				InventoryComponent* icp = go->GetComponent<InventoryComponent>();
//				Addon::WindowIcon* _item = (Addon::WindowIcon*)scroll.sprites[scroll.selectedBag];
//				Items::Armor* arm = (Items::Armor*)icp->bags[_item->index.first]->items[_item->index.second].first;
//				if (arm)
//					if (arm->armorType == armorType)
//					{
//						icon.setColor(sf::Color(25, 150, 25));
//						if (Engine::event.type == Engine::event.MouseButtonReleased)
//						{
//							if (Engine::event.mouseButton.button == sf::Mouse::Button::Left)
//							{
//								bool done = false;
//								size_t ii = 0;
//								for (size_t i = 0; i < icp->bags.size(); i++)
//								{
//									for (ii = 0; ii < icp->bags[i]->items.size(); ++ii)
//									{
//										if (icp->bags[i]->items[ii].first == arm)
//										{
//											done = true;
//											break;
//										}
//									}
//									if (done)
//										break;
//								}
//								icp->bags[_item->index.first]->items[_item->index.second].first = equip->equipArmor(arm);
//								if (icp->bags[_item->index.first]->items[_item->index.second].first)
//								{
//									icon.setColor(sf::Color(255, 255, 255));
//									icp->bags[_item->index.first]->items[_item->index.second].second = 1;
//									std::pair<int, int> pair = ((Addon::WindowIcon*)scroll.sprites[scroll.selectedBag])->index;
//
//									delete scroll.sprites[scroll.selectedBag];
//									scroll.sprites[scroll.selectedBag] = new Addon::WindowIcon(icp->bags[pair.first]->items[pair.second].first->icon,
//										icp->bags[pair.first]->items[pair.second].first->getName(),
//										icp->bags[pair.first]->items[pair.second].first->toToolTipString(), "1", Vector2(0, 16), pair);
//								}
//								else
//								{
//									icp->bags[_item->index.first]->items[_item->index.second].second = 0;
//									++icp->bags[_item->index.first]->freeSlots;
//									Addon::WindowIcon* tmp = (Addon::WindowIcon*)Engine::GUI.inventory.scroll.sprites[ii];
//									std::pair<int, int> pair = tmp->index;
//									delete scroll.sprites[scroll.selectedBag];
//
//									scroll.sprites[scroll.selectedBag] = NULL;
//									icon.setColor(sf::Color(255, 255, 255));
//									Engine::GUI.inventory.scroll.sprites[ii] = new Addon::WindowIcon(icon, "", "", "", Vector2(0, 16), pair);
//								}
//							}
//						}
//					}
//					else
//						icon.setColor(sf::Color(150, 25, 25));
//#pragma endregion
//			}
//			else
//				icon.setColor(sf::Color(255, 255, 255));
//			Engine::Graphic.view.render.draw(icon);
//			icon.setColor(sf::Color(255, 255, 255));
//		}
//		//*
//		void InventoryWindow::createStats()
//		{
//			for (std::vector<BaseWindowObject*>::iterator it = stats.sprites.begin(); it != stats.sprites.end(); it++)
//			{
//				delete *it;
//				*it = NULL;
//			}
//			stats.sprites.clear();
//			if (Engine::game.player)
//			{
//				StatsComponent* stat = Engine::game.player->GetComponent<StatsComponent>();
//				if (stat)
//				{
//					stats.sprites.push_back(new Addon::WindowIcon(sf::Sprite(*Engine::Graphic.requestTexture("GUIIcons.png"), sf::IntRect(0, 0, 16, 16)), "Health", "Maximum health.", std::to_string(stat->maxHealth), Vector2(18, 0), std::pair<int, int>(0, 0), sf::Color(255, 255, 255)));
//					stats.sprites.push_back(new Addon::WindowIcon(sf::Sprite(*Engine::Graphic.requestTexture("GUIIcons.png"), sf::IntRect(16, 0, 16, 16)), "Mana", "Maximum mana.", std::to_string(stat->maxMana), Vector2(18, 0), std::pair<int, int>(0, 0), sf::Color(255, 255, 255)));
//					stats.sprites.push_back(new Addon::WindowIcon(sf::Sprite(*Engine::Graphic.requestTexture("GUIIcons.png"), sf::IntRect(32, 0, 16, 16)), "Stamina", "Maximum stamina.", std::to_string(stat->maxStamina), Vector2(18, 0), std::pair<int, int>(0, 0), sf::Color(255, 255, 255)));
//					stats.sprites.push_back(new Addon::WindowIcon(sf::Sprite(*Engine::Graphic.requestTexture("GUIIcons.png"), sf::IntRect(48, 0, 16, 16)), "Agility", "Current agility, <TODO>", std::to_string(stat->agility), Vector2(18, 0), std::pair<int, int>(0, 0), sf::Color(255, 255, 255)));
//					stats.sprites.push_back(new Addon::WindowIcon(sf::Sprite(*Engine::Graphic.requestTexture("GUIIcons.png"), sf::IntRect(64, 0, 16, 16)), "Defense", "Current defense.\nReduces incoming damage.", "0", Vector2(18, 0), std::pair<int, int>(0, 0), sf::Color(255, 255, 255)));
//					stats.sprites.push_back(new Addon::WindowIcon(sf::Sprite(*Engine::Graphic.requestTexture("GUIIcons.png"), sf::IntRect(80, 0, 16, 16)), "Attack", "Current attack.\nIncreases outgoing damage.", "0", Vector2(18, 0), std::pair<int, int>(0, 0), sf::Color(255, 255, 255)));
//					updateStats = false;
//				}
//			}
//		}
//		//*/
//	}
//}