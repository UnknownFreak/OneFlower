//#include "Button.hpp"
//#include "../../../Component/HitboxComponent.hpp"
//#include "../../../Component/RenderComponent.h"
//#include <string>
//#include "../../../../Engine.hpp"
//
//namespace GUI
//{
//	namespace Windows
//	{
//		namespace Addon
//		{
//			Button::Button() : position(0, 0), name(""), hover(125, 125, 125), toolTip("None", "ToolTipIcon.png"), showToolTip(false), text(*Engine::Graphic.font.requestFont("arial.ttf"))
//			{
//				text.setSize(12);
//				icon.setTexture(*Engine::Graphic.requestTexture("ButtonTest.png"));
//				icon.setTextureRect(sf::IntRect(0, 0, 64, 64));
//				setPosition(position);
//			}
//
//			//Button::Button(std::string _icon) : position(0, 0), toolTip("None", "ToolTipIcon.png"), showToolTip(false), text(*Engine::Graphic.font.requestFont("arial.ttf"))
//			//{
//			//	text.setSize(12);
//			//	icon.setTexture(*Engine::Graphic.requestTexture(_icon));
//			//	icon.setTextureRect(sf::IntRect(0, 0, 64, 64));
//			//	setPosition(position);
//			//}
//			
//			Button::Button(std::string icon, int sizeX, int sizeY, double posX, double posY, sf::Color hover, bool showToolTip) : name(""), icon(*Engine::Graphic.requestTexture(icon), sf::IntRect(0, 0, sizeX, sizeY)), position(posX, posY), hover(hover), showToolTip(showToolTip), toolTip("", "", "ToolTipIcon.png"), text(*Engine::Graphic.font.requestFont("arial.ttf"))
//			{
//				text.setSize(12);
//				setPosition(position);
//			}
//			
//			//Button::Button(std::string icon, int sizeX, int sizeY, double posX, double posY, std::string toolTip, sf::Color hover) : name(""), icon(*Engine::Graphic.requestTexture(icon), sf::IntRect(0, 0, sizeX, sizeY)), position(posX, posY), hover(hover), showToolTip(true), toolTip("", toolTip, "ToolTipIcon.png"), text(*Engine::Graphic.font.requestFont("arial.ttf"))
//			//{
//			//	text.setSize(12);
//			//	setPosition(position);
//			//}
//			Button::Button(std::string icon, sf::IntRect rect, double posX, double posY, std::string toolTip, sf::Color hover) : 
//				name(""), icon(*Engine::Graphic.requestTexture(icon), rect), position(posX, posY), hover(hover), showToolTip(true), 
//				toolTip("", toolTip, "ToolTipIcon.png"), text(*Engine::Graphic.font.requestFont("arial.ttf"))
//			{
//				if (toolTip == "")
//					showToolTip = false;
//				text.setSize(12);
//				setPosition(position);
//			}
//			Button::Button(std::string iconName, std::string itext, sf::IntRect rect, double posX, double posY, TextAlignment textpos, std::string toolTip, sf::Color hover) :
//				icon(*Engine::Graphic.requestTexture(iconName), rect), position(posX, posY), hover(hover), showToolTip(true),
//				toolTip("", toolTip, "ToolTipIcon.png"), text(*Engine::Graphic.font.requestFont("arial.ttf")), textpos(textpos)
//			{
//				if (toolTip == "")
//					showToolTip = false;
//				text.setSize(12);
//				text = itext;
//				setPosition(position);
//			}
//
//			void Button::setIcon(std::string str)
//			{
//				icon.setTexture(*Engine::Graphic.requestTexture(str));
//			}
//
//			void Button::setToolTip(std::string toolTipText)
//			{
//				toolTip.setToolTipText(toolTipText);
//			}
//
//			bool Button::onHover()
//			{
//				if (Engine::GUI.mouseAim.position.x <= icon.getLocalBounds().width + position.x && Engine::GUI.mouseAim.position.x >= icon.getLocalBounds().left + position.x)
//					if (Engine::GUI.mouseAim.position.y <= icon.getLocalBounds().height + position.y && Engine::GUI.mouseAim.position.y >= icon.getLocalBounds().top + position.y)
//					{
//						icon.setColor(hover);
//						if (showToolTip)
//						{
//							toolTip.setPosition(Engine::GUI.mouseAim.position.x, Engine::GUI.mouseAim.position.y);
//							toolTip.draw();
//						}
//						return true;
//					}
//				icon.setColor(sf::Color(255, 255, 255));
//				return false;
//			}
//			void Button::setPosition(double x, double y)
//			{
//				position.x = x;
//				position.y = y;
//				icon.setPosition(x, y);
//				if (textpos == TextAlignment::Left)
//					text.setPosition(x, y +(icon.getTextureRect().height/2) - (int) (text.entireString.getLocalBounds().height));
//				else if (textpos == TextAlignment::Right)
//					text.setPosition(x + icon.getTextureRect().width - text.entireString.getLocalBounds().width,
//					y + (icon.getTextureRect().height / 2) - (int)(text.entireString.getLocalBounds().height) );
//				else
//					text.setPosition(x + (icon.getTextureRect().width / 2) - (int)(text.entireString.getLocalBounds().width / 2), 
//					y + (icon.getTextureRect().height / 2) - (int)(text.entireString.getLocalBounds().height ));
//			}
//			void Button::setPosition(Vector2 pos)
//			{
//				position = pos;
//				icon.setPosition(pos.x, pos.y);
//				if (textpos == TextAlignment::Left)
//					text.setPosition(pos.x, pos.y + (icon.getTextureRect().height / 2) - (int)(text.entireString.getLocalBounds().height ));
//				else if (textpos == TextAlignment::Right)
//					text.setPosition(pos.x + icon.getTextureRect().width - text.entireString.getLocalBounds().width,
//					pos.y + (icon.getTextureRect().height / 2) - (int)(text.entireString.getLocalBounds().height ));
//				else
//					text.setPosition(pos.x + (icon.getTextureRect().width / 2) - (int)(text.entireString.getLocalBounds().width /2), 
//					pos.y + (icon.getTextureRect().height / 2) - (int)(text.entireString.getLocalBounds().height ));
//			}
//
//			/*void Button::ActionSlotClick()
//			{
//				Engine::GUI.setActiveSkill(name);
//			}*/
//
//			void Button::draw()
//			{
//				Engine::Graphic.view.render.draw(icon);
//				text.draw();
//			}
//			Vector2 Button::getPosition()
//			{
//				return position;
//			}
//			void Button::setName(std::string name)
//			{
//				this->name = name;
//				text = name;
//			}
//			std::string Button::getName()
//			{
//				return name;
//			}
//		}
//	}
//}