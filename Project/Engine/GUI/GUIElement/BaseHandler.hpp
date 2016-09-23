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
		SetFocus,
		RemoveFocus,
		Close,
		Open,
		Click,
		Move,
		SetMoveCoord,
		ForceStopMove,
		Resize,
		NotifyParent,
		Enable,
		Disable,
		Hide,
		Show
	};

	class BaseHandler : public sf::Drawable
	{

		static std::vector<BaseHandler*> elements;
		// swap the vector to a deque
		static std::map<const BaseHandler*, std::deque<MessageType>> messages;

		//first element is the back, last element is the front
		//parse elements from last to first
		//draw elements from first to last
		static std::vector<BaseHandler*> zOrder;

		static BaseHandler* focused;

	protected:
		static bool mouseUsed;
		
		sf::Keyboard::Key shorcutKey;

		//Does this have focus.
		bool focus = false;
		BaseHandler* parentWindow = NULL;
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
		//ActualPosition of element
		Vector2 actualPos;
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
		BaseHandler(const BaseHandler& copy);
		virtual ~BaseHandler();

	public:
		
		void setPosition(Vector2 newPos);

		const Vector2i getSize();

		BaseHandler* getBaseHandler();

		void sendMessage(const BaseHandler& base, MessageType msg);
		
		bool isPointInside(Vector2& point);

		void addComponent(BaseHandler* base);

		// same as using sendMessage(const BaseHandler& base, GUI::Enable);
		// enabled controls can recieve input and focus when clicked
		void enable();

		// same as using sendMessage(const BaseHandler& base, GUI::Disable);
		// disabled controls can not recieve input and focus when clicked
		// controls can still recieve messages trough the sendMessage function.
		void disable();

		// Inherited via Drawable
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

		// static function that will draw the windows in correct order.
		static void draw();

		// returns the type of the handler
		Type getType();
		// gets a value that indicates if the handler has focus or not.
		bool hasFocus();

	};
}

#endif
