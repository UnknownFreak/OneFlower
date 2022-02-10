#include "SpriteSheetModel.hpp"
#include <Module\EngineModuleManager.hpp>
#include <Module/Logger/OneLogger.hpp>


Core::uuid Interfaces::Trait<SpriteSheetModel>::typeId = Core::uuid("d2f0bb66-3144-4b7d-b04a-26045f5c1775");

void SpriteSheetModel::del()
{
	delete[] spriteSheetFrames;
}

void SpriteSheetModel::createSpriteSheetFrames(const size_t& size)
{
	spriteSheetSize = size;
	spriteSheetFrames = new sf::IntRect[size];
	//memset is nice but we do not need it and it takes extra time.
	//memset(spriteSheetFrames, 0, sizeof(sf::IntRect)*spriteSheetSize);
}

SpriteSheetModel::SpriteSheetModel() : IModel()
{
	// Use this to set current object version
	objectVersion = OneVersion(1, 0, 0);

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
	objectVersion = right.objectVersion;

	updateRequired = right.updateRequired;
	m_sprite = right.m_sprite;

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
	Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Trying to set animation <" + _animationName + "> on a Sprite Sheet Model.", __FILE__, __LINE__);
	Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Currently Sprite Sheet Model only supports one looping animation.", __FILE__, __LINE__);
}

void SpriteSheetModel::setTextureMap(Core::String modOrigin, Core::String textureMapName)
{
	Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Trying to set texure map <" + modOrigin + ", " + textureMapName + "> on a Sprite Sheet Model.", __FILE__, __LINE__);
	Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Sprite Sheet Model does not support texture maps.", __FILE__, __LINE__);
}

void SpriteSheetModel::updateFrame(const float& update_ms)
{
	// cycle time between animationframes
	// 0 < x < totalTime, can use modulo, but conditional is faster
	_time = fmodf(_time + update_ms,totalAnimationTime);

	if (_time > (currentFrame * frameLength) && lastFrame == currentFrame)
		currentFrame = currentFrame++ % totalAnimationSteps;

	if (lastFrame != currentFrame)
	{
		// paren due to vectorptr
		m_sprite->setTextureRect(*(spriteSheetFrames + currentFrame));
		lastFrame = currentFrame;
	}
}

Interfaces::TypeInfo SpriteSheetModel::getTrait() const
{
	return { Interfaces::Trait<SpriteSheetModel>::typeId , {Interfaces::Trait<IModel>::typeId} };
}
