#ifndef BaseWindow_HPP
#define BaseWindow_HPP

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\VertexArray.hpp>
#include "Addon\Button.hpp"
#include "../Text/Message.hpp"
#include "../../../Vector.h"

namespace GUI
{
	namespace Window
	{
		class BaseWindow
		{
		public:

			BaseWindow(float x, float y, int sizeX, int sizeY, bool resizeable, std::string title);
			virtual ~BaseWindow() = default;

			bool open = false;
			bool focus = false;
			bool requestFocus = false;
			bool drawResizeIcon;
			bool requestClose = false;
			sf::Sprite window;
			Vector2 position;
			sf::VertexArray outline;
			void draw();
			void move();
			void WindowHandle();

			bool checkMouseInside();

			bool windowLClick = false;
			bool windowRClick = false;
		protected:

			int inventoryButtonOffsets = 16;
			bool resizeing = false;
			bool moving = false;

			Addon::Button close;
			Addon::Button resize;

			Vector2 clickOffset;

			Message title;

			double offsetX = 0;
			double offsetY = 0;

			bool MouseInsideTitleBar();

			void checkMouseOffset(double&x, double &y);
			void Imove(double x, double y);
			void Iresize(float x, float y);
		};
	}
}
#endif