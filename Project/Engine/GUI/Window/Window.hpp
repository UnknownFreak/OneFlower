#ifndef WINDOW_HPP 
#define WINDOW_HPP
#include "../GUIElement/BaseHandler.hpp"

namespace GUI
{
	class Window : public BaseHandler
	{
		bool moving = false;

		bool isPointInsideTitle(Vector2& pos);

		unsigned int titleHeight = 20;

	protected:
		// Inherited via BaseHandler
		virtual void mouseHandle() override;
	public:
		Window();

		unsigned int handle(MessageType msg) override;
	};
}

#endif
