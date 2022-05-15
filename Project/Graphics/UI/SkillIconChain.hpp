#ifndef SkillIconChain_HPP
#define SkillIconChain_HPP

#include <vector>
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
		void updatePos(const glm::vec2& newPos);

		// Inherited via UIContext
		virtual void onMouseHover(const glm::vec2& mouse) override;
		virtual void readInput() override;
		virtual void render() override;

	};
	
}


#endif