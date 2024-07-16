#pragma once
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>

#include <file/SaveState.hpp>

namespace of::trigger
{
	class TriggerState : public of::file::save_state::SaveState
	{

	protected:
		virtual common::String getType() const override;

	public:
		bool triggered;

		TriggerState();
		TriggerState(bool triggered);

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<SaveState>(this));
			ar(triggered);
		}
		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<SaveState>(this));
			ar(triggered);
		}
	};

}
CEREAL_REGISTER_TYPE(of::trigger::TriggerState);
