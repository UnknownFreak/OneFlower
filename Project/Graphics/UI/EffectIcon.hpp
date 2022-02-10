#ifndef EffectIcon_HPP
#define EffectIcon_HPP


#include "UIContext.hpp"
#include "PlainToolTip.hpp"

#include <Combat/EffectStack.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>

namespace Graphics::UI
{
	class EffectIcon : public UIContext
	{
		PlainToolTip toolTip;
		Core::Vector2f pos;
		std::shared_ptr<sf::Texture> iconTexture;
		Combat::EffectStack& stack;
		sf::Vertex vertex[4];
		sf::VertexBuffer buf;

	public:
		Core::Vector2f iconSize;

		EffectIcon(const Core::String& icon, Combat::EffectStack& stack);


		void updatePos(const Core::Vector2f& pos);
		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f& mouse) override;
		virtual void readInput() override;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void drawToolTip(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}

#endif