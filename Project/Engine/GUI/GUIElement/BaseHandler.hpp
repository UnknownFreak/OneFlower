#ifndef GUIBASEHANDLER_HPP
#define GUIBASEHANDLER_HPP

#include "../../../Engine.hpp"
#include "../../../Vector.h"
#include <SFML\Window\Keyboard.hpp>
#include <vector>
#include <map>
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Sprite.hpp>

namespace GUI
{
	enum Type
	{
		e_Text,
		e_FormatedText,
		e_Button,
		e_Window,
		e_Panel,
		e_ScrollBar,
		e_Image,
		e_TextField,
		e_Menu,
		e_MenuItem,
		e_ContextMenu,
		e_ProgressBar,
	};
	enum MouseState
	{
		None = 0,
		Down = 1 << 0,
		Hold = 1 << 1,
		Up = 1 << 2,
	};
	enum MessageType
	{
		RequestFocus,
		Close,
		Open,
		Click,
		Move,
		SetMoveCoord,
		Resize,
		NotifyParent,
		Enable,
		Disable,
	};

	class BaseHandler : public sf::Drawable
	{

		static std::vector<BaseHandler*> elements;
		// swap the vector to a deque
		static std::map<const BaseHandler*, std::vector<MessageType>> messages;

		//not used at the moment.
		std::vector<BaseHandler*> zOrder;

	protected:
		
		sf::Keyboard::Key shorcutKey;

		//Does this have focus.
		bool focus = false;
		//unsigned int zOrder = 0;

		//Is the element visible (true by default)
		bool visible = true;
		//Can the element be interacted with (true by default)
		bool enabled = true;

		//Can the element be resized, using the reszie message
		bool resizeAble = true;
		//Can the element be moved, using the move message
		bool moveAble = true;

		//Position of the element.
		Vector2 pos;
		//OffsetPos for click and drag (default (0,0))
		Vector2 Offset;

		//Size of the element.
		Vector2i size;
		//static reference towards the mouse position;
		static Vector2& mousePos;
		//Parent element, can be something.
		BaseHandler* parent;
		//Added elements;
		std::vector<BaseHandler*> components;
		
		//Element type.
		Type guiType;
		//Mouse state for the gui element
		MouseState mouseState = None;

		//sprite for the element.
		sf::Sprite sprite;

		Vector2i minResizeSize = Vector2i(0, 0);

		//Handle function. Can be overriden to add custom user functions.
		virtual unsigned int handle(MessageType msg);
		//Mouse function for element, to handle the mouse events.
		virtual void mouseHandle() = 0;

		BaseHandler(Type type);
		virtual ~BaseHandler();

	public:

		void sendMessage(const BaseHandler& base, MessageType msg);
		
		bool isPointInside(Vector2& point);

		void addElement(BaseHandler* base);

		// same as using sendMessage(const BaseHandler& base, GUI::Enable);
		// enabled controls can recieve input and focus when clicked
		void enable();
		// same as using sendMessage(const BaseHandler& base, GUI::Disable);
		// disabled controls can not recieve input and focus when clicked
		// controls can still recieve messages trough the sendMessage function.
		void disable();

		// Inherited via Drawable
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	};
}

#endif
