#ifndef SpawnObjectTrigger_HPP
#define SpawnObjectTrigger_HPP

#include <trigger/Trigger.hpp>
#include <file/FileId.hpp>
#include <glm/vec3.hpp>

namespace Trigger
{

	class SpawnObjectTrigger : public of::trigger::Trigger
	{
		
		// Inherited via Trigger
		virtual void executeInternal() override;

	public:

		of::file::FileId prefabId;
		glm::vec3 position;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Trigger>(this));
			ar(prefabId);
			ar(position.x, position.y, position.z);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Trigger>(this));
			ar(prefabId);
			ar(position.x, position.y, position.z);
		}

		// Inherited via Trigger
		virtual std::unique_ptr<Trigger> clone() const override;
	};
}

#endif