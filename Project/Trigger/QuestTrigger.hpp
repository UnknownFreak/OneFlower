#ifndef QuestTrigger_HPP
#define QuestTrigger_HPP

#include "Trigger.hpp"

#include <Helpers/Enum/QuestTriggerType.hpp>
#include <Quest/Quest.hpp>

namespace Trigger
{
	// TODO: remove
	struct tmp {
		inline void start(const ModFileUUIDHelper&) {};
		inline void fail(const ModFileUUIDHelper&) {};
		inline void reset(const ModFileUUIDHelper&) {};
		inline void progress(const ModFileUUIDHelper&) {};
	};

	class QuestTrigger : public Trigger
	{
		// Inherited via Trigger
		virtual void executeInternal() override;

	public:
		ModFileUUIDHelper questId;
		Enums::QuestTriggerType triggerType;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Trigger>(this));
			ar(questId);
			ar(triggerType);
		}
		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Trigger>(this));
			ar(questId);
			ar(triggerType);
		}

		// Inherited via Trigger
		virtual std::unique_ptr<Trigger> clone() const override;
	};

}

#endif