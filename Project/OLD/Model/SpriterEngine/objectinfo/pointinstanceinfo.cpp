#include "pointinstanceinfo.h"

namespace SpriterEngine
{
	PointInstanceInfo::PointInstanceInfo()
	{
	}

	point PointInstanceInfo::getPosition() const
	{
		return position;
	}

	real PointInstanceInfo::getAngle() const
	{
		return angle.angle;
	}

	point PointInstanceInfo::getScale() const
	{
		return point(1, 1);
	}

	real PointInstanceInfo::getAlpha() const
	{
		return 1;
	}

	void PointInstanceInfo::setPosition(const point &newPosition)
	{
		position = newPosition;
	}

	void PointInstanceInfo::setAngle(real newAngle)
	{
		angle.angle = newAngle;
	}

	void PointInstanceInfo::setSpin(s_int newSpin)
	{
		angle.spinDirection = newSpin;
	}

	void PointInstanceInfo::setScale(const point & newScale)
	{
		// ignore setScale commands without throwing an error
	}

	void PointInstanceInfo::setAlpha(real newAlpha)
	{
		// ignore setAlpha commands without throwing an error
	}

	void PointInstanceInfo::setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance)
	{
		real tempAngle = angle.angle;
		point tempPosition = position;

		aObject->setObjectToLinear(bObject, t, this);

		setAngle(shortestAngleLinear(tempAngle, angle.angle, blendRatio));
		setPosition(linear(tempPosition, position, blendRatio));
	}

	void PointInstanceInfo::render()
	{
		// if (renderDebugPoints)
		// TODO: override and add drawing code here to enable point debug rendering
	}
}