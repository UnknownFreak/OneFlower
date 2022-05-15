#include "PlayerBuffDebuff.hpp"

void Graphics::UI::PlayerBuffDebuff::setStats(std::shared_ptr<Component::Stats> newStats)
{
	stats = newStats;
}

Graphics::UI::PlayerBuffDebuff::PlayerBuffDebuff(const glm::vec2& pos) : UIContext(swizzle::input::Keys::KeyNone, "BuffDebuff", true), pos(pos)
{
}

void Graphics::UI::PlayerBuffDebuff::update()
{
	auto& effects = stats->getEffects();
	for (auto& stack : effects)
	{
		if (stack.second.hiddenStack == false && effectIcons.find(stack.first) == effectIcons.end() && stack.second.modifiers.size() != 0)
			effectIcons.emplace(stack.first, EffectIcon(stack.second.effectIcon, stack.second));
		else if (effectIcons.find(stack.first) != effectIcons.end() && stack.second.modifiers.size() == 0)
			effectIcons.erase(stack.first);
	}
	if (effects.size() == 0 && effectIcons.size() > 0)
		effectIcons.clear();
	glm::vec2 loopPos = pos;
	for (auto& icon : effectIcons)
	{
		icon.second.updatePos(loopPos);
		loopPos.x += icon.second.iconSize.x + 2;
	}
}

void Graphics::UI::PlayerBuffDebuff::onMouseHover(const glm::vec2& mouse)
{
	for (auto& icon : effectIcons)
		icon.second.onMouseHover(mouse);
}

void Graphics::UI::PlayerBuffDebuff::readInput()
{
}

void Graphics::UI::PlayerBuffDebuff::render()
{
	if (!visible)
		return;
	for (auto& icon : effectIcons)
	{
		icon.second.render();
	}
	//for (auto& icon : effectIcons)
	//{
	//	icon.second.drawToolTip(target, states);
	//}
}
