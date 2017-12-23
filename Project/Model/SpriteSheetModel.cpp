#include "SpriteSheetModel.hpp"
#include <Core\IEngineResource\EngineResourceManager.hpp>
#include <Logger\Logger.hpp>

void SpriteSheetModel::del()
{
	delete[] spriteSheetFrames;
}

void SpriteSheetModel::createSpriteSheetFrames(const size_t& size)
{
	spriteSheetSize = size;
	spriteSheetFrames = new sf::IntRect[size];
	//memset is nice but we do not need it.
	//memset(spriteSheetFrames, 0, sizeof(sf::IntRect)*spriteSheetSize);
}

SpriteSheetModel::SpriteSheetModel()
{
	createSpriteSheetFrames(0);
}

SpriteSheetModel::SpriteSheetModel(const SpriteSheetModel & copy) : IModel(copy), totalAnimationSteps(copy.totalAnimationSteps),
totalAnimationTime(copy.totalAnimationTime), currentFrame(copy.currentFrame), lastFrame(copy.lastFrame),
frameLength(copy.frameLength), _time(copy._time)
{
	createSpriteSheetFrames(copy.spriteSheetSize);
	std::memcpy(spriteSheetFrames, copy.spriteSheetFrames, sizeof(sf::IntRect) * spriteSheetSize);

}

SpriteSheetModel & SpriteSheetModel::operator=(const SpriteSheetModel & right)
{
	ID = right.ID;
	mode = right.mode;
	fromMod = right.fromMod;

	updateRequired = right.updateRequired;
	m_render_sprite = right.m_render_sprite;

	createSpriteSheetFrames(right.spriteSheetSize);
	std::memcpy(spriteSheetFrames, right.spriteSheetFrames, sizeof(sf::IntRect) * spriteSheetSize);

	totalAnimationSteps = right.totalAnimationSteps;
	totalAnimationTime = right.totalAnimationTime;
	currentFrame = right.currentFrame;
	lastFrame = right.lastFrame;
	frameLength = right.frameLength;
	_time = right._time;

	return *this;
}

SpriteSheetModel::~SpriteSheetModel()
{
	del();
}

void SpriteSheetModel::setAnimation(Core::String _animationName)
{
	Engine::Get<OneLogger>().Warning("Trying to set animation <" + _animationName + "> on a Sprite Sheet Model.", __FILE__, __LINE__);
	Engine::Get<OneLogger>().Warning("Currently Sprite Sheet Model only supports one looping animation.", __FILE__, __LINE__);
}

void SpriteSheetModel::setTextureMap(Core::String modOrigin, Core::String textureMapName)
{
	Engine::Get<OneLogger>().Warning("Trying to set texure map <" + modOrigin + ", " + textureMapName + "> on a Sprite Sheet Model.", __FILE__, __LINE__);
	Engine::Get<OneLogger>().Warning("Sprite Sheet Model does not support texture maps.", __FILE__, __LINE__);
}

void SpriteSheetModel::updateFrame(const size_t& update_ms)
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
		m_render_sprite->setTextureRect(*(spriteSheetFrames + currentFrame));
		lastFrame = currentFrame;
	}
}
