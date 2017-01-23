#ifndef TextureRef_HPP
#define TextureRef_HPP

#include<SFML\Graphics\Texture.hpp>
#include<future>

class TextureRef
{
	friend class TextureLoader;
	std::shared_future<sf::Texture> myTexture;
public:
	TextureRef(std::string name);
	TextureRef(const TextureRef& copy);

	const sf::Texture* getTexture();
	bool isReady();
	
	size_t useCount = 0;
	std::string name;

	void setNewFuture(std::shared_future<sf::Texture> future);
	void reloadTexture();
};

#endif