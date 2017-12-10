#ifndef SPRITESHEETMODEL_HPP
#define SPRITESHEETMODEL_HPP
#include "IModel.hpp"

class SpriteSheetModel : public IModel
{

	std::vector<sf::IntRect> const * spriteSheetFrames;

	// how many frames in animation
	size_t totalAnimationSteps = 0;
	// total animation time
	double totalAnimationTime = 0;
	
	// which frame we at
	size_t currentFrame = 0;
	size_t lastFrame = 0;
	// length of each frame (total / steps)
	double frameLength = 0;

	double _time = 0;

public:

	SpriteSheetModel();

	// Inherited via IModel
	virtual void setAnimation(Core::String) override;
	virtual void setTextureMap(Core::String, Core::String) override;

	template<class Archive>
	void save(Archive& _save) const
	{
		//ar(spriteSheetFrames.size());
		//std::vector<sf::IntRect>::const_iterator it = spriteSheetFrames.begin();
		//std::vector<sf::IntRect>::const_iterator eit = spriteSheetFrames.end();
		//
		//for (it; it != eit; it++)
		//{
		//	ar(it->left, it->top, it->width, it->height);
		//}
		//
		//ar(totalAnimationTime);
		//ar(_time)
	}

	template<class Archive>
	void load(Archive& _load)
	{
		//ar(totalAnimationSteps);
		//size_t it = 0;
		//
		//size_t l, t, w, h;
		//for (it; it < totalAnimationSteps; it++)
		//{
		//	ar(l, t, w, h);
		//	spriteSheetFrames.push_back(sf::IntRect(l, t, w, h));
		//}
		//
		//ar(totalAnimationTime);
		//ar(_time);
		//frameLength = totalAnimationTime / totalAnimationSteps;
	}

protected:

	// Inherited via IModel
	virtual void updateFrame(const double& update_ms) override;
};

#endif