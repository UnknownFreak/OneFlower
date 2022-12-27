#pragma once

#include <cereal/cereal.hpp>
#include <cereal/types/map.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>

#include <module/SaveState.hpp>

#include <object/ObjectState.hpp>

#include <utils/common/uuid.hpp>

namespace of::object
{
	class ObjectSaveState : public of::module::save_state::SaveState
	{
	protected:
		virtual common::String getType() const override;

	public:
		std::map<of::common::uuid, std::unique_ptr<of::module::save_state::SaveState>> objectSaveStates;
		Enums::ObjectState objectState = Enums::ObjectState::Undefined;

		ObjectSaveState();
		ObjectSaveState(const ObjectSaveState&) = delete;
		ObjectSaveState& operator=(const ObjectSaveState) = delete;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<SaveState>(this));
			ar(objectSaveStates);
		}
		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<SaveState>(this));
			ar(objectSaveStates);
		}
	};
}
CEREAL_REGISTER_TYPE(of::object::ObjectSaveState);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::module::save_state::SaveState, of::object::ObjectSaveState);
