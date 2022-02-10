#ifndef BUILDINFO_HPP
#define BUILDINFO_HPP

#include "UIContext.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Helpers/String.hpp>

namespace Graphics::UI
{

	class BuildInfo : public Graphics::UI::UIContext
	{
		sf::Font f;
		sf::Text t;

		const Core::String text;
	public:
		BuildInfo(const Core::String info = "Null", float x = 0.f, float y = 0.f) : UIContext(sf::Keyboard::F3, info, false) {
			f.loadFromFile("C:/Windows/Fonts/arial.ttf");
			t.setFont(f);
			t.setCharacterSize(12);
			t.setPosition(x, y);

			t.setString(info);

		}

		BuildInfo(const BuildInfo& copy) : BuildInfo(copy.text, copy.t.getPosition().x, copy.t.getPosition().y)
		{
		}
		
		// Inherited via Drawable
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			if (!visible)
				return;
			target.draw(t, states);
		}

		// Inherited via UIContext
		virtual void readInput() override {};

		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f&) override {};
	};
}

#endif 
