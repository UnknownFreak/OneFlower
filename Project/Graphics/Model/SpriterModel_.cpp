#include "SpriterModel_.hpp"

#include <Module\EngineModuleManager.hpp>

Core::uuid Interfaces::Trait<Model::SpriterModel>::typeId = Core::uuid("3208acb2-0dda-4075-8448-f018ac39e3cf");

namespace Model
{
	void SpriterModel::setModel()
	{
		myEntity = Engine::GetModule<SpriterInstanceContainer>().requestModel(fileName, selectedModelName, textureMapId, m_sprite);
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

	SpriterModel::SpriterModel(const SpriterModel & copy) : IModel(copy), fileName(copy.fileName), modelNames(copy.modelNames), selectedModelName(copy.selectedModelName),
		textureMapId(textureMapId)
	{
		setModel();
	}

	SpriterModel & SpriterModel::operator=(const SpriterModel & right)
	{
		if (this == &right)
			return *this;

		ID = right.ID;
		fromMod = right.fromMod;
		mode = right.mode;
		objectVersion = right.objectVersion;

		m_sprite = right.m_sprite;
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

	void SpriterModel::updateFrame(const float& update_ms)
	{
		myEntity->setTimeElapsed(update_ms);
		std::map<Core::String, SpriterAnimationInfo>::iterator it = subInstances.begin();
		std::map<Core::String, SpriterAnimationInfo>::iterator eit = subInstances.end();
		for (; it != eit; it++)
			it->second.updateFrame((size_t)update_ms);
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
	Interfaces::TypeInfo SpriterModel::getTrait() const
	{
		return { Interfaces::Trait<SpriterModel>::typeId, {Interfaces::Trait<IModel>::typeId} };
	}
}