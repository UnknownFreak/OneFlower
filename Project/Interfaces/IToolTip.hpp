#ifndef IToolTip_HPP
#define IToolTip_HPP

#include <Helpers/String.hpp>
#include <glm/vec2.hpp>

namespace Interfaces
{
	class ITooltip
	{
	protected:
		Core::String toolTip;
		Core::String toolTipIcon;
	public:
		bool drawToolTip;
		virtual void setToolTip(const Core::String& string) = 0;
		virtual void setPosition(const glm::vec2& position) = 0;

		// Inherited via Drawable
	};
}

#endif