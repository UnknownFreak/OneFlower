#ifndef BONEOBJECTINFO_H
#define BONEOBJECTINFO_H

#include "universalobjectinterface.h"

#include "angleinfo.h"

namespace SpriterEngine
{
	class BoneObjectInfo : public UniversalObjectInterface
	{
	public:
		BoneObjectInfo();

		point getPosition() const override;
		real getAngle() const override;
		point getScale() const override;
		real getAlpha() const override;

		void setPosition(const point &newPosition) override;
		void setAngle(real newAngle) override;
		void setScale(const point &newScale) override;
		void setAlpha(real newAlpha) override;
		void setSpin(s_int newSpin) override;

		void setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject) override;

	private:
		point position;
		AngleInfo angle;
		point scale;
		real alpha;
	};
}

#endif // BONEOBJECTINFO_H
