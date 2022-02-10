#ifndef UICONTEXT_HPP
#define UICONTEXT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <Helpers/String.hpp>
#include <Helpers/Vector.hpp>

namespace Graphics::UI
{
	class UIContext : public sf::Drawable
	{
		bool noKeybind = false;
		sf::Keyboard::Key toggleKey;

		void registerKeybind();

	protected:
		bool mouseInside(const Core::Vector2f& pos, const Core::Vector2f& size, const Core::Vector2f& mouse) const;
		bool visible = true;

	public:
		Core::String uiName;

		UIContext(const sf::Keyboard::Key& toggleKey, const Core::String& uiName, const bool& noKeybind);
		virtual void onMouseHover(const Core::Vector2f& mouse) = 0;
		virtual ~UIContext() {};
		virtual void readInput() = 0;
		virtual void update() {};

		void toggleVisible();
		const bool& isVisible() const;

		// Inherited via Drawable
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}
#endif