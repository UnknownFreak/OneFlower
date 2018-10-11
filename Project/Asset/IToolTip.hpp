#ifndef IToolTip_HPP
#define IToolTip_HPP

#include <SFML/Graphics/Drawable.hpp>

#include <Core/String.hpp>

class ITooltip : public sf::Drawable
{

	Core::String toolTip;
	Core::String toolTipIcon;
	
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;
};

#endif