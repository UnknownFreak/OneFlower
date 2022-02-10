#ifndef SkillIconChain_HPP
#define SkillIconChain_HPP

#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include "UIContext.hpp"
#include "SkillIcon.hpp"

namespace Graphics::UI
{

	class SkillIconChain : public UIContext
	{

		std::vector<SkillIcon> icons;

	public:

		SkillIconChain();
		SkillIconChain(const std::vector<SkillIcon>& icons);
		SkillIconChain(const SkillIconChain& copy);

		void update() override;
		void updatePos(const Core::Vector2f& newPos);

		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f& mouse) override;
		virtual void readInput() override;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
	
}


#endif