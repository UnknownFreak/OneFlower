#include "EffectIcon.hpp"

#include <module/resource/TextureLoader.hpp>

Graphics::UI::EffectIcon::EffectIcon(const of::common::String& icon, of::combat::EffectStack& stack) : UIContext(swizzle::input::Keys::KeyNone, "EffectIcon", true),
iconSize{32.f, 32.f}, stack(stack),
iconTexture(of::module::texture::get().requestTexture(icon, of::engine::path::ui))
{
	//vertex[0].texCoords = { 0.f ,0.f };
	//vertex[1].texCoords = { 0.f, 64.f };
	//vertex[2].texCoords = { 64.f, 64.f};
	//vertex[3].texCoords = { 64.f, 0.f };
	//buf.create(4);
	updatePos({ 0,0 });
}

//Graphics::UI::EffectIcon::EffectIcon() : EffectIcon("", nullptr)
//{
//
//}

void Graphics::UI::EffectIcon::updatePos(const glm::vec2& newPos)
{
	pos = newPos;
	//vertex[0].position = { pos.x, pos.y };
	//vertex[1].position = { pos.x, pos.y + iconSize.y };
	//vertex[2].position = { pos.x + iconSize.x, pos.y + iconSize.y};
	//vertex[3].position = { pos.x + iconSize.x, pos.y };
	//buf.update(vertex);
	toolTip.setToolTip("Aasdad");
}

void Graphics::UI::EffectIcon::onMouseHover(const glm::vec2& mouse)
{
	toolTip.drawToolTip = visible;
	if (toolTip.drawToolTip && mouseInside(pos, iconSize, mouse))
	{
		toolTip.setPosition(mouse);
	}
}

void Graphics::UI::EffectIcon::readInput()
{
}

void Graphics::UI::EffectIcon::render()
{
	if (!visible)
		return;
	ImGui::Image((void*)iconTexture.get(), {64.f, 64.f});
	if (ImGui::IsItemHovered())
	{
		// drawToolTip
	}
}
