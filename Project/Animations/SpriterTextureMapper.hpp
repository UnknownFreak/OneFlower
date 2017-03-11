#ifndef SPRITERTEXTUREMAPPER_HPP
#define	SPRITERTEXTUREMAPPER_HPP

#include "TextureMap.hpp"
#include <AssetManager\SpriteRef.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <map>
//included via TextureMap
//#include <Core\String.hpp>
class SpriterTextureMapper
{
public:

	SpriterTextureMapper(sf::RenderWindow& renderWindow);

	void setTextureMap(std::pair<Core::String, Core::String> newTextureMap);
	void setSpritePointer(SpriteRef* sprite);
	void setTextureMapAndSprite(std::pair<Core::String, Core::String> newTextureMap, SpriteRef* sprite);

	void setRenderWindow(sf::RenderWindow* newRenderWindow);

	sf::RenderWindow* renderWindow;
	std::pair<Core::String, Core::String> currentTextureMapString;
	TextureMap* currentTextureMap;
	std::map<std::pair<Core::String, Core::String>, TextureMap> textureMaps;

	SpriteRef* currentSprite;

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(currentTextureMapString.first, currentTextureMapString.second);
		std::map < std::pair<std::string, std::string>, TextureMap> theStuffWeWillActuallySave;
		for (std::map<std::pair<std::string, std::string>, TextureMap>::const_iterator it = textureMaps.begin();
			it != textureMaps.end(); it++)
		{

			if (it->second.mode == ObjectSaveMode::DEFAULT)
			{
				if (it->second.modName == AssetManagerCore::openedMod || it->second.modName == "DEFAULT")
				{
					theStuffWeWillActuallySave.insert(std::pair<std::pair<std::string, std::string >, TextureMap>(it->first, it->second));
				}
			}
			else if (it->second.mode == ObjectSaveMode::REMOVE)
			{
				if (it->second.modName != AssetManagerCore::openedMod)
				{
					theStuffWeWillActuallySave.insert(std::pair<std::pair<std::string, std::string >, TextureMap>(it->first, it->second));
				}
			}
			else if (it->second.mode == ObjectSaveMode::EDIT)
			{
				TextureMap tex = it->second;
				if (it->second.modName == AssetManagerCore::openedMod || it->second.modName == "DEFAULT")
				{
					tex.mode = ObjectSaveMode::DEFAULT;
				}
				theStuffWeWillActuallySave.insert(std::pair<std::pair<std::string, std::string >, TextureMap>(it->first, tex));
			}
			else if (it->second.mode == ObjectSaveMode::ADD)
			{
				TextureMap tex = it->second;
				if (it->second.modName == AssetManagerCore::openedMod)
				{
					tex.mode = ObjectSaveMode::DEFAULT;
				}
				theStuffWeWillActuallySave.insert(std::pair<std::pair<std::string, std::string >, TextureMap>(it->first, tex));
			}
		}
		ar(theStuffWeWillActuallySave.size());
		for (std::map<std::pair<std::string, std::string>, TextureMap>::iterator i = theStuffWeWillActuallySave.begin(); i != theStuffWeWillActuallySave.end(); i++)
		{
			ar(i->first.first);
			ar(i->first.second);
			ar(i->second);
		}
	}

	template<class Archive>
	void load(Archive& ar)
	{
		std::string modName, mapName;
		ar(modName, mapName);
		size_t size;
		ar(size);
		for (size_t i = 0; i < size; i++)
		{
			std::string name = "OneFlower.main";
			std::string name2 = "Default";
			TextureMap tex;
			ar(name);
			ar(name2);
			ar(tex);
			if (tex.mode == ObjectSaveMode::REMOVE)
			{
				if (textureMaps.find(std::pair<std::string, std::string>(name, name2)) != textureMaps.end())
					textureMaps.erase(textureMaps.find(std::pair<std::string, std::string>(name, name2)));
			}
			else if (tex.mode == ObjectSaveMode::EDIT)
			{
				if (textureMaps.find(std::pair<std::string, std::string>(name, name2)) != textureMaps.end())
					textureMaps[std::pair<std::string, std::string>(name, name2)].TexturePoints = tex.TexturePoints;
			}
			else
			{
				if (textureMaps.find({ name, name2 }) != textureMaps.end())
					textureMaps.at({ name, name2 }) = tex;
				else
					textureMaps.insert(std::pair<std::pair<std::string, std::string>, TextureMap>({ name, name2 }, tex));
			}
		}
		setTextureMap({ modName, mapName });
	}
private:
	SpriteRef DefaultSprite;
};

#endif