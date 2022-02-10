#include "PlayerBuffDebuff.hpp"

void Graphics::UI::PlayerBuffDebuff::setStats(std::shared_ptr<Component::Stats> newStats)
{
	stats = newStats;
}

Graphics::UI::PlayerBuffDebuff::PlayerBuffDebuff(const Core::Vector2f& pos) : UIContext(sf::Keyboard::Key::Unknown, "BuffDebuff", true), pos(pos)
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
	Core::Vector2f loopPos = pos;
	for (auto& icon : effectIcons)
	{
		icon.second.updatePos(loopPos);
		loopPos.x += icon.second.iconSize.x + 2;
	}
}

void Graphics::UI::PlayerBuffDebuff::onMouseHover(const Core::Vector2f& mouse)
{
	for (auto& icon : effectIcons)
		icon.second.onMouseHover(mouse);
}

void Graphics::UI::PlayerBuffDebuff::readInput()
{
}

void Graphics::UI::PlayerBuffDebuff::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!visible)
		return;
	for (auto& icon : effectIcons)
	{
		target.draw(icon.second, states);
	}
	for (auto& icon : effectIcons)
	{
		icon.second.drawToolTip(target, states);
	}
}
