#ifndef WINDOW_HPP 
#define WINDOW_HPP
#include "../GUIElement/ElementBase.hpp"
#include <SFML\Graphics\RenderTarget.hpp>

namespace GUI
{
	class Window : public ElementBase, public sf::Drawable
	{

		sf::Sprite backgroundSprite;

	protected:
		// Inherited via ElementBase
		virtual void mouseHandle() override;
	public:
		Window();


		// Inherited via Drawable
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
		unsigned int handle(ElementBase& guiRef, ElementMessage msg);
	};
}

#endif
