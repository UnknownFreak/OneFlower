#ifndef PlayerBuffDebuff_HPP
#define PlayerBuffDebuff_HPP

#include <unordered_map>
#include "UIContext.hpp"

#include <component/stats.hpp>
#include "PlainToolTip.hpp"
#include "EffectIcon.hpp"

namespace Graphics::UI
{

	class PlayerBuffDebuff : public UIContext
	{
		glm::vec2 pos;
		std::unordered_map<of::common::uuid, EffectIcon> effectIcons;
		PlainToolTip dummy;
		std::shared_ptr<of::component::Stats> stats;
	public:

		void setStats(std::shared_ptr<of::component::Stats> stats);

		PlayerBuffDebuff(const glm::vec2& pos);

		void update();

		// Inherited via UIContext
		virtual void onMouseHover(const glm::vec2& mouse) override;
		virtual void readInput() override;

		virtual void render() override;

	};
}

#endif