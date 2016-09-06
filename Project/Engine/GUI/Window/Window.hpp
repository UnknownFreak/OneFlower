#ifndef WINDOW_HPP 
#define WINDOW_HPP
#include "../GUIElement/ElementBase.hpp"

namespace GUI
{
	class Window : public ElementBase
	{
		bool moving = false;

		bool isPointInsideTitle(Vector2& pos);

	protected:
		// Inherited via ElementBase
		virtual void mouseHandle() override;
	public:
		Window();

		unsigned int handle(MessageType msg) override;
	};
}

#endif
