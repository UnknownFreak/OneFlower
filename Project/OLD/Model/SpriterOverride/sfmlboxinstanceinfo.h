#ifndef SFMLBOXINSTANCEINFO_H
#define SFMLBOXINSTANCEINFO_H

#include "SFML/Graphics/RenderWindow.hpp"

#include "SFML/Graphics/RectangleShape.hpp"

#include "../spriterengine/objectinfo/boxinstanceinfo.h"

namespace SpriterEngine
{
	class SfmlBoxInstanceInfo : public BoxInstanceInfo
	{
	public:
		SfmlBoxInstanceInfo(point initialSize);

		void render() override;

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	private:
		mutable sf::RectangleShape rectangle;
	};
}

#endif // SFMLBOXINSTANCEINFO_H
