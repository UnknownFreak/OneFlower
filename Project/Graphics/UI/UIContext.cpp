#include "UIContext.hpp"

namespace Graphics::UI
{
	UIContext::UIContext(const swizzle::input::Keys& toggleKey, const of::common::String& uiName, const bool& noKeybind) : toggleKey(toggleKey), uiName(uiName), noKeybind(noKeybind)
	{
		registerKeybind();
	}

	void UIContext::registerKeybind()
	{
		if (noKeybind)
			return;
	}

	bool UIContext::mouseInside(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& mouse) const
	{
		return mouse.x > pos.x && mouse.x < pos.x + size.x && 
			mouse.y > pos.y && mouse.y < pos.y + size.y;
	}

	void UIContext::toggleVisible()
	{
		visible = !visible;
	}

	const bool& UIContext::isVisible() const
	{
		return visible;
	}
}
