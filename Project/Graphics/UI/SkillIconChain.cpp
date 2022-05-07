#include "SkillIconChain.hpp"

Graphics::UI::SkillIconChain::SkillIconChain() : SkillIconChain(std::vector<SkillIcon>())
{
}

Graphics::UI::SkillIconChain::SkillIconChain(const std::vector<SkillIcon>& icons) : UIContext(swizzle::input::Keys::KeyNone, "SkillIconChain", true), icons(icons)
{
}

Graphics::UI::SkillIconChain::SkillIconChain(const SkillIconChain& copy): SkillIconChain(copy.icons)
{
}

void Graphics::UI::SkillIconChain::update()
{
	for (auto& icon : icons)
	{
		icon.update();
	}
}

void Graphics::UI::SkillIconChain::updatePos(const Core::Vector2f& newPos)
{
	Core::Vector2f offset = { 0,0 };
	for (auto& icon : icons)
	{
		icon.setPosition(newPos + offset);
		offset.x += 70.f;
	}
}

void Graphics::UI::SkillIconChain::onMouseHover(const Core::Vector2f& mouse)
{
	for (auto& icon : icons)
	{
		icon.onMouseHover(mouse);
	}
}

void Graphics::UI::SkillIconChain::readInput()
{
}

void Graphics::UI::SkillIconChain::render()
{
	for (auto& icon : icons)
	{
		icon.render();
	}
}
