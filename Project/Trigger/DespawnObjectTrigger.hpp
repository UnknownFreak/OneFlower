#ifndef DespawnObjectTrigger_HPP
#define DespawnObjectTrigger_HPP

#include "Trigger.hpp"

namespace Trigger
{
	class DespawnObjectTrigger : public Trigger
	{

	public:

		Core::uuid gameObjectToDespawn;

		// Inherited via Trigger
		virtual void executeInternal() override;

		// Inherited via Trigger
		virtual std::unique_ptr<Trigger> clone() const override;
	};
}

#endif