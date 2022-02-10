#ifndef Globals_HPP
#define Globals_HPP

#include <SFML/Graphics/ConvexShape.hpp>

#include "Interfaces/IEngineModule.hpp"
#include <map>
#include <vector>

#include <File/Resource/RequestorV2.hpp>
#include <Interfaces/IRequestable.hpp>

#include <Helpers/String.hpp>
#include <SFML/Graphics/Font.hpp>

class Globals : public Interfaces::IEngineResource<Globals>
{
	template<class T, class U>
	void putVariableInto(RequestorV2& container, U& containerToPut, const Enums::ObjectType& type)
	{
		std::vector<std::pair<Core::String, Core::uuid>> idVector = container.listAllObjectKeys(type);
		for (std::pair<Core::String, Core::uuid> it : idVector)
		{
			{
				T* ref = container.request<T>({ it.first, it.second });
				if (ref)
					containerToPut.insert({ ref->name, ref->value });
			}
			container.requestRemoval(it.first, it.second);
		}
	}


public:
	static const unsigned MAX_SIZE = 64;
	static const float MAX_SIZE_F;
	static const float Z_OFFSET;
	
	Globals();

	std::map<Core::String, long> longGlobals;
	std::map<Core::String, double> doubleGlobals;
	std::map<Core::String, Core::String> stringGlobals;
	std::map<Core::String, bool> boolGlobals;

	std::map<Core::String, std::vector<Core::String>> stringList;
	std::map<Core::String, std::vector<long>> longList;
	std::map<Core::String, std::vector<double>> doubleList;


	ModFileUUIDHelper newGameWorldInstance;
	ModFileUUIDHelper newGameWorldInstanceLoadingScreen;
	Core::Vector3f newGamePoint;

	static sf::Font font;

	// Inherited via IEngineResource
	Enums::EngineResourceType& getType() const
	{
		return type;
	}

	static const Core::String texturePath;
	static const Core::String uiTexturePath;
	static const Core::String tileTexturePath;

	static sf::ConvexShape shape;

	static const Core::String GLOBAL_DRAW_HITBOX;
	static const Core::String GLOBAL_DRAW_QT;
	static const Core::String LIGHT;

	static const Core::String LOADING_TIMER;
	static const Core::String TOTAL_TIME_LOADED_PART;
	static const Core::String TOTAL_TIME_LOADED;
	static const Core::String B_GLOBAL_LOADINGSCREENINFO;
	static const Core::String B_GLOBAL_SLOW_LOADING;

	static const Core::String B_FORCE_SAME_SEED;
};


#endif
