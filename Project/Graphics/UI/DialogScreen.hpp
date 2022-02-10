#ifndef DialogScreen_HPP
#define DialogScreen_HPP

#include "UIContext.hpp"

#include <Helpers/Enum/InteractionOption.hpp>

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class Dialog;
namespace Graphics::UI
{
	class DialogScreen : public UIContext
	{
		sf::Font f;
		sf::Text t;

		Dialog* dialog = nullptr;
		std::shared_ptr<sf::Texture> texture;
		sf::VertexArray dialogFrame;
	public:
		DialogScreen();
		DialogScreen(Dialog* dialog);
		~DialogScreen();
		// Inherited via UIContext

		void toggleVisible();
		virtual void readInput() override;
		void readInput(const Enums::InteractionOption& navigation);
		void show(Dialog* dialog);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f& mouse) override;

	};
}


#endif