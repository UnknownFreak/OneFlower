#pragma once
#ifndef ModifyObjectActiveStateTrigger_HPP
#define ModifyObjectActiveStateTrigger_HPP

#include <resource/trigger/Trigger.hpp>
#include <object/ObjectState.hpp>

namespace Trigger
{
	class ModifyObjectActiveState : public of::resource::trigger::Trigger
	{

	public:

		of::common::uuid gameObjectToModify;
		of::object::ObjectState objectState = of::object::ObjectState::Active;

		// Inherited via Trigger
		virtual void executeInternal() override;

		// Inherited via Trigger
		virtual std::unique_ptr<Trigger> clone() const override;
	};
}


#endif