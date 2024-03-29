#ifndef CollectItemObjective_HPP
#define CollectItemObjective_HPP

#include "QuestObjective.hpp"

namespace Questing
{
	class CollectItemObjective : public QuestObjective
	{
	public:
		size_t itemCount;
		File::Mod::ModFileUUIDHelper itemId;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<QuestObjective>(this));
			ar(itemCount);
			ar(itemId);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<QuestObjective>(this));
			ar(itemCount);
			ar(itemId);
		}

		virtual void activateObjective() override;

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