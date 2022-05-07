#ifndef PlayerStats_HPP
#define PlayerStats_HPP

#include "UIContext.hpp"
#include "PlayerBuffDebuff.hpp"
#include "ActionBar.hpp"

#include <Combat/Stats.hpp>

#include <Graphics/UI/ProgressBar.hpp>

namespace Graphics::UI
{
	class PlayerStats : public Graphics::UI::UIContext
	{
		std::shared_ptr<Component::Stats> stats;
		PlayerBuffDebuff buffDebuff;
		ActionBar actionBar;

		ProgressBar healthBar;
		ProgressBar manaBar;
		ProgressBar barrierBar;
		ProgressBar xpBar;

		float x, y;
	public:
		PlayerStats();

		void setPlayerStats(std::shared_ptr<Component::Stats> component);

		// Inherited via UIContext
		virtual void readInput() override;
		virtual void update() override;

		// Inherited via Drawable
		virtual void render() override;

		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f& mouse) override;
	};

}

#endif