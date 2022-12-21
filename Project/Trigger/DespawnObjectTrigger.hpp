#ifndef DespawnObjectTrigger_HPP
#define DespawnObjectTrigger_HPP

#include <resource/trigger/Trigger.hpp>

namespace Trigger
{
	class DespawnObjectTrigger : public of::resource::trigger::Trigger
	{

	public:

		of::common::uuid gameObjectToDespawn;

		// Inherited via Trigger
		virtual void executeInternal() override;

		// Inherited via Trigger
		virtual std::unique_ptr<Trigger> clone() const override;
	};
}

#endif