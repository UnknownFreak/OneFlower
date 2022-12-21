#ifndef DefeatEnemyObjective_HPP
#define DefeatEnemyObjective_HPP

#include "QuestObjective.hpp"

namespace Questing
{
	class DefeatEnemyObjective : public QuestObjective
	{
	public:
		size_t defeatCount;
		size_t currentDefeatCount;

		of::common::uuid enemy;
		of::common::String tag;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<QuestObjective>(this));
			ar(defeatCount);
			ar(currentDefeatCount);
			ar(enemy);
			ar(tag);
		}

		template<class Archive>
		void load(Archive& ar) 
		{
			ar(cereal::base_class<QuestObjective>(this));
			ar(defeatCount);
			ar(currentDefeatCount);
			ar(enemy);
			ar(tag);
		}

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

CEREAL_REGISTER_TYPE(Questing::DefeatEnemyObjective);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Questing::QuestObjective, Questing::DefeatEnemyObjective);
#endif