#ifndef SpawnObjectTrigger_HPP
#define SpawnObjectTrigger_HPP

#include "Trigger.hpp"
#include <File/ModFileUUIDHelper.hpp>
#include <Helpers/Vector3.hpp>

namespace Trigger
{

	class SpawnObjectTrigger : public Trigger
	{
		
		// Inherited via Trigger
		virtual void executeInternal() override;

	public:

		ModFileUUIDHelper prefabId;
		Core::Vector3f position;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Trigger>(this));
			ar(prefabId);
			ar(position);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Trigger>(this));
			ar(prefabId);
			ar(position);
		}

		// Inherited via Trigger
		virtual std::unique_ptr<Trigger> clone() const override;
	};
}

#endif