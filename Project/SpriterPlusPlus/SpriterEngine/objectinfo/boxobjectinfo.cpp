#include "boxobjectinfo.h"

namespace SpriterEngine
{
	BoxObjectInfo::BoxObjectInfo() :
		scale(1, 1),
		alpha(1)
	{
	}

	point BoxObjectInfo::getPosition() const
	{
		return position;
	}

	real BoxObjectInfo::getAngle() const
	{
		return angle.angle;
	}

	point BoxObjectInfo::getScale() const
	{
		return scale;
	}

	real BoxObjectInfo::getAlpha() const
	{
		return alpha;
	}

	point BoxObjectInfo::getPivot() const
	{
		return pivot;
	}

	void BoxObjectInfo::setPosition(const point &newPosition)
	{
		position = newPosition;
	}

	void BoxObjectInfo::setAngle(real newAngle)
	{
		angle.angle = newAngle;
	}

	void BoxObjectInfo::setScale(const point &newScale)
	{
		scale = newScale;
	}

	void BoxObjectInfo::setAlpha(real newAlpha)
	{
		alpha = newAlpha;
	}

	void BoxObjectInfo::setPivot(const point &newPivot)
	{
		pivot = newPivot;
	}

	void BoxObjectInfo::setSpin(s_int newSpin)
	{
		angle.spinDirection = newSpin;
	}

	void BoxObjectInfo::setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setAngle(angle.angleLinear(bObject->getAngle(), t));
		resultObject->setAlpha(linear(alpha, bObject->getAlpha(), t));
		resultObject->setPosition(linear(position, bObject->getPosition(), t));
		resultObject->setScale(linear(scale, bObject->getScale(), t));
		resultObject->setPivot(pivot);
	}
}