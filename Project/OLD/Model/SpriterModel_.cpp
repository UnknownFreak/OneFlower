#include "SpriterModel_.hpp"

#include <Core\IEngineResource\EngineResourceManager.hpp>

#include <Graphic\Time\Time.hpp>

namespace Model
{
	void SpriterModel::setModel()
	{
		myEntity = Engine::Get<SpriterInstanceContainer>().requestModel(fileName, selectedModelName, textureMapId, m_render_sprite);
	}

	SpriterModel::SpriterModel() : myEntity(nullptr)
	{
		objectVersion = OneVersion(1, 0, 0);
	}

	SpriterModel::~SpriterModel()
	{
		if (myEntity)
		{
			delete myEntity;
			myEntity = nullptr;
		}
	}

	//SpriterModel::SpriterModel(const SpriterModel & copy) : IModel(copy), fileName(copy.fileName), modelNames(copy.modelNames), selectedModelName(copy.selectedModelName),
	//	textureMapId(textureMapId)
	//{
	//	setModel();
	//}

	SpriterModel & SpriterModel::operator=(const SpriterModel & right)
	{
		if (this == &right)
			return *this;

		ID = right.ID;
		fromMod = right.fromMod;
		mode = right.mode;
		objectVersion = right.objectVersion;

		m_render_sprite = right.m_render_sprite;
		updateRequired = right.updateRequired;

		fileName = right.fileName;
		modelNames = right.modelNames;
		selectedModelName = right.selectedModelName;
		textureMapId = right.textureMapId;
		
		if (myEntity)
			delete myEntity;

		setModel();

		return *this;
	}

	bool SpriterModel::isFaceable()
	{
		return true;
	}

	void SpriterModel::updateFrame(const size_t& update_ms)
	{
		myEntity->setTimeElapsed(update_ms/10.0);
		std::map<Core::String, SpriterAnimationInfo>::iterator it = subInstances.begin();
		std::map<Core::String, SpriterAnimationInfo>::iterator eit = subInstances.end();
		for (; it != eit; it++)
			it->second.updateFrame(update_ms);
	}

	void SpriterModel::setAnimation(Core::String _animation)
	{
		Core::String modelName = "default";
		if (modelName != "default")
			subInstances[modelName].setAnimation(_animation);
		else
			myEntity->setCurrentAnimation(_animation);
	}

	void SpriterModel::setTextureMap(Core::String _modOrigin, Core::String _textureMapName)
	{
	}

	void SpriterModel::setPosition(const Core::Vector2 & vec)
	{
		myEntity->setPosition(vec);
	}

	void SpriterModel::setRotation(const float rot)
	{
		myEntity->setAngle(rot);
	}

	void SpriterModel::setScale(const Core::Vector2 & scale)
	{
		myEntity->setScale(scale);
	}

	void SpriterModel::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(*myEntity, states);
	}
}