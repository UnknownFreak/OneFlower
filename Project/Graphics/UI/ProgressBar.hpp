#ifndef ProgressBar_HPP
#define ProgressBar_HPP

#include "UIContext.hpp"
#include "PlainToolTip.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <SFML/Graphics/Text.hpp>
namespace Graphics::UI
{
	class ProgressBar : public UIContext
	{
		PlainToolTip tooltip;
		sf::Font font;
		float x, y, sizeX, sizeY;
		float extensionTop, extensionBottom;
		float textOffsetX, textOffsetY;
		float maxVal, currentVal;
		sf::Text valueText;
		bool drawText;
	protected:
		sf::Vertex points[8];
		sf::VertexBuffer theBar;

	public:
		ProgressBar(const float& x, const float& y, const float& sizeX, const float& sizeY, const float& max, const float& current, const sf::Color& color,
			const float& extensionTop, const float& extensionBottom, const bool& drawText=true, const float& textOffsetX=0.f, const float& textOffsetY=0.f);

		// Inherited via UIContext
		virtual void readInput() override;
		void setNewMax(const float& newMax);
		void update(const float& currentVal);
		virtual void update() override;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void drawToolTip(sf::RenderTarget& target, sf::RenderStates states) const;

		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f& mouse) override;
	};
}

#endif