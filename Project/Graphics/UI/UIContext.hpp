#ifndef UICONTEXT_HPP
#define UICONTEXT_HPP

#include <swizzle/core/Input.hpp>

#include <utils/common/string.hpp>
#include <glm/vec2.hpp>
#include <imgui/imgui.h>

namespace Graphics::UI
{
	enum class Rel
	{
		Left,
		Right,
	};
	class UIContext
	{
		bool noKeybind = false;
		swizzle::input::Keys toggleKey;

		void registerKeybind();

	protected:
		bool mouseInside(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& mouse) const;
		bool visible = true;

	public:
		float x, y;
		of::common::String uiName;

		UIContext(const swizzle::input::Keys& toggleKey, const of::common::String& uiName, const bool& noKeybind);
		virtual void onMouseHover(const glm::vec2& mouse) = 0;
		virtual ~UIContext() {};
		virtual void readInput() = 0;
		virtual void update() {};

		void toggleVisible();
		const bool& isVisible() const;

		virtual void render() = 0;

	};
}
#endif