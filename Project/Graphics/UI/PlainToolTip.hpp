#pragma once
#include <Interfaces/IToolTip.hpp>


namespace Graphics::UI
{
	class PlainToolTip : public Interfaces::ITooltip
	{
		Core::String toolTipText;
	public:

		PlainToolTip();
		PlainToolTip(const PlainToolTip& copy);
		
		virtual void setToolTip(const Core::String& string) override;
		virtual void setPosition(const glm::vec2& string) override;

	};
}
