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

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(animation.looping);
		ar(animation.AnimationTime);
		ar(animation.CurrentTime);
		ar(animation.AnimationFrames.size());
		for each (sf::IntRect var in animation.AnimationFrames)
			ar(var.height, var.left, var.top, var.width);
	}
	template<class Archive>
	void load(Archive& ar)
	{
		ar(animation.looping);
		ar(animation.AnimationTime);
		ar(animation.CurrentTime);
		size_t size;
		ar(size);
		for (size_t i = 0; i < size; i++)
		{
			int h, l, t, w;
			ar(h, l, t, w);
			animation.AnimationFrames.push_back(sf::IntRect(l, t, w, h));
		}
	}
private:
	sf::IntRect def = sf::IntRect(0, 0, 0, 0);
	//not required atm.
	//size_t currentAnimationFrame = 0;
};
#endif