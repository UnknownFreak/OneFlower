#include "universalobjectinterface.h"

#include "../global/settings.h"

namespace SpriterEngine
{
	UniversalObjectInterface::UniversalObjectInterface()
	{
	}

	UniversalObjectInterface::~UniversalObjectInterface()
	{
	}

	point UniversalObjectInterface::getPosition() const
	{
		Settings::error("UniversalObjectInterface::getPosition - object does not contain this component - falling back on default value");
		return point();
	}

	real UniversalObjectInterface::getAngle() const
	{
		Settings::error("UniversalObjectInterface::getAngle - object does not contain this component - falling back on default value");
		return 0;
	}

	point UniversalObjectInterface::getScale() const
	{
		Settings::error("UniversalObjectInterface::getScale - object does not contain this component - falling back on default value");
		return point{ 1, 1 };
	}

	point UniversalObjectInterface::getPivot() const
	{
		Settings::error("UniversalObjectInterface::getPivot - object does not contain this component - falling back on default value");
		return point{ 0,0 };
	}

	real UniversalObjectInterface::getAlpha() const
	{
		Settings::error("UniversalObjectInterface::getAlpha - object does not contain this component - falling back on default value");
		return 1;
	}

	point UniversalObjectInterface::getSize() const
	{
		Settings::error("UniversalObjectInterface::getSize - object does not contain this component - falling back on default value");
		return point();
	}

	ImageFile *UniversalObjectInterface::getImage()
	{
		Settings::error("UniversalObjectInterface::getImage - object does not contain this component - returning null pointer");
		return 0;
	}

	EntityInstanceData * UniversalObjectInterface::getEntity(s_int)
	{
		Settings::error("UniversalObjectInterface::getEntity - object does not contain this component - returning null pointer");
		return 0;
	}

	real UniversalObjectInterface::getCurrentTime()
	{
		Settings::error("UniversalObjectInterface::getCurrentTime - object does not contain this component - falling back on default value");
		return 0;
	}

	real UniversalObjectInterface::getTimeRatio()
	{
		Settings::error("UniversalObjectInterface::getTimeRatio - object does not contain this component - falling back on default value");
		return 0;
	}

	void UniversalObjectInterface::reprocessCurrentTime()
	{
		Settings::error("UniversalObjectInterface::reprocessCurrentTime - object does not contain this component - no action taken");
	}

	ObjectInterfaceVector * UniversalObjectInterface::getZOrder()
	{
		Settings::error("UniversalObjectInterface::getZOrder - object does not contain this component - returning null pointer");
		return 0;
	}

	real UniversalObjectInterface::getRealValue()
	{
		Settings::error("UniversalObjectInterface::getRealValue - object does not contain this component - returning 0");
		return 0;
	}

	s_int UniversalObjectInterface::getIntValue()
	{
		Settings::error("UniversalObjectInterface::getIntValue - object does not contain this component - returning 0");
		return 0;
	}

	Core::String UniversalObjectInterface::getStringValue()
	{
		Settings::error("UniversalObjectInterface::getStringValue - object does not contain this component - return empty string");
		return "";
	}

	s_int UniversalObjectInterface::getTriggerCount()
	{
		Settings::error("UniversalObjectInterface::getTriggerCount - object does not contain this component - falling back on default value");
		return 0;
	}

	real UniversalObjectInterface::getVolume()
	{
		Settings::error("UniversalObjectInterface::getVolume - object does not contain this component - falling back on default value");
		return 1;
	}

	real UniversalObjectInterface::getPanning()
	{
		Settings::error("UniversalObjectInterface::getPanning - object does not contain this component - falling back on default value");
		return 0;
	}

	VariableInstanceNameAndIdMap *UniversalObjectInterface::getVariables()
	{
		Settings::error("UniversalObjectInterface::getVariables - object does not contain this component - returning null pointer");
		return 0;
	}

	UniversalObjectInterface *UniversalObjectInterface::getTags() const
	{
		Settings::error("UniversalObjectInterface::getTags - object does not contain this component - returning null pointer");
		return 0;
	}

	bool UniversalObjectInterface::tagIsActive(const Core::String &) const
	{
		Settings::error("UniversalObjectInterface::tagIsActive - object does not contain this component - falling back on default value");
		return false;
	}

	void UniversalObjectInterface::setPosition(const point &)
	{
		Settings::error("UniversalObjectInterface::setPosition - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setAngle(real )
	{
		Settings::error("UniversalObjectInterface::setAngle - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setScale(const point &)
	{
		Settings::error("UniversalObjectInterface::setScale - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setPivot(const point &)
	{
		Settings::error("UniversalObjectInterface::setPivot - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setAlpha(real )
	{
		Settings::error("UniversalObjectInterface::setAlpha - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setSpin(s_int )
	{
		Settings::error("UniversalObjectInterface::setSpin - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setImage(ImageFile *)
	{
		Settings::error("UniversalObjectInterface::setImage - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setCurrentEntity(s_int )
	{
		Settings::error("UniversalObjectInterface::setCurrentEntity - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setCurrentEntity(EntityInstanceData * )
	{
		Settings::error("UniversalObjectInterface::setCurrentEntity - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setCurrentAnimation(s_int )
	{
		Settings::error("UniversalObjectInterface::setCurrentAnimation - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setCurrentAnimation(AnimationInstance * )
	{
		Settings::error("UniversalObjectInterface::setCurrentAnimation - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setTimeRatio(real )
	{
		Settings::error("UniversalObjectInterface::setTimeRatio - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setRealValue(real )
	{
		Settings::error("UniversalObjectInterface::setRealValue - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setIntValue(s_int )
	{
		Settings::error("UniversalObjectInterface::setIntValue - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setStringValue(const Core::String &)
	{
		Settings::error("UniversalObjectInterface::setStringValue - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setStringValue(Core::String *)
	{
		Settings::error("UniversalObjectInterface::setStringValue - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setTriggerCount(s_int )
	{
		Settings::error("UniversalObjectInterface::setTriggerCount - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setVolume(real )
	{
		Settings::error("UniversalObjectInterface::setVolume - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setPanning(real )
	{
		Settings::error("UniversalObjectInterface::setPanning - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setSound(SoundFile *)
	{
		Settings::error("UniversalObjectInterface::setSound - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setTagList(TagList *)
	{
		Settings::error("UniversalObjectInterface::setTagList - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setObjectToLinear(UniversalObjectInterface *, real , UniversalObjectInterface *)
	{
		Settings::error("UniversalObjectInterface::setObjectToLinear - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setToBlendedLinear(UniversalObjectInterface *, UniversalObjectInterface *, real , real , ObjectRefInstance *)
	{
		Settings::error("UniversalObjectInterface::setObjectToBlendedLinear - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::render()
	{
		Settings::error("UniversalObjectInterface::render - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::playTrigger()
	{
		Settings::error("UniversalObjectInterface::playTrigger - object does not contain this component - no action taken");
	}
	void UniversalObjectInterface::draw(sf::RenderTarget &, sf::RenderStates) const
	{
		Settings::error("UniversalObjectInterface::sf::Drawable::draw - object does not contain this component - no action taken");
	}
}