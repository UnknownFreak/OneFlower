#include "SpriteSheetModel.hpp"

SpriteSheetModel::SpriteSheetModel() : totalAnimationSteps(0)
{
}

void SpriteSheetModel::setAnimation(Core::String)
{
}

void SpriteSheetModel::setTextureMap(Core::String, Core::String)
{
}

void SpriteSheetModel::updateFrame()
{
	// cycle time between animationframes
	// 0 < x < totalTime, can use modulo, but conditional is faster
	_time = _time++ == totalAnimationTime ? 0 : _time++;

	if (_time > (currentFrame * frameLength) && lastFrame == currentFrame)
		currentFrame = currentFrame++ == totalAnimationSteps ? 0 : currentFrame++;

	if (lastFrame != currentFrame)
	{
		// paren due to vectorptr
		m_render_sprite->setTextureRect((*spriteSheetFrames)[currentFrame]);
		lastFrame = currentFrame;
	}
}
