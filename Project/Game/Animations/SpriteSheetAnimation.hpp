#ifndef SPRITESHEETANIMATION_HPP
#define	SPRITESHEETANIMATION_HPP

#include <SFML\Graphics\Rect.hpp>
#include <vector>

struct SpriteSheetAnimation
{
	SpriteSheetAnimation();
	sf::IntRect& getCurrentAnimationFrame();

	double AnimationTime;
	double CurrentTime;
	std::vector<sf::IntRect> AnimationFrames;
	bool looping;

private:
	//not required atm.
	//size_t currentAnimationFrame = 0;
};
#endif