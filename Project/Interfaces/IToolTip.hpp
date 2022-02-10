#ifndef IToolTip_HPP
#define IToolTip_HPP

#include <SFML/Graphics/Drawable.hpp>

#include <Helpers/String.hpp>
#include <Helpers/Vector.hpp>

namespace Interfaces
{
	class ITooltip : public sf::Drawable
	{
	protected:
		Core::String toolTip;
		Core::String toolTipIcon;
	public:
		bool drawToolTip;
		virtual void setToolTip(const Core::String& string) = 0;
		virtual void setPosition(const Core::Vector2f& position) = 0;

		// Inherited via Drawable
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;
	};
}

#endif