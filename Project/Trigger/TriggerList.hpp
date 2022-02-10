#ifndef TriggerList_HPP
#define TriggerList_HPP

#include <vector>
#include <Trigger/Trigger.hpp>

namespace Trigger
{
	class TriggerList : public Trigger
	{
	public:

		std::vector<std::unique_ptr<Trigger>> triggerList;

		// Inherited via Trigger
		virtual void executeInternal() override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Trigger>(this));
			ar(TriggerList);
		}
		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Trigger>(this));
			ar(triggerList);
		}

		// Inherited via Trigger
		virtual std::unique_ptr<Trigger> clone() const override;
	};
}

#endif