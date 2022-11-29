#ifndef DuelObjective_HPP
#define DuelObjective_HPP

#include "QuestObjective.hpp"

namespace Questing
{
	class DuelObjective : public QuestObjective
	{
	public:
		of::common::uuid duel;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<QuestObjective>(this));
			ar(duel);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<QuestObjective>(this));
			ar(duel);
		}

		size_t completeOrFailObjective(const bool& forceFail = false) override;

		// Inherited via QuestObjective
		virtual size_t onEnemyDefeated(GameObject* go) override;
		virtual size_t onItemPickUp(Items::Base* b) override;
		virtual size_t onItemDropped(Items::Base* b) override;


		// Inherited via QuestObjective
		virtual ObjectiveState getCurrentState() override;
		virtual void restoreState(const ObjectiveState& state) override;

	};
}

#endif 