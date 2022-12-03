#ifndef ListObjective_HPP
#define ListObjective_HPP

#include "QuestObjective.hpp"

namespace Questing
{
	class ListObjective : public QuestObjective
	{

		size_t recalculateList();
	public:

		std::vector<std::unique_ptr<QuestObjective>> list;


		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<QuestObjective>(this));
			ar(list);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<QuestObjective>(this));
			ar(list);
		}

		void activateObjective() override;
		void deactivateObjective() override;

		// Inherited via QuestObjective
		virtual size_t onEnemyDefeated(GameObject* go) override;
		virtual size_t onItemPickUp(Items::Base* b) override;
		virtual size_t onItemDropped(Items::Base* b) override;
		virtual void resetObjective() override;
		

		// Inherited via QuestObjective
		virtual ObjectiveState getCurrentState() override;
		virtual void restoreState(const ObjectiveState& state) override;

	};
}
CEREAL_REGISTER_TYPE(Questing::ListObjective);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Questing::QuestObjective, Questing::ListObjective);
#endif