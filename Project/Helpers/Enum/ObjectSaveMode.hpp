#ifndef EDITOROBJECTSAVEMODE_HPP
#define EDITOROBJECTSAVEMODE_HPP
/*
Save mode defines how the Requestable is saved.
*/
namespace Enums
{

	enum class ObjectSaveMode
	{
		/*
		Default mode for saving object,
		this will save the object IF the requestable fromMod equals current openedMod
		//*/
		DEFAULT,
		/*
		Remove mode for saving object,
		this will remove the object from the Requsetable (when loading)
		IF the Requestable fromMod is equal to the WorldManagement openedMod,
		it will not be saved
		//*/
		REMOVE,
		/*
		Edit mode for saving object,
		this will move the object from the Requestable IF the fromMod does not
		equal to the Requestable fromMod, IF it is equal, then it will be saved
		and the flag type will be set to DEFAULT
		//*/
		EDIT,
		/*
		Add mode for saving object,
		this will save the object.
		IF the Requestable fromMod equals WorldManagement openedMod
		the flag will be set to DEFAULT
		//*/
		ADD
	};

	inline of::common::String to_string(const Enums::ObjectSaveMode& type)
	{
		switch (type)
		{
		case Enums::ObjectSaveMode::DEFAULT: return "Default";
		case Enums::ObjectSaveMode::REMOVE: return "Remove";
		case Enums::ObjectSaveMode::EDIT: return "Edit";
		case Enums::ObjectSaveMode::ADD: return "Add";
		default:
			return "Unknown";
		}
	}
}
#endif