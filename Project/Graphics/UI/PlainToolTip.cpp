#include "PlainToolTip.hpp"

void Graphics::UI::PlainToolTip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (drawToolTip)
	{
		target.draw(buf, states);
		target.draw(toolTipText, states);
	}
}

Graphics::UI::PlainToolTip::PlainToolTip(): buf(sf::PrimitiveType::Quads, sf::VertexBuffer::Usage::Dynamic), toolTipText()
{
	drawToolTip = false;
	buf.create(4);
	if (!font.loadFromFile(Core::SystemFonts + "arial.ttf"))
	{
		auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Graphics::UI::PlainToolTip");
		logger.Error("Failed to load font for whatever reason...");

	}
	toolTipText.setFont(font);
	toolTipText.setCharacterSize(12);
	toolTipFrame[0].color = sf::Color(0, 0, 0, 180);
	toolTipFrame[1].color = sf::Color(0, 0, 0, 180);
	toolTipFrame[2].color = sf::Color(0, 0, 0, 180);
	toolTipFrame[3].color = sf::Color(0, 0, 0, 180);
	setPosition({ 0,0 });
}

void Graphics::UI::PlainToolTip::setToolTip(const Core::String& string)
{
	toolTip = string;
	toolTipText.setString(toolTip);
}

Graphics::UI::PlainToolTip::PlainToolTip(const PlainToolTip& copy) : PlainToolTip()
{
	setToolTip(copy.toolTip);
}

void Graphics::UI::PlainToolTip::setPosition(const Core::Vector2f& position)
{
	toolTipText.setPosition({ position.x + 10, position.y + 1});
	auto lb = toolTipText.getLocalBounds();
	toolTipFrame[0].position = { position.x, position.y };
	toolTipFrame[1].position = { position.x, position.y + lb.height + 10};
	toolTipFrame[2].position = { position.x + 20 + lb.width, position.y + lb.height + 10};
	toolTipFrame[3].position = { position.x + 20 + lb.width, position.y };
	buf.update(toolTipFrame);
}
