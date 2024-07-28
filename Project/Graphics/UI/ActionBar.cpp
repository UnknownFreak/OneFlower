#include "ActionBar.hpp"

Graphics::UI::ActionBar::ActionBar() : UIContext(swizzle::input::Keys::KeyNone, "ActionBar", true)
{
}

void Graphics::UI::ActionBar::setPlayerCombatSkills(std::shared_ptr<of::component::CombatComponent> newCombat)
{
	combat = newCombat;
}

void Graphics::UI::ActionBar::update()
{
	if (combat && combat->wasSkillChanged)
	{
		auto& skills = combat->getSkills();
		//for (auto& skill : skills)
		//{
		//	iconChains[skill.first] = skill.second.getChain();
		//}
		if (skills.size() != 0)
			combat->wasSkillChanged = false;
	}
	glm::vec2 pos = {420.f, 1440.f - 280.f};
	for (auto& chain : iconChains)
	{
		chain.second.update();
		chain.second.updatePos(pos);
		pos.y += 70.f;
	}
}

void Graphics::UI::ActionBar::onMouseHover(const glm::vec2& mouse)
{
	for (auto& it : iconChains)
		it.second.onMouseHover(mouse);
}

void Graphics::UI::ActionBar::readInput()
{
}

void Graphics::UI::ActionBar::render()
{
	for (auto& it : iconChains)
		it.second.render();
}
