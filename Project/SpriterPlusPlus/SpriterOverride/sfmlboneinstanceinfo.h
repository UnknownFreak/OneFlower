#ifndef SFMLBONEINSTANCEINFO_H
#define SFMLBONEINSTANCEINFO_H

#include "SFML/Graphics/RenderWindow.hpp"

#include "SFML/Graphics/ConvexShape.hpp"

#include "../spriterengine/objectinfo/boneinstanceinfo.h"

namespace SpriterEngine
{
	class SfmlBoneInstanceInfo : public BoneInstanceInfo
	{
	public:
		SfmlBoneInstanceInfo(point initialSize);

		void render() override;

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	private:
		mutable sf::ConvexShape boneShape;
	};
}

#endif // SFMLBONEINSTANCEINFO_H
