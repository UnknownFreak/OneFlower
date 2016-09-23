#ifndef WINDOW_HPP 
#define WINDOW_HPP
#include "../GUIElement/BaseHandler.hpp"
#include "../Button/Button.hpp"
namespace GUI
{
	class Window : public BaseHandler
	{
		bool moving = false;

		bool isPointInsideTitle(Vector2& pos);

		unsigned int titleHeight = 20;

		Button close;
		Button resizeGrip;
		void closeClick();
	protected:
		// Inherited via BaseHandler
		virtual void mouseHandle() override;
	public:
		Window();

		unsigned int handle(MessageType msg) override;
		void enableResizeMode();
		void disableResizeMode();
	};
}

#endif
