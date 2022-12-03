#ifndef QuestTrigger_HPP
#define QuestTrigger_HPP

#include "Trigger.hpp"

#include <Helpers/Enum/QuestTriggerType.hpp>
#include <Quest/Quest.hpp>

namespace Trigger
{
	// TODO: remove
	struct tmp {
		inline void start(const of::file::FileId&) {};
		inline void fail(const of::file::FileId&) {};
		inline void reset(const of::file::FileId&) {};
		inline void progress(const of::file::FileId&) {};
	};

	class QuestTrigger : public Trigger
	{
		// Inherited via Trigger
		virtual void executeInternal() override;

	public:
		of::file::FileId questId;
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