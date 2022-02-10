#include "SpriteSheetAnimation.hpp"

SpriteSheetAnimation::SpriteSheetAnimation() : AnimationTime(0), AnimationFrames(0), looping(false)
{
}

sf::IntRect& SpriteSheetAnimation::getCurrentAnimationFrame()
{
	size_t size = AnimationFrames.size();
	if (size != 0)
	{
		size_t pos = (int)(size - (size * (AnimationTime - CurrentTime)));
		if (pos >= size)
			pos = size - 1;
		return AnimationFrames[pos];
	}
	return def;
}