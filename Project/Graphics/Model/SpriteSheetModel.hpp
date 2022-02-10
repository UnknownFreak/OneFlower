#ifndef SPRITESHEETMODEL_HPP
#define SPRITESHEETMODEL_HPP
#include "IModel.hpp"

class SpriteSheetModel : public IModel
{

	sf::IntRect * spriteSheetFrames; // not null
	size_t spriteSheetSize = 1;

	// how many frames in animation
	size_t totalAnimationSteps = 0;
	// total animation time in s
	float totalAnimationTime = 0.f;
	
	// which frame we at
	size_t currentFrame = 0;
	size_t lastFrame = 0;
	// length of each frame (total / steps)
	float frameLength = 0;

	float _time = 0;

	void del();
	void createSpriteSheetFrames(const size_t& size);
public:

	SpriteSheetModel();
	SpriteSheetModel(const SpriteSheetModel& copy);
	SpriteSheetModel& operator=(const SpriteSheetModel& right);

	~SpriteSheetModel();

	// Inherited via IModel
	virtual void setAnimation(Core::String) override;
	virtual void setTextureMap(Core::String, Core::String) override;

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(spriteSheetSize);
		size_t it = 0;
		for (it; it != spriteSheetSize; it++)
		{
			ar((spriteSheetFrames + it)->left, (spriteSheetFrames + it)->top, (spriteSheetFrames + it)->width, (spriteSheetFrames + it)->height);
		}
		ar(totalAnimationSteps);
		ar(totalAnimationTime);
		ar(_time);
	}

	template<class Archive>
	void load(Archive& ar)
	{
		del();
		ar(spriteSheetSize);
		createSpriteSheetFrames(spriteSheetSize);
		
		size_t it = 0;
		int l, t, w, h;
		for (it; it < spriteSheetSize; it++)
		{
			ar(l, t, w, h);
			(spriteSheetFrames + it)->left = l;
			(spriteSheetFrames + it)->top= t;
			(spriteSheetFrames + it)->width = w;
			(spriteSheetFrames + it)->height = h;
		}
		ar(totalAnimationSteps);
		ar(totalAnimationTime);
		ar(_time);
		frameLength = totalAnimationTime / totalAnimationSteps;
	}

protected:

	// Inherited via IModel
	virtual void updateFrame(const float& update_ms) override;
	// Inherited via IRequestable
	virtual Interfaces::TypeInfo getTrait() const override;
};

#endif