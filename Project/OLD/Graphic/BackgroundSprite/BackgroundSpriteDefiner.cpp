#include "BackgroundSprite.hpp"
#include <AssetManager\AssetManagerCore.hpp>

BackgroundSprite::BackgroundSprite(const Core::String n, const Core::Vector2 pos) : BackgroundSprite(n, pos.x, pos.y, 0, 0)
{
}
BackgroundSprite::BackgroundSprite(const Core::String n, const float x, const float y) : BackgroundSprite(n, x, y, 0, 0)
{
}
BackgroundSprite::BackgroundSprite(const Core::String n, const float x, const float y, const int sizeX, const int sizeY) : name(n), position(x, y), size(sizeX, sizeY)
{
	sprite.setTexture(Engine::Get<AssetManager>().textureloader.requestTexture(n));
	sprite.setPosition(x, y);
}
BackgroundSprite::BackgroundSprite(const DBBackgroundSprite & DbBackground) : BackgroundSprite(DbBackground.name, DbBackground.position.x, DbBackground.position.y,
	DbBackground.size.x, DbBackground.size.y)
{
	setSize(size);
}
BackgroundSprite::BackgroundSprite(const BackgroundSprite &BackgroundSprite) : BackgroundSprite(BackgroundSprite.name, BackgroundSprite.position.x,
	BackgroundSprite.position.y, BackgroundSprite.size.x, BackgroundSprite.size.y)
{
	setSize(size);
}
BackgroundSprite& BackgroundSprite::operator=(const BackgroundSprite &BackgroundSprite)
{
	name = BackgroundSprite.name;
	position = BackgroundSprite.position;
	size = BackgroundSprite.size;
	sprite.setTexture(Engine::Get<AssetManager>().textureloader.requestTexture(name));
	setPosition(position.x, position.y);
	return *this;
}
void BackgroundSprite::setRepeated(bool b)
{
	sf::Texture *tmp = (sf::Texture*)sprite.getTexture();
	tmp->setRepeated(b);
}
void BackgroundSprite::setPosition(int x, int y)
{
	position.x = (float)x;
	position.y = (float)y;
	sprite.setPosition(position.x, position.y);
}
void BackgroundSprite::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	sprite.setPosition(x, y);
}

void BackgroundSprite::setSize(Core::Vector2i size)
{
	// size is not zero
	if (this->size.x && this->size.y)
		sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}
