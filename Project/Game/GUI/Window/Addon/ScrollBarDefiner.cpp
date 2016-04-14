#include "ScrollBar.hpp"
#include "../../../../Engine.hpp"

#include "../../../Component/InventoryComponent.hpp"
#include "../../../Item/Bag.hpp"
#include "../BaseWindow.hpp"
#include "WindowIcon.hpp"
namespace GUI
{
	namespace Window
	{
		namespace Addon
		{
			ScrollBar::ScrollBar(float x, float y, int sizeX, int sizeY, Vector2 iconSize, Vector2 iconOffset, BaseWindow* parent, bool swapItems, bool clickableIcons) : scrollLine(sf::PrimitiveType::LinesStrip, 2),
				top("ScrollBar.png", sf::IntRect(Engine::Graphic.requestTexture("ScrollBar.png")->getSize().x / 2, 0,
				Engine::Graphic.requestTexture("ScrollBar.png")->getSize().x / 2,
				Engine::Graphic.requestTexture("ScrollBar.png")->getSize().y / 2), x, y, ""),

				bot("ScrollBar.png", sf::IntRect(Engine::Graphic.requestTexture("ScrollBar.png")->getSize().x / 2,
				Engine::Graphic.requestTexture("ScrollBar.png")->getSize().y / 2,
				Engine::Graphic.requestTexture("ScrollBar.png")->getSize().x / 2,
				Engine::Graphic.requestTexture("ScrollBar.png")->getSize().y / 2), x, y + sizeY, ""), scrolling(false),

				scroll("ScrollBar.png", sf::IntRect(0, 0, Engine::Graphic.requestTexture("ScrollBar.png")->getSize().x / 2,
				Engine::Graphic.requestTexture("ScrollBar.png")->getSize().y / 2), x, y + 8, ""), parent(parent),
				offset(parent->position.x, parent->position.y), canSwapItems(swapItems),
				iconSize(iconSize), iconOffset(iconOffset), position(x, y), size(sizeX, sizeY)
				, tooltip(NULL, ToolTip()), clickableIcons(clickableIcons)
			{
				double scaleX = 8 / (Engine::Graphic.requestTexture("ScrollBar.png")->getSize().x / 2.0);
				double scaleY = 8 / (Engine::Graphic.requestTexture("ScrollBar.png")->getSize().y / 2.0);
				top.icon.setScale(scaleX, scaleY);
				bot.icon.setScale(scaleX, scaleY);
				scroll.icon.setScale(scaleX, 1);
				setPosition(x, y);
			}
			ScrollBar::~ScrollBar()
			{
				for (size_t i = 0; i < sprites.size(); i++)
				{
					delete sprites[i];
					sprites[i] = NULL;
				}
			}
			void ScrollBar::draw()
			{
				scrollHandle();
				if (_draw)
				{
					Engine::Graphic.view.render.draw(scrollLine);
					top.draw();
					bot.draw();
					scroll.draw();
				}
				int i = 0;
				Vector2 off(offset);
				for (std::vector<BaseWindowObject*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
				{
					BaseWindowObject* obj = *it;
					if (obj)
					{
						obj->setPosition(off.x, off.y - scrolled);
						drawIcon(*obj, off, i);
						setTiles(off);
						++i;
					}
				}
				checkIfScrollBar(off);
				i = 0;
				off = offset;
			}
			void ScrollBar::setPosition(double x, double y)
			{
				position.x = x;
				position.y = y;
				offset.x = position.x + 60;
				offset.y = position.y + 6;
				scrollLine[0].position = sf::Vector2f(position.x + size.x + 3.5, position.y + 1);
				scrollLine[1].position = sf::Vector2f(position.x + size.x + 3.5, position.y + size.y);
				top.setPosition(position.x + size.x, position.y);
				bot.setPosition(position.x + size.x, position.y + size.y);
				scroll.setPosition(position.x + size.x, top.getPosition().y + 8 + (((bot.getPosition().y - 16 - scroll.icon.getTextureRect().height) - top.getPosition().y + 8) * (scrolled / maxScrolls)));
			}
			void ScrollBar::setTiles(Vector2& off)
			{
				off.x += iconSize.x + iconOffset.x;
				if (off.x > top.icon.getPosition().x - iconSize.x - iconOffset.x)
				{
					off.y += iconSize.y + iconOffset.y;
					off.x = offset.x;
				}
			}
			void ScrollBar::checkIfScrollBar(Vector2&off)
			{
				double width = top.icon.getPosition().x - offset.x;
				double itemsPerRow_f = width / (iconSize.x + iconOffset.x);
				double windowSize = bot.getPosition().y + 8 - offset.y;
				double totalRows_f = sprites.size() / itemsPerRow_f;
				double itemsInWindow = (windowSize) / (iconSize.y + iconOffset.y);

				if ((int)totalRows_f < totalRows_f)
					totalRows_f = (int)totalRows_f + 1;
				maxScrolls = off.y - bot.getPosition().y + 8 + iconOffset.y;
				deltaScrolls = itemsInWindow / (totalRows_f);

				int size = (bot.getPosition().y - (top.getPosition().y + 8)) * deltaScrolls;
				setScrollBarSize(size);

				if (deltaScrolls > 1 || deltaScrolls <= 0)
					_draw = false;
				else
					_draw = true;
			}
			void ScrollBar::setScrollBarSize(int size)
			{
				scroll.icon.setTextureRect(sf::IntRect(0, 0, scroll.icon.getTextureRect().width, size));
			}
			void ScrollBar::setSizeY(int len)
			{
				size.y = len;
			}
			bool ScrollBar::checkCulling(sf::Sprite* sprite, Vector2& position)
			{
				if (position.y - scrolled > top.getPosition().y && position.y - scrolled + iconSize.y < bot.getPosition().y + 8)
				{
					sprite->setTextureRect(sf::IntRect(sprite->getTextureRect().left, 0, iconSize.x, iconSize.y));
					return true;
				}
				else if (position.y - scrolled + iconSize.y > top.getPosition().y && !(position.y - scrolled + iconSize.y + iconOffset.y > bot.getPosition().y + 8))
				{
					double minSize = sprite->getPosition().y + iconSize.y;
					double topSize = top.getPosition().y;
					sprite->setTextureRect(sf::IntRect(sprite->getTextureRect().left, iconSize.y - (minSize - topSize), iconSize.x, (minSize - topSize)));
					sprite->setPosition(position.x, top.getPosition().y);
					return true;
				}
				else if (position.y - scrolled < bot.getPosition().y && position.y - scrolled + iconSize.y + iconOffset.y > bot.icon.getPosition().y + 8)
				{
					double minSize = sprite->getPosition().y + iconSize.y;
					double topSize = bot.getPosition().y + 8;
					sprite->setTextureRect(sf::IntRect(sprite->getTextureRect().left, 0, iconSize.x, iconSize.y - (minSize - topSize)));
					return true;
				}
				return false;
			}
			void ScrollBar::scrollHandle()
			{
				if (_draw)
				{
					if (parent->focus)
					{
						if (top.onHover() && parent->windowLClick)
						{
							scrolled -= 8;
							if (scrolled < 0)
								scrolled = 0;
						}
						else if (bot.onHover() && parent->windowLClick)
						{
							scrolled += 8;
							if (scrolled > maxScrolls)
								scrolled = maxScrolls;
						}
						else if (scroll.onHover() && parent->windowLClick)
							scrolling = true;
					}
					if (scrolling && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						if (mousePosY < Engine::Input.mouse.pos.y)
						{
							scrolled += Engine::Input.mouse.pos.y - mousePosY;
							mousePosY = Engine::Input.mouse.pos.y;
						}
						else if (mousePosY > Engine::Input.mouse.pos.y)
						{
							scrolled -= mousePosY - Engine::Input.mouse.pos.y;
							mousePosY = Engine::Input.mouse.pos.y;
						}
						else
							mousePosY = Engine::Input.mouse.pos.y;
						if (scrolled < 0)
							scrolled = 0;
						else if (scrolled > maxScrolls)
							scrolled = maxScrolls;
					}
					else
						scrolling = false;
					scroll.setPosition(scroll.getPosition().x, top.getPosition().y + 8 + (((bot.getPosition().y - 16 - scroll.icon.getTextureRect().height) - top.getPosition().y + 8) * (scrolled / maxScrolls)));
				}
				movingItemScrollHandle();
			}
			void ScrollBar::movingItemScrollHandle()
			{
				if (movingItem && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					if (selected)
					{
						selected->setPosition(Engine::GUI.mouseAim.position.x, Engine::GUI.mouseAim.position.y);
						selected->setColor(sf::Color(255, 255, 255, 127));
						Engine::Graphic.view.render.draw(*selected);
						selected->setColor(sf::Color(255, 255, 255));
					}
				}
				else if (movingItem && !mouseInsideIcon(*selected) && canSwapItems && mouseInside())
				{
					movingItem = false;
					requestSwap = true;
				}
				else if (movingItem && !mouseInside() && !equipItem)
				{
					movingItem = false;
					requestSwap = false;
				}
				else
					movingItem = false;
			}

			void ScrollBar::setSizeX(int x)
			{
				size.x = x;
			}
			bool ScrollBar::mouseInsideIcon(sf::Sprite& sprite)
			{
				if (Engine::GUI.mouseAim.position.x <= sprite.getLocalBounds().width + sprite.getPosition().x &&
					Engine::GUI.mouseAim.position.x >= sprite.getLocalBounds().left + sprite.getPosition().x)
					if (Engine::GUI.mouseAim.position.y <= sprite.getLocalBounds().height + sprite.getPosition().y &&
						Engine::GUI.mouseAim.position.y >= sprite.getLocalBounds().top + sprite.getPosition().y)
						return true;
				return false;
			}
			void ScrollBar::drawIcon(BaseWindowObject& obj, Vector2& off, int i)
			{
				if (obj.type == 1)
				{
					WindowIcon& ico = (WindowIcon&)obj;
					if (checkCulling(&ico.icon, off))
					{
						if (mouseInsideIcon(ico.icon) && !movingItem && parent->focus ||
							mouseInsideIcon(ico.icon) && !movingItem && !Engine::GUI.focusedWindow->checkMouseInside() ||
							mouseInsideIcon(ico.icon) && !movingItem && parent->requestFocus)
						{
							if (!canSwapItems && selected == &ico.icon)
							{
								ico.icon.setColor(sf::Color(25, 230, 140));
								ico.draw();
								ico.icon.setColor(sf::Color(255, 255, 255));
							}
							else if (!canSwapItems && clickableIcons)
							{
								ico.icon.setColor(sf::Color(25, 230, 140, 127));
								ico.draw();
								ico.icon.setColor(sf::Color(255, 255, 255));
							}
							else if (!clickableIcons)
								ico.draw();
							else
							{
								ico.icon.setColor(sf::Color(150, 150, 150));
								ico.draw();
								ico.icon.setColor(sf::Color(255, 255, 255));
							}
							if (ico.toolTipBody != "")
							{
								tooltip.first = &ico.icon;
								tooltip.second.setToolTipText(ico.toolTipTitle, ico.toolTipBody);
							}
							if ((parent->windowLClick || parent->requestFocus) && canSwapItems && ico.toolTipBody != "")
							{
								movingItem = true;
								selected = &ico.icon;
								selectedBag = i;
							}
							if ((parent->windowLClick || parent->requestFocus) && !canSwapItems && clickableIcons && ico.toolTipBody != "")
							{
								selected = &ico.icon;
								selected->setPosition(ico.getPosition().x, ico.getPosition().y);
								selectedBag = i;
							}
						}

						else if (mouseInsideIcon(ico.icon) && movingItem && &ico.icon != selected)
							drawMoving(ico.icon, i, ico.toolTipBody);
						else if (mouseInsideIcon(ico.icon) && movingItem)
						{
							ico.icon.setColor(sf::Color(150, 25, 25));
							ico.draw();
							ico.icon.setColor(sf::Color(255, 255, 255));
						}
						else if (!canSwapItems && selected == &ico.icon)
						{
							ico.icon.setColor(sf::Color(25, 230, 140));
							ico.draw();
							ico.icon.setColor(sf::Color(255, 255, 255));
						}
						else
							ico.draw();
						if (movingItem && !mouseInside())
						{
							tooltip.first = NULL;
							equipItem = true;
						}
						else
							equipItem = false;
					}
				}
			}
			bool ScrollBar::getIfMovingItem()
			{
				return movingItem;
			}
			bool ScrollBar::mouseInside()
			{
				if (Engine::GUI.mouseAim.position.x <= parent->window.getTextureRect().width + parent->window.getPosition().x &&
					Engine::GUI.mouseAim.position.x >= parent->window.getTextureRect().left + parent->window.getPosition().x + 60)
					if (Engine::GUI.mouseAim.position.y <= parent->window.getTextureRect().height + parent->window.getPosition().y &&
						Engine::GUI.mouseAim.position.y >= parent->window.getTextureRect().top + parent->window.getPosition().y)
						return true;
				return false;
			}
			void ScrollBar::setScroll(int deltaScroll)
			{
				deltaScroll *= 8;
				if (_draw)
				{
					scrolled -= deltaScroll;
					if (scrolled < 0)
						scrolled = 0;
					else if (scrolled > maxScrolls)
						scrolled = maxScrolls;
				}
			}
			void ScrollBar::drawMoving(sf::Sprite& icon, int index, std::string toolTipBody)
			{
				//TODO: REWORK THIS
				InventoryComponent* icp = NULL;// Engine::Window.focus.gameObject->GetComponent<InventoryComponent>();
				swapBag = index;
				int bagSwapIndex = index;
				int droppedIndex = 0;
				for (size_t it = 0; it < icp->bags.size(); ++it)
					if (icp->bags[it]->size > bagSwapIndex)
					{
						droppedIndex = it;
						break;
					}
					else
						bagSwapIndex -= icp->bags[it]->size;
				if (icp->bags[droppedIndex]->items[bagSwapIndex].first && unequipBag && toolTipBody != "")
				{
					icon.setColor(sf::Color(150, 25, 25));
					Engine::Graphic.view.render.draw(icon);
					icon.setColor(sf::Color(255, 255, 255));
				}
				else
				{
					icon.setColor(sf::Color(25, 150, 25));
					Engine::Graphic.view.render.draw(icon);
					icon.setColor(sf::Color(255, 255, 255));
				}
			}
		}
	}
}