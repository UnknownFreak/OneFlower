#pragma once
#include <Interfaces/IToolTip.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>

namespace Graphics::UI
{
	class PlainToolTip : public Interfaces::ITooltip
	{
		sf::Vertex toolTipFrame[4];
		sf::VertexBuffer buf;
		sf::Font font;
		sf::Text toolTipText;
	public:

		PlainToolTip();
		PlainToolTip(const PlainToolTip& copy);
		
		virtual void setToolTip(const Core::String& string) override;
		virtual void setPosition(const Core::Vector2f& string) override;

		// Inherited via ITooltip
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}
