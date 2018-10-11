#include "soundobjectinfo.h"

namespace SpriterEngine
{
	SoundObjectInfo::SoundObjectInfo()
	{
	}

	s_int SoundObjectInfo::getTriggerCount()
	{
		return trigger;
	}

	real SoundObjectInfo::getVolume()
	{
		return volume;
	}

	real SoundObjectInfo::getPanning()
	{
		return panning;
	}

	void SoundObjectInfo::setTriggerCount(s_int newTriggerCount)
	{
		trigger = newTriggerCount != 0;
	}

	void SoundObjectInfo::setVolume(real newVolume)
	{
		volume = newVolume;
	}

	void SoundObjectInfo::setPanning(real newPanning)
	{
		panning = newPanning;
	}

	void SoundObjectInfo::setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setVolume(linear(volume, bObject->getVolume(), t));
		resultObject->setPanning(linear(panning, bObject->getPanning(), t));
	}
}