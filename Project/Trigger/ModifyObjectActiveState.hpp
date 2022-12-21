#pragma once
#ifndef ModifyObjectActiveStateTrigger_HPP
#define ModifyObjectActiveStateTrigger_HPP

#include <resource/trigger/Trigger.hpp>
#include <Helpers/Enum/ObjectState.hpp>

namespace Trigger
{
	class ModifyObjectActiveState : public of::resource::trigger::Trigger
	{

	public:

		of::common::uuid gameObjectToModify;
		Enums::ObjectState objectState = Enums::ObjectState::Active;

		// Inherited via Trigger
		virtual void executeInternal() override;

		// Inherited via Trigger
		virtual std::unique_ptr<Trigger> clone() const override;
	};
}


#endif