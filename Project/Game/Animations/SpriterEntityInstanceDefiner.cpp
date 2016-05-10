#include "SpriterEntityInstance.hpp"
#include "../../Engine.hpp"
SpriterEntityInstance::SpriterEntityInstance(SpriterEngine::EntityInstance* myEntity, SpriterTextureMapper* textureMap) :
MyEntityInstance(myEntity), textureMaps(textureMap)
{

}
SpriterEntityInstance::~SpriterEntityInstance()
{
	if (MyEntityInstance)
		delete MyEntityInstance;
	// TextureMaps will always be deleted from the modelcontainer
	// so there is no need to delete it here
}
SpriterEntityInstance::SpriterEntityInstance()
{

}
SpriterEntityInstance::SpriterEntityInstance(const SpriterEntityInstance &copy):
myTextureMap(copy.myTextureMap), entityName(copy.entityName), sceneFile(copy.sceneFile),
textureMaps(copy.textureMaps)
{
	MyEntityInstance = Engine::ModelContainer.getModel(sceneFile).getNewEntityInstance(entityName);
	textureMaps = Engine::ModelContainer.requestTextureMapper(sceneFile);
}
SpriterEntityInstance& SpriterEntityInstance::operator = (const SpriterEntityInstance& right)
{
	entityName = right.entityName;
	myTextureMap = right.myTextureMap;
	sceneFile = right.sceneFile;
	textureMaps = Engine::ModelContainer.requestTextureMapper(sceneFile);
	MyEntityInstance = Engine::ModelContainer.getModel(sceneFile).getNewEntityInstance(entityName);
	return *this;
}
void SpriterEntityInstance::render(sf::Sprite* sprite)
{
	if (MyEntityInstance)
	{
		textureMaps->setTextureMapAndSprite(myTextureMap, sprite);
		MyEntityInstance->setCurrentTime(MyEntityInstance->getCurrentTime());
		MyEntityInstance->render();
	}
}