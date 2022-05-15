#ifndef DialogScreen_HPP
#define DialogScreen_HPP

#include "UIContext.hpp"

#include <Helpers/Enum/InteractionOption.hpp>

class Dialog;
namespace Graphics::UI
{
	class DialogScreen : public UIContext
	{
		Core::String t;

		Dialog* dialog = nullptr;
		//std::shared_ptr<sf::Texture> texture;
		//sf::VertexArray dialogFrame;
	public:
		DialogScreen();
		DialogScreen(Dialog* dialog);
		~DialogScreen();
		// Inherited via UIContext

		void toggleVisible();
		virtual void readInput() override;
		void readInput(const Enums::InteractionOption& navigation);
		void show(Dialog* dialog);
		virtual void render() override;


		// Inherited via UIContext
		virtual void onMouseHover(const glm::vec2& mouse) override;

	};
}


#endif