#ifndef AOrBlObjective_HPP
#define AOrBlObjective_HPP

#include "QuestObjective.hpp"

namespace Questing
{
	class AOrBObjective : public QuestObjective
	{

		size_t checkABState();

	public:

		std::unique_ptr<QuestObjective> a;
		std::unique_ptr<QuestObjective> b;


		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<QuestObjective>(this));
			ar(a);
			ar(b);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<QuestObjective>(this));
			ar(a);
			ar(b);
		}

		void activateObjective() override;
		void deactivateObjective() override;

		// Inherited via QuestObjective
		virtual size_t onEnemyDefeated(of::object::GameObject* go) override;
		virtual size_t onItemPickUp(Items::Base* b) override;
		virtual size_t onItemDropped(Items::Base* b) override;
		virtual void resetObjective() override;

		// Inherited via QuestObjective
		virtual ObjectiveState getCurrentState() override;
		virtual void restoreState(const ObjectiveState& state) override;
	};
}
CEREAL_REGISTER_TYPE(Questing::AOrBObjective);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Questing::QuestObjective, Questing::AOrBObjective);
#endif 