#include "sfmlboneinstanceinfo.h"

#include "../spriterengine/global/settings.h"

namespace SpriterEngine
{
	SfmlBoneInstanceInfo::SfmlBoneInstanceInfo(point initialSize) :
		BoneInstanceInfo(initialSize)
	{
		boneShape.setPointCount(4);

		boneShape.setPoint(0, sf::Vector2f(0, initialSize.y / 2.0f));
		boneShape.setPoint(1, sf::Vector2f(4, 0));
		boneShape.setPoint(2, sf::Vector2f(initialSize.x, initialSize.y / 2.0f));
		boneShape.setPoint(3, sf::Vector2f(4, initialSize.y));

		boneShape.setOrigin(0, initialSize.y / 2.0f);

		boneShape.setFillColor(sf::Color(0, 0, 255, 50));

		boneShape.setOutlineColor(sf::Color::White);
		boneShape.setOutlineThickness(1);
	}

	void SfmlBoneInstanceInfo::render()
	{
	}
	void SfmlBoneInstanceInfo::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (Settings::renderDebugBones)
		{
			boneShape.setPosition(getPosition().x, getPosition().y);
			boneShape.setRotation(toDegrees(getAngle()));
			boneShape.setScale(getScale().x, getScale().y);
			target.draw(boneShape, states);
		}
	}
}