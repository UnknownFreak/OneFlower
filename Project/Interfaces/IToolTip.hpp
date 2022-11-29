#ifndef IToolTip_HPP
#define IToolTip_HPP

#include <utils/common/string.hpp>
#include <glm/vec2.hpp>

namespace Interfaces
{
	class ITooltip
	{
	protected:
		of::common::String toolTip;
		of::common::String toolTipIcon;
	public:
		bool drawToolTip;
		virtual void setToolTip(const of::common::String& string) = 0;
		virtual void setPosition(const glm::vec2& position) = 0;

		// Inherited via Drawable
	};
}

#endif