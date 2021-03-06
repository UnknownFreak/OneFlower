#include "sfmlpointinstanceinfo.h"

#include "../spriterengine/global/settings.h"

namespace SpriterEngine
{
	SfmlPointInstanceInfo::SfmlPointInstanceInfo() :
		circle(10)
	{
		circle.setFillColor(sf::Color::Red);
		circle.setOrigin(5, 5);
	}

	void SfmlPointInstanceInfo::render()
	{

	}
	void SfmlPointInstanceInfo::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (Settings::renderDebugPoints)
		{
			circle.setPosition(getPosition().x, getPosition().y);
			circle.setRotation(toDegrees(getAngle()));
			target.draw(circle, states);
		}
	}
}