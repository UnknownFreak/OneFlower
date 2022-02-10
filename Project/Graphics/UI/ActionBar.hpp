#ifndef ActionBar_HPP
#define ActionBar_HPP

#include "UIContext.hpp"

#include "SkillIconChain.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <Combat/Combat.hpp>

namespace Graphics::UI
{

	class ActionBar : public UIContext
	{
		std::map<Enums::CombatSkill, SkillIconChain> iconChains;
		std::shared_ptr<Component::CombatComponent> combat = nullptr;

	public:

		ActionBar();

		void setPlayerCombatSkills(std::shared_ptr<Component::CombatComponent> combat);

		virtual void update() override;

		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f& mouse) override;
		virtual void readInput() override;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
}

#endif