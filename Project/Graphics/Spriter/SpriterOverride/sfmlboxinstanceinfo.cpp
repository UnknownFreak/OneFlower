#include "sfmlboxinstanceinfo.h"

#include "../spriterengine/global/settings.h"

namespace SpriterEngine
{
	SfmlBoxInstanceInfo::SfmlBoxInstanceInfo(point initialSize) :
		BoxInstanceInfo(initialSize),
		rectangle(sf::Vector2f(initialSize.x, initialSize.y))
	{
	}

	void SfmlBoxInstanceInfo::render()
	{
		
	}
	void SfmlBoxInstanceInfo::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (Settings::renderDebugBoxes)
		{
			rectangle.setPosition(getPosition().x, getPosition().y);
			rectangle.setRotation(toDegrees(getAngle()));
			rectangle.setScale(getScale().x, getScale().y);
			rectangle.setOrigin(getPivot().x*getSize().x, getPivot().y*getSize().y);
			target.draw(rectangle, states);
		}
	}
}