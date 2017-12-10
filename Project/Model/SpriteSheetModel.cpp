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

void SpriteSheetModel::updateFrame(const double& update_ms)
{
	// cycle time between animationframes
	// 0 < x < totalTime, can use modulo, but conditional is faster
	if (_time == totalAnimationTime)
		_time = 0;
	else
		_time+=update_ms;

	if (_time > (currentFrame * frameLength) && lastFrame == currentFrame)
		currentFrame = currentFrame++ == totalAnimationSteps ? 0 : currentFrame++;

	if (lastFrame != currentFrame)
	{
		// paren due to vectorptr
		m_render_sprite->setTextureRect((*spriteSheetFrames)[currentFrame]);
		lastFrame = currentFrame;
	}
}
