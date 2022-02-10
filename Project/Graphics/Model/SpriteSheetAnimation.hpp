#ifndef SPRITESHEETANIMATION_HPP
#define	SPRITESHEETANIMATION_HPP

#include <Helpers/Rect.hpp>
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

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(looping);
		ar(AnimationTime);
		ar(CurrentTime);
		ar(AnimationFrames.size());
		for(sf::IntRect var : AnimationFrames)
			ar(var.height, var.left, var.top, var.width);
	}
	template<class Archive>
	void load(Archive& ar)
	{
		ar(looping);
		ar(AnimationTime);
		ar(CurrentTime);
		size_t size;
		ar(size);
		for (size_t i = 0; i < size; i++)
		{
			int h, l, t, w;
			ar(h, l, t, w);
			AnimationFrames.push_back(sf::IntRect(l, t, w, h));
		}
	}
private:
	sf::IntRect def = sf::IntRect(0, 0, 0, 0);
	//not required atm.
	//size_t currentAnimationFrame = 0;
};
#endif