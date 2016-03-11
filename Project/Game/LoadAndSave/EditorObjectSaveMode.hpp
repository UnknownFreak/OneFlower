#ifndef EDITOROBJECTSAVEMODE_HPP
#define EDITOROBJECTSAVEMODE_HPP
/*
Save mode defines how the object is saved.
This applies to DBZones, DBZonePrefabStruct, Prefabs, Items and Quest
*/

enum EditorObjectSaveMode
{
	/*
	Default mode for saving object,
	this will save the object IF the DBZone fromMod equals
	to the WorldManagement openedMod
	//*/
	DEFAULT,
	/*
	Remove mode for saving object,
	this will remove the object from the DBZone (when loading)
	IF the DBZone fromMod is equal to the WorldManagement openedMod,
	it will not be saved
	//*/
	REMOVE,
	/*
	Edit mode for saving object,
	this will move the object from the DBZone IF the fromMod does not
	equal to the DBZone fromMod, IF it is equal, then it will be saved
	and the flag type will be set to DEFAULT
	//*/
	EDIT,
	/*
	Add mode for saving object,
	this will save the object.
	IF the DBZone fromMod equals WorldManagement openedMod
	the flag will be set to DEFAULT
	//*/
	ADD

};

#endif