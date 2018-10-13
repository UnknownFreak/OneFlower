#include "Zone.hpp"
#include <Asset\AssetManagerCore.hpp>
#include <Core\Component\GameObject.h>

#include <SFML\Graphics\RenderTarget.hpp>

//void Zone::placeChunks()
//{
//	if (chunk_count_x == 0 && chunk_count_y == 0)
//	{
//		chunkList.push_back(Chunk());
//		chunks.insert(&chunkList.rbegin().operator*());
//	}
//}


Zone::Zone(Zone &z) : IRequestable(z),  name(z.name), background(z.background), loadScreen(z.loadScreen), loadingScreenMessage(z.loadingScreenMessage), chunks(Chunk::size * 50, Chunk::size * 50)
{
	for (size_t i = 0; i < z.objects.size(); i++)
		this->objects.push_back(z.objects[i]);
}

Zone::Zone() : Zone(0, 0)
{
}

Zone::Zone(const size_t chunk_count_x, const size_t chunk_count_y) : IRequestable(), name(""), chunks(Chunk::size * 50, Chunk::size * 50),
chunk_count_x(chunk_count_x), chunk_count_y(chunk_count_y)
{
	//placeChunks();
}

Zone::~Zone()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		delete objects[i].second;
		objects[i].second = nullptr;
	}
	objects.empty();
}

Zone& Zone::operator=(const Zone &z)
{
	name = z.name;
	fromMod = z.fromMod;
	ID = z.ID;
	mode = z.mode;
	background = z.background;
	loadScreen = z.loadScreen;
	loadingScreenMessage = z.loadingScreenMessage;
	for (size_t i = 0; i < z.objects.size(); i++)
		objects.push_back(z.objects[i]);

	return *this;
}

void Zone::update()
{

}

Core::String& Zone::getName()
{
	return name;
}

BackgroundSprite* Zone::getBackground()
{
	return &background;
}

BackgroundSprite* Zone::getLoadingScreen()
{
	return &loadScreen;
}

const Core::String& Zone::getLoadingScreenMessage() const
{
	return loadingScreenMessage;
}

#ifdef _DEBUG

void Zone::setBackground(Core::String _name)
{
	background.name = _name;
	background.sprite.setTexture(Engine::GetModule<Asset::AssetManager>().textureloader.requestTexture(_name));
}

void Zone::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background.sprite, states);
	target.draw(chunks, states);
}

#endif