#ifndef QuestTrigger_HPP
#define QuestTrigger_HPP

#include "Trigger.hpp"

#include <Helpers/Enum/QuestTriggerType.hpp>
#include <Quest/Quest.hpp>

namespace Trigger
{
	// TODO: remove
	struct tmp {
		inline void start(const File::Mod::ModFileUUIDHelper&) {};
		inline void fail(const File::Mod::ModFileUUIDHelper&) {};
		inline void reset(const File::Mod::ModFileUUIDHelper&) {};
		inline void progress(const File::Mod::ModFileUUIDHelper&) {};
	};

	class QuestTrigger : public Trigger
	{
		// Inherited via Trigger
		virtual void executeInternal() override;

	public:
		File::Mod::ModFileUUIDHelper questId;
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