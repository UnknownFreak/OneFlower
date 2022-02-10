#ifndef SkillIcon_HPP
#define SkillIcon_HPP

#include "UIContext.hpp"

#include <Combat/Skill.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>

namespace Graphics::UI
{
	class SkillIcon : public UIContext
	{
		std::shared_ptr<sf::Texture> skillIcon;
		Core::Vector2f pos;
		sf::Vertex vertices[8];
		sf::VertexBuffer buf;
		Combat::Skill* skill;
	public:
		SkillIcon(Combat::Skill* skill);
		SkillIcon(const SkillIcon& copy);
		//SkillIcon& operator=(const SkillIcon& other);

		void setPosition(const Core::Vector2f& pos);
		void update() override;

		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f& mouse) override;
		virtual void readInput() override;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
}



#endif