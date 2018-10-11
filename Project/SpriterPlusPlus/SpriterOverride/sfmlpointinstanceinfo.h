#ifndef SFMLPOINTINSTANCEINFO_H
#define SFMLPOINTINSTANCEINFO_H

#include "SFML/Graphics/RenderWindow.hpp"

#include "SFML/Graphics/CircleShape.hpp"

#include "../spriterengine/objectinfo/pointinstanceinfo.h"

namespace SpriterEngine
{
	class SfmlPointInstanceInfo : public PointInstanceInfo
	{
	public:
		SfmlPointInstanceInfo();

		void render() override;

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	private:
		mutable sf::CircleShape circle;
	};
}

#endif // SFMLPOINTINSTANCEINFO_H
