#pragma once

#include <cereal/cereal.hpp>
#include <cereal/types/map.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>

#include <file/SaveState.hpp>

#include <object/ObjectState.hpp>

#include <utils/common/uuid.hpp>
#include <file/FileId.hpp>

namespace of::object
{
	class ObjectSaveState : public of::session::SaveState
	{
	protected:
		virtual common::String getType() const override;

	public:
		std::map<of::common::uuid, std::unique_ptr<of::session::SaveState>> objectSaveStates;
		ObjectState objectState = ObjectState::Undefined;
		of::file::FileId prefabId{};

		ObjectSaveState();
		ObjectSaveState(const ObjectSaveState&) = delete;
		ObjectSaveState& operator=(const ObjectSaveState) = delete;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<SaveState>(this));
			ar(objectSaveStates);
			ar(prefabId);
		}
		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<SaveState>(this));
			ar(objectSaveStates);
			ar(prefabId);
		}
	};
}
CEREAL_REGISTER_TYPE(of::object::ObjectSaveState);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::session::SaveState, of::object::ObjectSaveState);
