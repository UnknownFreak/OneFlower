#pragma once

namespace of::session
{
	enum class SaveSetting
	{
		/*
		* Never save the object, this is used for all static objects
		*/
		NEVER_STORE,
		/*
		* Save the object on interact, this can be via player interaction or dynamically by another object trigger etc.
		*/
		PERSIST_ON_INTERACT,
		/*
		* Persist the object on save, this object will always be persisted 
		*/
		PERSIST_ON_SAVE,
		/*
		* Persist the object (like above), but it's a special object (e.g. player spell, or skill), so references needs to be re-calculated, could also be loot for example), persist the statuses of the object (if applicable)
		*/
		SPECIAL_RE_CONSTRUCT,
	};

}