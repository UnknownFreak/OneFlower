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

		Core::uuid enemy;
		Core::String tag;

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
		virtual size_t onEnemyDefeated(GameObject* go) override;
		virtual size_t onItemPickUp(Items::Base* b) override;
		virtual size_t onItemDropped(Items::Base* b) override;

		virtual void resetObjective() override;

		// Inherited via QuestObjective
		virtual ObjectiveState getCurrentState() override;
		virtual void restoreState(const ObjectiveState& state) override;
	};
}

#endif