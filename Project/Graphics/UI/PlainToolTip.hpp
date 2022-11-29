#pragma once
#include <Interfaces/IToolTip.hpp>


namespace Graphics::UI
{
	class PlainToolTip : public Interfaces::ITooltip
	{
		of::common::String toolTipText;
	public:

		PlainToolTip();
		PlainToolTip(const PlainToolTip& copy);
		
		virtual void setToolTip(const of::common::String& string) override;
		virtual void setPosition(const glm::vec2& string) override;

	};
}
