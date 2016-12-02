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
		void resizeDrag();
		void resizPreClick();
	protected:
		// Inherited via BaseHandler
		virtual bool mouseDown() override;
		virtual void mouseHold() override;
		virtual void mouseUp() override;
	public:
		Window();

		unsigned int handle(MessageType msg) override;
		void enableResizeMode();
		void disableResizeMode();

		// Inherited via BaseHandler
	};
}

#endif
