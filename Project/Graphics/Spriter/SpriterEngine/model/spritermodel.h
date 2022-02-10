#ifndef SPRITERMODEL_H
#define SPRITERMODEL_H

#include <vector>

#include "../file/file.h"
#include "../entity/entity.h"

#include "../loading/loader.h"
#include <SFML/Graphics/Sprite.hpp>

class SpriteRef;
namespace SpriterEngine
{
	class FileReference;
	class EntityInstance;
	class FileFactory;
	class ObjectFactory;

	typedef std::vector<File*> FileVector;
	typedef std::vector<Entity*> EntityVector;

	typedef std::vector<s_int> EntityIdVector;

	typedef std::vector<FileReference*> FileReferenceVector;
	typedef std::vector<Core::String> StringVector;

	class SpriterModel
	{
	public:
		SpriterModel(const Core::String &fileName, FileFactory *newFileFactory, ObjectFactory *newObjectFactory, std::shared_ptr<sf::Sprite> sprite);
		SpriterModel(FileFactory *newFileFactory, ObjectFactory *newObjectFactory, std::shared_ptr<sf::Sprite> sprite);
		~SpriterModel();

		EntityInstance *getNewEntityInstance(s_int entityId);
		EntityInstance *getNewEntityInstance(EntityIdVector *entityIds);
		EntityInstance *getNewEntityInstance(Core::String entityName, std::shared_ptr<sf::Sprite> sprite);
		void appendEntityToInstanceByName(EntityInstance * entityInstance, Core::String entityName);
		void setupFileReferences(FileReferenceVector *fileReferences);

		Entity *pushBackEntity(Core::String entityName);
		void pushBackImageFile(Core::String initialFilePath, point initialDefaultPivot);
		void pushBackImageFile(Core::String initialFilePath, point initialDefaultPivot, point size);
		void pushBackSoundFile(Core::String initialFilePath);
		void pushBackTag(Core::String newTag);

		s_int fileCount();

		File * getFileAtIndex(s_int fileIndex);

		const Core::String *getTag(s_int tagIndex);

		void loadFile(const Core::String &fileName);

		StringVector getEntityNames();

	private:
		FileVector files;
		EntityVector entities;
		StringVector tags;

		Loader loader;

		FileFactory *fileFactory;
		ObjectFactory *objectFactory;

		Entity *getEntity(s_int entityId);
		Entity *getEntity(Core::String entityName);

		std::shared_ptr<sf::Sprite> _sprite;

	};
}

#endif // SPRITERMODEL_H
