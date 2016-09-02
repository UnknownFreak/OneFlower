#ifndef GUIELEMENTBASE_HPP
#define GUIELEMENTBASE_HPP

#include "../../../Vector.h"
#include <SFML\Window\Keyboard.hpp>
#include <vector>
#include <map>

namespace GUI
{
	enum Element
	{
		Text,
		FormatedText,
		Button,
		Window,
		Panel,
		ScrollBar,
		Image,
		TextField,
		Menu,
		MenuItem,
		ContextMenu,
	};
	enum MouseState
	{
		Down,
		Hold,
		Up,
		None
	};
	enum ElementMessage
	{
		RequestFocus,
		Close,
		Open,
		Click,
		Move,
		Resize,
		NotifyParent,
		Enable,
		Disable,
	};

	class ElementBase
	{

		static std::vector<ElementBase*> elements;
		static std::map<const ElementBase*, std::vector<ElementMessage>> messages;

	protected:
		
		sf::Keyboard::Key shorcutKey;

		//Does this have focus.
		bool focus = false;
		unsigned int zBuffer=0;
		//Static variable to check element requesting focus, has to be of type window else this will be set to null.
		//static ElementBase* const requestingFocus = NULL;

		//Is the element visible (true by default)
		bool visible = true;
		//Can the element be interacted with (true by default)
		bool enabled = true;

		//Position of the element.
		Vector2 pos;
		//Size of the element.
		Vector2 size;
		//LastMousePos;
		Vector2 lastMousePos;
		//Parent element, can be something.
		ElementBase* parent;
		//Added elements;
		std::vector<ElementBase*> components;
		
		//Element type.
		Element guiType;
		//Mouse state for the gui element
		MouseState mouseState = None;


		//Handle function.
		virtual unsigned int handle(ElementBase& guiRef, ElementMessage msg);
		//Mouse function for element, to handle the mouse events.
		virtual void mouseHandle() = 0;

		inline ElementBase(Element type) : guiType(type)
		{
			messages.insert({ this, {} });
			elements.push_back(this);
		};

		inline virtual ~ElementBase()
		{ 
			elements.erase(std::find(elements.begin(), elements.end(),this)); 
			messages.erase(this);
		};
	public:

		inline void sendMessage(const ElementBase& base, ElementMessage msg)
		{
			messages[&base].push_back(msg);
		};
		
		bool isPointInside(Vector2 point);

		void addElement(ElementBase* base);

	};
}

#endif
