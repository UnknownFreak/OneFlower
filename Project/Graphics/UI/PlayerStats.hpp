#ifndef PlayerStats_HPP
#define PlayerStats_HPP

#include "UIContext.hpp"
#include "PlayerBuffDebuff.hpp"
#include "ActionBar.hpp"

#include <Combat/Stats.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <Graphics/UI/ProgressBar.hpp>

namespace Graphics::UI
{
	class PlayerStats : public Graphics::UI::UIContext
	{
		sf::RectangleShape temp;
		std::shared_ptr<Component::Stats> stats;
		sf::CircleShape playerLevel;
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
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f& mouse) override;
	};

}

#endif