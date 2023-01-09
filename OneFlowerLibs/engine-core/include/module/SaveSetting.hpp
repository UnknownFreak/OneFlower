#pragma once

namespace of::module
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
		* Persist the object, but it's a special object (e.g. player spell, or skill), could also be loot for example), persist the statuses of the object (if applicable)
		*/
		SPECIAL_RE_CONSTRUCT,
	};

}