#ifndef PlayerBuffDebuff_HPP
#define PlayerBuffDebuff_HPP

#include <unordered_map>
#include "UIContext.hpp"

#include <Combat/Stats.hpp>
#include "PlainToolTip.hpp"
#include "EffectIcon.hpp"

namespace Graphics::UI
{

	class PlayerBuffDebuff : public UIContext
	{
		Core::Vector2f pos;
		std::unordered_map<Core::uuid, EffectIcon> effectIcons;
		PlainToolTip dummy;
		std::shared_ptr<Component::Stats> stats;
	public:

		void setStats(std::shared_ptr<Component::Stats> stats);

		PlayerBuffDebuff(const Core::Vector2f& pos);

		void update();

		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f& mouse) override;
		virtual void readInput() override;

		virtual void render() override;

	};
}

#endif