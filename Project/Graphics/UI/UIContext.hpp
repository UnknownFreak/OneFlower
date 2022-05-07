#ifndef UICONTEXT_HPP
#define UICONTEXT_HPP

#include <swizzle/core/Input.hpp>

#include <Helpers/String.hpp>
#include <Helpers/Vector.hpp>
#include <imgui/imgui.h>

namespace Graphics::UI
{
	class UIContext
	{
		bool noKeybind = false;
		swizzle::input::Keys toggleKey;

		void registerKeybind();

	protected:
		bool mouseInside(const Core::Vector2f& pos, const Core::Vector2f& size, const Core::Vector2f& mouse) const;
		bool visible = true;

	public:
		Core::String uiName;

		UIContext(const swizzle::input::Keys& toggleKey, const Core::String& uiName, const bool& noKeybind);
		virtual void onMouseHover(const Core::Vector2f& mouse) = 0;
		virtual ~UIContext() {};
		virtual void readInput() = 0;
		virtual void update() {};

		void toggleVisible();
		const bool& isVisible() const;

		virtual void render() = 0;

	};
}
#endif