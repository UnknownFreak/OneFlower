#include "BackgroundSprite.hpp"
#include <AssetManager\AssetManagerCore.hpp>

/*
BackgroundSprite::BackgroundSprite()
{
name = "test.png";
spritesetTexture(*Engine::Graphic.requestTexture("test.png"));
//sprite.setOrigin(spritegetTextureRect().width / 2,spritegetTextureRect().height / 2);
sizeX = 0;
sizeY = 0;
}
//*/
BackgroundSprite::BackgroundSprite(Core::String n, Core::Vector2 pos) : name(n), position(pos), size(0, 0)
{
	sprite.setTexture(Engine::Get<AssetManager>().textureloader.requestTexture(n));
	setPosition(position.x, position.y);
}
BackgroundSprite::BackgroundSprite(Core::String n, float x, float y) : name(n), position(x, y), size(0, 0)
{
	sprite.setTexture(Engine::Get<AssetManager>().textureloader.requestTexture(n));
	sprite.setPosition(x, y);
}
BackgroundSprite::BackgroundSprite(const DBBackgroundSprite & DbBackground) :  name(DbBackground.name) , position(DbBackground.position), size(DbBackground.size)
{
	sprite.setTexture(Engine::Get<AssetManager>().textureloader.requestTexture(name));
	setPosition(position.x, position.y);
	setSize(size);
}
BackgroundSprite::BackgroundSprite(const BackgroundSprite &BackgroundSprite) : name(BackgroundSprite.name), position(BackgroundSprite.position), size(BackgroundSprite.size)
{
	sprite.setTexture(Engine::Get<AssetManager>().textureloader.requestTexture(name));
	setPosition(position.x, position.y);
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
