#ifndef ButtonObject_HPP
#define ButtonObject_HPP
//#include "../../../Component/HitboxComponent.hpp"
//#include <SFML\Graphics\Sprite.hpp>
//#include "../../../../Vector.h"
//#include "../../ToolTip.hpp"
//#include "../../Text/Message.hpp"
//#include <functional>
//
//namespace GUI
//{
//	namespace Windows
//	{
//		namespace Addon
//		{
//			class Button
//			{
//			public:
//				enum TextAlignment
//				{
//					Left,
//					Center,
//					Right,
//				};
//			private:
//				
//				enum TextAlignment textpos = Left;
//
//				bool showToolTip;
//
//				sf::Color hover;
//				std::string name;
//				ToolTip toolTip;
//				Vector2 position;
//
//				Message text;
//			public:
//
//				sf::Sprite icon;
//				Button();
//				//Button(std::string icon);
//				Button(std::string icon, int sizeX, int sizeY, double posX, double posY, sf::Color hover = sf::Color(125, 125, 125), bool showToolTip = false);
//				//Button(std::string icon, int sizeX, int sizeY, double posX, double posY, std::string toolTip, sf::Color hover = sf::Color(125, 125, 125));
//				Button(std::string icon, sf::IntRect rect, double posX, double posY, std::string toolTip, sf::Color hover = sf::Color(125, 125, 125));
//				
//				Button(std::string iconName, std::string buttonText, sf::IntRect rect, double posX, double posY, TextAlignment textpos = Left, std::string toolTip = "", sf::Color hover = sf::Color(125,125,125));
//				
//			
//				
//				//~Button();
//				void setToolTip(std::string tip);
//				void setIcon(std::string ico);
//				void setPosition(double x, double y);
//				void setPosition(Vector2 pos);
//				void setName(std::string name);
//				std::string getName();
//				Vector2 getPosition();
//				bool onHover();
//
//				void draw();
//
//				std::function<void(void)> onClick;
//			};
//		}
//	}
//}
#endif