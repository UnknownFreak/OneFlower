#include "PlayerStats.hpp"

#include <Object/GameObject.hpp>

// TODO: Read x, y from config file (makes the ui somewhat customizable)
Graphics::UI::PlayerStats::PlayerStats() : UIContext(sf::Keyboard::F4, "PlayerStats", false), x(5.f), y(10.f),
healthBar(x + 50, y + 15, 300, 20, 1, 1, sf::Color(0, 150, 0), 0, 40, true, 30, 2.f),
manaBar(x + 60, y + 35, 250, 15, 1, 1, sf::Color(0, 0, 170), 40, 0, true, 20, 0.f),
barrierBar(x + 50, y + 50, 180, 15, 1, 0, sf::Color(150, 150, 0), 40, 0, true, 30, 0.f),
xpBar(x + 43, y + 65, 180, 4, 10, 5, sf::Color(0, 150, 150), 0, 0, false),
buffDebuff({x + 40, y + 80})
{
	temp.setPosition(x, y);
	temp.setSize({ 400.f, 170.f });
	playerLevel.setPosition(x, y);
	playerLevel.setRadius(30.f);
	playerLevel.setFillColor(sf::Color::Black);
}

void Graphics::UI::PlayerStats::setPlayerStats(std::shared_ptr<Component::Stats> component)
{
	stats = component;
	buffDebuff.setStats(component);
	actionBar.setPlayerCombatSkills(component->attachedOn->getSharedComponent<Component::CombatComponent>());
}

void Graphics::UI::PlayerStats::readInput()
{
}

void Graphics::UI::PlayerStats::update()
{
	if (stats)
	{
		auto& health = stats->mainStat[Enums::Attribute::Health];
		healthBar.setNewMax(float(health.max));
		healthBar.update(float(health.current));
		auto& mana = stats->mainStat[Enums::Attribute::Mana];
		manaBar.setNewMax(float(mana.max));
		manaBar.update(float(mana.current));
		auto& barrierStat = stats->mainStat[Enums::Attribute::BarrierStrength];
		float barrierValue = 0.f;
		for (auto& barrier : stats->barriers)
		{
			barrierValue = (float)barrier.second.totalBarrier;
		}
		barrierBar.setNewMax(float(barrierStat.max));
		barrierBar.update(barrierValue);
		buffDebuff.update();
		actionBar.update();
	}
}

void Graphics::UI::PlayerStats::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!visible)
		return;
	target.draw(temp);
	target.draw(healthBar, states);
	target.draw(manaBar, states);
	target.draw(barrierBar, states);
	target.draw(xpBar, states);
	target.draw(playerLevel, states);

	healthBar.drawToolTip(target, states);
	manaBar.drawToolTip(target, states);
	barrierBar.drawToolTip(target, states);
	xpBar.drawToolTip(target, states);

	target.draw(buffDebuff, states);
	target.draw(actionBar, states);
}

void Graphics::UI::PlayerStats::onMouseHover(const Core::Vector2f& mouse)
{
	healthBar.onMouseHover(mouse);
	manaBar.onMouseHover(mouse);
	barrierBar.onMouseHover(mouse);
	xpBar.onMouseHover(mouse);
	buffDebuff.onMouseHover(mouse);
	actionBar.onMouseHover(mouse);
}
