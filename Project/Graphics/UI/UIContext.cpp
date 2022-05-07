#include "UIContext.hpp"


#include <Module/EngineModuleManager.hpp>
#include <Input/InputHandler.hpp>
namespace Graphics::UI
{
	UIContext::UIContext(const swizzle::input::Keys& toggleKey, const Core::String& uiName, const bool& noKeybind) : toggleKey(toggleKey), uiName(uiName), noKeybind(noKeybind)
	{
		registerKeybind();
	}

	void UIContext::registerKeybind()
	{
		if (noKeybind)
			return;
		Input::InputHandler& ih = Engine::GetModule<Input::InputHandler>();
		ih.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp(uiName, [&](bool, swizzle::input::Keys, const float&) { toggleVisible(); }, false), toggleKey, Enums::Input::Action::Press);
	}

	bool UIContext::mouseInside(const Core::Vector2f& pos, const Core::Vector2f& size, const Core::Vector2f& mouse) const
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
