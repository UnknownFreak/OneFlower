#include "ProgressBar.hpp"
#include <Helpers/FloatingPointConversionHelper.hpp>


Graphics::UI::ProgressBar::ProgressBar(const float& x, const float& y, const float& sizeX, const float& sizeY, const float& maxVal, const float& currentVal, const sf::Color& color,
	const float& extensionTop, const float& extensionBottom, const bool& drawText, const float& textOffsetX, const float& textOffsetY) :
	x(x), y(y), sizeX(sizeX), sizeY(sizeY), maxVal(maxVal), currentVal(currentVal), UIContext(sf::Keyboard::Key::Unknown, "ProgressBar", true),
	theBar(sf::PrimitiveType::Quads, sf::VertexBuffer::Dynamic), extensionBottom(extensionBottom), extensionTop(extensionTop), drawText(drawText), textOffsetX(textOffsetX), textOffsetY(textOffsetY)
{
	font.loadFromFile(Core::SystemFonts + "arial.ttf");
	valueText.setFont(font);
	valueText.setCharacterSize(13);

	auto lb = valueText.getLocalBounds();

	valueText.setOrigin(lb.left, lb.top);

	points[0].position = { x, y };
	points[1].position = { x, y + sizeY + 1.f};
	points[2].position = { x + sizeX + extensionBottom, y + sizeY + 1.f };
	points[3].position = { x + sizeX + extensionTop, y };
	points[0].color = sf::Color::Black;
	points[1].color = sf::Color::Black;
	points[2].color = sf::Color::Black;
	points[3].color = sf::Color::Black;

	setNewMax(maxVal);

	points[4].color = color;
	points[5].color = color;
	points[6].color = color;
	points[7].color = color;

	theBar.create(8);
	theBar.update(points);
}

void Graphics::UI::ProgressBar::readInput()
{
}

void Graphics::UI::ProgressBar::setNewMax(const float& newMax)
{
	maxVal = newMax;
	update();
}

void Graphics::UI::ProgressBar::update(const float& newVal)
{
	currentVal = newVal;
	valueText.setString(Core::to_string_with_precision(currentVal, 0));
	update();
}

void Graphics::UI::ProgressBar::update()
{
	auto frac = currentVal / maxVal;
	if (frac > 1.f)
		frac = 1.f;
	if (frac < 0.f)
		frac = 0.f;
	points[4].position = { x + 1.f , y + 1.f};
	points[5].position = { x + 1.f , y + sizeY};
	points[6].position = { x + ((sizeX + extensionBottom) * frac) , y + sizeY };
	points[7].position = { x + ((sizeX + extensionTop) * frac) , y + 1.f};
	theBar.update(points);
	if (drawText)
	{
		auto lb = valueText.getLocalBounds();
		valueText.setPosition(std::floor(x + textOffsetX) , std::floor(y + textOffsetY));
	}
	tooltip.setToolTip(Core::to_string_with_precision(currentVal, 0) + "/" + Core::to_string_with_precision(maxVal, 0));
}

void Graphics::UI::ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(theBar, states);
	if (drawText)
		target.draw(valueText, states);
}

void Graphics::UI::ProgressBar::drawToolTip(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(tooltip, states);
}

void Graphics::UI::ProgressBar::onMouseHover(const Core::Vector2f& mouse)
{
	if (tooltip.drawToolTip = visible && mouseInside({ x,y }, { sizeX + extensionTop, sizeY }, mouse))
	{
		tooltip.setPosition(mouse);
	}
}
