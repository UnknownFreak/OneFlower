#include "boxinstanceinfo.h"

namespace SpriterEngine
{
	BoxInstanceInfo::BoxInstanceInfo(point initialSize) :
		size(initialSize)
	{
	}

	point BoxInstanceInfo::getPosition() const
	{
		return position;
	}

	real BoxInstanceInfo::getAngle() const
	{
		return angle.angle;
	}

	point BoxInstanceInfo::getScale() const
	{
		return scale;
	}

	point BoxInstanceInfo::getPivot() const
	{
		return pivot;
	}

	point BoxInstanceInfo::getSize() const 
	{
		return size;
	}

	real BoxInstanceInfo::getAlpha() const
	{
		return 1;
	}

	void BoxInstanceInfo::setPosition(const point &newPosition)
	{
		position = newPosition;
	}

	void BoxInstanceInfo::setAngle(real newAngle)
	{
		angle.angle = newAngle;
	}

	void BoxInstanceInfo::setScale(const point &newScale)
	{
		scale = newScale;
	}

	void BoxInstanceInfo::setPivot(const point &newPivot)
	{
		pivot = newPivot;
	}

	void BoxInstanceInfo::setAlpha(real /*newAlpha*/)
	{
		// ignore setAlpha commands without throwing an error
	}

	void BoxInstanceInfo::setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *)
	{
		real tempAngle = angle.angle;
		point tempPosition = position;
		point tempScale = scale;
		point tempPivot = pivot;

		aObject->setObjectToLinear(bObject, t, this);

		setAngle(shortestAngleLinear(tempAngle, angle.angle, blendRatio));
		setPosition(linear(tempPosition, position, blendRatio));
		setScale(linear(tempScale, scale, blendRatio));
		setPivot(linear(tempPivot, pivot, blendRatio));
	}

	void BoxInstanceInfo::render()
	{
		// if (renderDebugBoxes)
		// TODO: add drawing code here to enable bone debug rendering

		// getPosition()
		// getAngle();
		// getScale();
		// getPivot() * getSize();
	}
}