#ifndef DefendObjective_HPP
#define DefendObjective_HPP

#include "QuestObjective.hpp"

namespace Questing
{
	class DefendObjective : public QuestObjective
	{
	public:
		Core::uuid defend;
		std::unique_ptr<Requirement::Requirement> completeRequirement;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<QuestObjective>(this));
			ar(defend);
			ar(completeRequirement);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<QuestObjective>(this));
			ar(defend);
			ar(completeRequirement);
		}

		size_t completeOrFailObjective(const bool& forceFail=false) override;
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

#endif 