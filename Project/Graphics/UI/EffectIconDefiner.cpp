#include "EffectIcon.hpp"

#include <File/Resource/TextureLoader.hpp>

Graphics::UI::EffectIcon::EffectIcon(const Core::String& icon, Combat::EffectStack& stack) : UIContext(sf::Keyboard::Key::Unknown, "EffectIcon", true),
buf(sf::PrimitiveType::Quads, sf::VertexBuffer::Usage::Static), iconSize{32.f, 32.f}, stack(stack),
iconTexture(Engine::GetModule<TextureLoader>().requestTexture(icon, Globals::uiTexturePath))
{
	vertex[0].texCoords = { 0.f ,0.f };
	vertex[1].texCoords = { 0.f, 64.f };
	vertex[2].texCoords = { 64.f, 64.f};
	vertex[3].texCoords = { 64.f, 0.f };
	buf.create(4);
	updatePos({ 0,0 });
}

//Graphics::UI::EffectIcon::EffectIcon() : EffectIcon("", nullptr)
//{
//
//}

void Graphics::UI::EffectIcon::updatePos(const Core::Vector2f& newPos)
{
	pos = newPos;
	vertex[0].position = { pos.x, pos.y };
	vertex[1].position = { pos.x, pos.y + iconSize.y };
	vertex[2].position = { pos.x + iconSize.x, pos.y + iconSize.y};
	vertex[3].position = { pos.x + iconSize.x, pos.y };
	buf.update(vertex);
	toolTip.setToolTip("Aasdad");
}

void Graphics::UI::EffectIcon::onMouseHover(const Core::Vector2f& mouse)
{
	if (toolTip.drawToolTip = visible && mouseInside(pos, iconSize, mouse))
	{
		toolTip.setPosition(mouse);
	}
}

void Graphics::UI::EffectIcon::readInput()
{
}

void Graphics::UI::EffectIcon::draw(sf::RenderTarget& target, sf::RenderStates ) const
{
	if (!visible)
		return;
	target.draw(buf, iconTexture.get());
}

void Graphics::UI::EffectIcon::drawToolTip(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(toolTip, states);
}
