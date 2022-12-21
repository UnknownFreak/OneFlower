#ifndef CollectItemObjective_HPP
#define CollectItemObjective_HPP

#include "QuestObjective.hpp"

namespace Questing
{
	class CollectItemObjective : public QuestObjective
	{
	public:
		size_t itemCount;
		of::file::FileId itemId;

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
		virtual size_t onEnemyDefeated(of::object::GameObject* go) override;
		virtual size_t onItemPickUp(Items::Base* b) override;
		virtual size_t onItemDropped(Items::Base* b) override;

		// Inherited via QuestObjective
		virtual ObjectiveState getCurrentState() override;
		virtual void restoreState(const ObjectiveState& state) override;
	};
}

CEREAL_REGISTER_TYPE(Questing::CollectItemObjective);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Questing::QuestObjective, Questing::CollectItemObjective);

#endif