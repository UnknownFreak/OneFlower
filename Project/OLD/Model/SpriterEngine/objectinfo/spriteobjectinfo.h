#ifndef SPRITEOBJECTINFO_H
#define SPRITEOBJECTINFO_H

#include "universalobjectinterface.h"

#include "../override/imagefile.h"

#include "angleinfo.h"

namespace SpriterEngine
{
	class SpriteObjectInfo : public UniversalObjectInterface
	{
	public:
		SpriteObjectInfo();

		point getPosition() const override;
		real getAngle() const override;
		point getScale() const override;
		real getAlpha() const override;
		point getPivot() const override;
		ImageFile *getImage() override;

		void setPosition(const point &newPosition) override;
		void setAngle(real newAngle) override;
		void setScale(const point &newScale) override;
		void setAlpha(real newAlpha) override;
		void setPivot(const point &newPivot) override;
		void setImage(ImageFile *newImageFile) override;
		void setSpin(s_int newSpin) override;

		void setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance = 0) override;

		void render() override;

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;


	private:
		point position;
		AngleInfo angle;
		point scale;
		real alpha;
		point pivot;
		ImageFile *imageFile;
	};
}

#endif // SPRITEOBJECTINFO_H
