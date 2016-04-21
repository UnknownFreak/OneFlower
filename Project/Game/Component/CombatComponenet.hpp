#ifndef COMBAT_COMPONENT_HPP
#define COMBAT_COMPONENT_HPP
#include "IBaseComponent.hpp"
#include "../Skills/Skill.hpp"
#include <SFML\System\Clock.hpp>
namespace Component
{
	class Combat : public IBaseComponent < Combat >
	{
	public: 
		Combat();

		void execute();
		void update();

		Skill testSkill;
		bool executingSkill;
	protected:

		void attachOn(GameObject* attachTo);

	private:

		template < class Archive>//, GameObject& go>
		friend void save(Archive& archive, const Component::Combat& dc);
		template < class Archive>//, GameObject& go>
		friend void load(Archive& archive, Component::Combat& dc);
	};
}


#endif