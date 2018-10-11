#ifndef TextureRef_HPP
#define TextureRef_HPP

#include<SFML\Graphics\Texture.hpp>
#include <Core/String.hpp>
#ifndef _EDITOR_
#include<future>
#endif
class TextureRef
{
	friend class TextureLoader;
#ifdef _EDITOR_
	sf::Texture myTexture;
#else
	std::shared_future<sf::Texture> myTexture;
#endif
public:
	TextureRef(Core::String name);
	TextureRef(const TextureRef& copy);
	TextureRef& operator=(const TextureRef& copy);
	const sf::Texture* getTexture();
	bool isValid();
	
	size_t useCount = 0;
	Core::String name;
#ifdef _EDITOR_
	void setNewFuture(sf::Texture future);
#else
	void setNewFuture(std::shared_future<sf::Texture> future);

#endif
	void reloadTexture();
};

#endif