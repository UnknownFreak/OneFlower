#pragma once

namespace of::module
{
	enum class SaveSetting
	{
		/*
		* Never save the object, this is used for all static objects that can be saved
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
		* Persist the object, but it's a special effect (e.g. player spell, or skill), persist the status of the skill (if applicable)
		*/
		SPECIAL_EFFECT_RE_CONSTRUCT,
	};

}