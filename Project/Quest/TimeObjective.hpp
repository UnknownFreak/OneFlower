#ifndef SurviveObjective_HPP
#define SurviveObjective_HPP

#include "QuestObjective.hpp"
#include <Requirement/TimedRequirement.hpp>

namespace Questing
{
	class TimeObjective : public QuestObjective
	{
	public:
		Enums::QuestState fullfilledState;
		Requirement::TimedRequirement timeToSurvive;

		// Inherited via QuestObjective
		virtual size_t onEnemyDefeated(of::object::GameObject* go) override;
		virtual size_t onItemPickUp(Items::Base* b) override;
		virtual size_t onItemDropped(Items::Base* b) override;
		virtual ObjectiveState getCurrentState() override;
		virtual void restoreState(const ObjectiveState& state) override;

		virtual size_t completeObjective() override;
		virtual size_t failObjective() override;

		virtual void activateObjective() override;
		virtual void deactivateObjective() override;
		virtual void resetObjective() override;
		virtual void updateObjectiveRequirement() override;


		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<QuestObjective>(this));
			ar(timeToSurvive);
			ar(fullfilledState);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<QuestObjective>(this));
			ar(timeToSurvive);
			ar(fullfilledState);
		}
	};
}

#endif