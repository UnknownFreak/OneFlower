#ifndef SkillIcon_HPP
#define SkillIcon_HPP

#include <swizzle/gfx/Texture.hpp>

#include "UIContext.hpp"

#include <Combat/Skill.hpp>

namespace Graphics::UI
{
	class SkillIcon : public UIContext
	{
		std::shared_ptr<swizzle::gfx::Texture> skillIcon;
		glm::vec2 pos;
		of::combat::Skill* skill;
	public:
		SkillIcon(of::combat::Skill* skill);
		SkillIcon(const SkillIcon& copy);
		//SkillIcon& operator=(const SkillIcon& other);

		void setPosition(const glm::vec2& pos);
		void update() override;

		// Inherited via UIContext
		virtual void onMouseHover(const glm::vec2& mouse) override;
		virtual void readInput() override;

		virtual void render() override;
	};
}



#endif