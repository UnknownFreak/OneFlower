#include "spritermodel.h"

#include "../global/settings.h"

#include "../entity/entityinstance.h"

#include "../override/imagefile.h"
#include "../override/soundfile.h"
#include "../override/filefactory.h"
#include "../override/objectfactory.h"

#include "../file/filereference.h"

namespace SpriterEngine
{
	SpriterModel::SpriterModel(const Core::String & fileName, FileFactory * newFileFactory, ObjectFactory * newObjectFactory, std::shared_ptr<sf::Sprite> sprite) :
		SpriterModel(newFileFactory, newObjectFactory, sprite)
	{
		loadFile(fileName);
	}

	SpriterModel::SpriterModel(FileFactory * newFileFactory, ObjectFactory * newObjectFactory, std::shared_ptr<sf::Sprite> sprite) :
		fileFactory(newFileFactory),
		objectFactory(newObjectFactory),
		loader(newFileFactory), _sprite(sprite)
	{
	}

	SpriterModel::~SpriterModel()
	{
		for (auto& it : files)
		{
			delete it;
		}
		for (auto& it : entities)
		{
			delete it;
		}

		if (fileFactory)
		{
			delete fileFactory;
		}

		if (objectFactory)
		{
			delete objectFactory;
		}
	}

	EntityInstance *SpriterModel::getNewEntityInstance(s_int entityId)
	{
		if (entityId < entities.size())
		{
			return entities.at(entityId)->getNewEntityInstance(this, objectFactory);
		}
		else
		{
			Settings::error("SpriterModel::getNewEntityInstance - entity id " + std::to_string(entityId) + " out of range");
			return 0;
		}
	}

	EntityInstance * SpriterModel::getNewEntityInstance(EntityIdVector * entityIds)
	{
		EntityInstance *newEntityInstance = new EntityInstance();
		for (auto& it : *entityIds)
		{
			Entity *entity = getEntity(it);
			if (entity)
			{
				newEntityInstance->appendEntity(this, entity, objectFactory);
			}
			else
			{
				Settings::error("SpriterModel::getNewEntityInstance - could not find entity with id " + std::to_string(it));
			}
		}
		return newEntityInstance;
	}

	void SpriterModel::appendEntityToInstanceByName(EntityInstance *entityInstance, Core::String entityName)
	{
		if (entityInstance)
		{
			Entity *entity = getEntity(entityName);
			if (entity)
			{
				entityInstance->appendEntity(this, entity, objectFactory);
			}
			else
			{
				Settings::error("SpriterModel::appendEntityToInstanceByName - no entityInstance provided \"" + entityName + "\"");
			}
		}
		else
		{
			Settings::error("SpriterModel::appendEntityToInstanceByName - no entityInstance provided \"" + entityName + "\"");
		}
	}

	EntityInstance * SpriterModel::getNewEntityInstance(Core::String entityName, std::shared_ptr<sf::Sprite> sprite)
	{
		_sprite = sprite;
		for (auto& it : entities)
		{
			if (it->getName() == entityName)
			{
				return it->getNewEntityInstance(this, objectFactory);
			}
		}
		Settings::error("SpriterModel::getNewEntityInstance - could not find entity with name \"" + entityName + "\"");
		return 0;
	}

	void SpriterModel::setupFileReferences(FileReferenceVector *fileReferences)
	{
		for (auto& it : files)
		{
			fileReferences->push_back(new FileReference(it));
		}
	}

	Entity *SpriterModel::pushBackEntity(Core::String entityName)
	{
		entities.push_back(new Entity(entityName, entities.size(), &files));
		return entities.back();
	}

	void SpriterModel::pushBackImageFile(Core::String initialFilePath, point initialDefaultPivot)
	{
		files.push_back(fileFactory->newImageFile(initialFilePath, initialDefaultPivot, _sprite));
	}
	void SpriterModel::pushBackImageFile(Core::String initialFilePath, point initialDefaultPivot, point size)
	{
		files.push_back(fileFactory->newImageFile(initialFilePath, initialDefaultPivot, size, _sprite));
	}
	void SpriterModel::pushBackSoundFile(Core::String initialFilePath)
	{
		files.push_back(fileFactory->newSoundFile(initialFilePath));
	}

	void SpriterModel::pushBackTag(Core::String newTag)
	{
		tags.push_back(newTag);
	}

	s_int SpriterModel::fileCount()
	{
		return files.size();
	}

	File * SpriterModel::getFileAtIndex(s_int fileIndex)
	{
		if (fileIndex >= 0 && fileIndex < files.size())
		{
			return files.at(fileIndex);
		}
		else
		{
			return 0;
		}
	}

	const Core::String * SpriterModel::getTag(s_int tagIndex)
	{
		if (tagIndex < tags.size())
		{
			return &tags.at(tagIndex);
		}
		else
		{
			Settings::error("SpriterModel::getTag - tag index " + std::to_string(tagIndex) + " out of range");
			return 0;
		}
	}

	void SpriterModel::loadFile(const Core::String & fileName)
	{
		loader.loadFile(this, fileName);
	}

	Entity * SpriterModel::getEntity(s_int entityId)
	{
		if (entityId < entities.size())
		{
			return entities.at(entityId);
		}
		else
		{
			Settings::error("SpriterModel::getEntity - entity id " + std::to_string(entityId) + " out of range");
			return 0;
		}
	}

	Entity * SpriterModel::getEntity(Core::String entityName)
	{
		for (auto& it : entities)
		{
			if (it->getName() == entityName)
			{
				return it;
			}
		}
		Settings::error("SpriterModel::getEntity - could not find entity with name \"" + entityName + "\"");
		return 0;
	}

	StringVector SpriterModel::getEntityNames()
	{
		StringVector v;
		for (auto& it : entities)
		{
			v.push_back(it->getName());
		}
		return v;
	}
}
