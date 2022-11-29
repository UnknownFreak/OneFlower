#include "PlainToolTip.hpp"

Graphics::UI::PlainToolTip::PlainToolTip(): toolTipText()
{
	drawToolTip = false;
	
	setPosition({ 0,0 });
}

void Graphics::UI::PlainToolTip::setToolTip(const of::common::String& string)
{
	toolTip = string;
	toolTipText = toolTip;
}

Graphics::UI::PlainToolTip::PlainToolTip(const PlainToolTip& copy) : PlainToolTip()
{
	setToolTip(copy.toolTip);
}

void Graphics::UI::PlainToolTip::setPosition(const glm::vec2& )
{

}
