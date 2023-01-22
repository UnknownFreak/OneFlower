#ifndef ActionBar_HPP
#define ActionBar_HPP

#include "UIContext.hpp"

#include "SkillIconChain.hpp"

#include <object/component/Combat.hpp>

namespace Graphics::UI
{

	class ActionBar : public UIContext
	{
		std::map<Enums::CombatSkill, SkillIconChain> iconChains;
		std::shared_ptr<of::object::component::CombatComponent> combat = nullptr;

	public:

		ActionBar();

		void setPlayerCombatSkills(std::shared_ptr<of::object::component::CombatComponent> combat);

		virtual void update() override;

		// Inherited via UIContext
		virtual void onMouseHover(const glm::vec2& mouse) override;
		virtual void readInput() override;

		virtual void render() override;

	};
}

#endif