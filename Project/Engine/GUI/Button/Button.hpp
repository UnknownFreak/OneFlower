#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../GUIElement/BaseHandler.hpp"
#include <functional>

namespace GUI
{
	class Button : public BaseHandler
	{
	private:

		bool preClick = false;

	protected:
		// Inherited via BaseHandler
		virtual bool mouseDown() override;
		virtual void mouseHold() override;
		virtual void mouseUp() override;
	public:

		Button();
		Button(const Button& copy);
		Button(std::string buttonText, Vector2i size, Vector2 position, BaseHandler* parent);

		unsigned int handle(MessageType msg) override;

		//function that runs when the button is clicked (up)
		std::function<void(void)> click;
		//function that runs when the button is held
		std::function<void(void)> hold;
		//function that runs when the button is preClicked
		std::function<void(void)> preClickfn;


	};

};

#endif