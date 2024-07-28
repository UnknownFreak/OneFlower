#include "PlayerStats.hpp"

#include <Object/GameObject.hpp>

// TODO: Read x, y from config file (makes the ui somewhat customizable)
Graphics::UI::PlayerStats::PlayerStats() : UIContext(swizzle::input::Keys::KeyF4, "PlayerStats", false), x(5.f), y(10.f),
healthBar(x + 50, y + 15, 300, 20, 1, 1, glm::vec3(0, 150, 0), 0, 40, true, 30, 2.f),
manaBar(x + 60, y + 35, 250, 15, 1, 1, glm::vec3(0, 0, 170), 40, 0, true, 20, 0.f),
barrierBar(x + 50, y + 50, 180, 15, 1, 0, glm::vec3(150, 150, 0), 40, 0, true, 30, 0.f),
xpBar(x + 43, y + 65, 180, 4, 10, 5, glm::vec3(0, 150, 150), 0, 0, false),
buffDebuff({x + 40, y + 80})
{
	//temp.setPosition(x, y);
	//temp.setSize({ 400.f, 170.f });
	//playerLevel.setPosition(x, y);
	//playerLevel.setRadius(30.f);
	//playerLevel.setFillColor(sf::Color::Black);
}

void Graphics::UI::PlayerStats::setPlayerStats(std::shared_ptr<of::component::Stats> component)
{
	stats = component;
	buffDebuff.setStats(component);
	actionBar.setPlayerCombatSkills(component->attachedOn->getShared<of::component::CombatComponent>());
}

void Graphics::UI::PlayerStats::readInput()
{
}

void Graphics::UI::PlayerStats::update()
{
	if (stats)
	{
		auto& health = stats->mainStat[Enums::StatType::Health];
		healthBar.setNewMax(float(health.max));
		healthBar.update(float(health.current));
		auto& mana = stats->mainStat[Enums::StatType::Mana];
		manaBar.setNewMax(float(mana.max));
		manaBar.update(float(mana.current));
		auto& barrierStat = stats->mainStat[Enums::StatType::BarrierStrength];
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

void Graphics::UI::PlayerStats::render()
{
	if (!visible)
		return;
	//ImGui::NewFrame();
	//ImGui::Begin("Fluff");
	//healthBar.render();
	//manaBar.render();
	//barrierBar.render();
	//xpBar.render();
	//
	//buffDebuff.render();
	//actionBar.render();
	//ImGui::End();
	//ImGui::EndFrame();
}

void Graphics::UI::PlayerStats::onMouseHover(const glm::vec2& mouse)
{
	healthBar.onMouseHover(mouse);
	manaBar.onMouseHover(mouse);
	barrierBar.onMouseHover(mouse);
	xpBar.onMouseHover(mouse);
	buffDebuff.onMouseHover(mouse);
	actionBar.onMouseHover(mouse);
}
