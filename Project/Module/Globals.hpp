#ifndef Globals_HPP
#define Globals_HPP

#include <glm/vec3.hpp>

#include <module/IEngineModule.hpp>
#include <module/ModuleManager.hpp>
#include <map>
#include <vector>

#include <file/archive/Requestor.hpp>
#include <file/archive/Requestable.hpp>

#include <utils/common/String.hpp>

class Globals : public of::module::interface::IEngineResource<Globals>
{
	template<class T, class U>
	void putVariableInto(of::file::archive::Requestor& container, U& containerToPut, const of::file::ObjectType& type)
	{
		std::vector<of::file::FileId> idVector = container.listAllObjectKeys(type);
		for (auto& it : idVector)
		{
			{
				T* ref = container.request<T>(it);
				if (ref)
					containerToPut.insert({ ref->name, ref->value });
			}
			container.requestRemoval(it);
		}
	}


public:
	static const unsigned MAX_SIZE = 64;
	static const float MAX_SIZE_F;
	static const float Z_OFFSET;
	
	Globals();

	std::map<of::common::String, long> longGlobals;
	std::map<of::common::String, double> doubleGlobals;
	std::map<of::common::String, of::common::String> stringGlobals;
	std::map<of::common::String, bool> boolGlobals;

	std::map<of::common::String, std::vector<of::common::String>> stringList;
	std::map<of::common::String, std::vector<long>> longList;
	std::map<of::common::String, std::vector<double>> doubleList;


	of::file::FileId newGameWorldInstance;
	of::file::FileId newGameWorldInstanceLoadingScreen;
	glm::vec3 newGamePoint;

	// Inherited via IEngineResource
	of::module::EngineResourceType& getType() const
	{
		return type;
	}

	static const of::common::String texturePath;
	static const of::common::String skyboxTexturePath;
	static const of::common::String uiTexturePath;
	static const of::common::String tileTexturePath;
	static const of::common::String meshPath;
	static const of::common::String shaderPath;

	static const of::common::String GLOBAL_DRAW_HITBOX;
	static const of::common::String GLOBAL_DRAW_QT;
	static const of::common::String LIGHT;

	static const of::common::String LOADING_TIMER;
	static const of::common::String TOTAL_TIME_LOADED_PART;
	static const of::common::String TOTAL_TIME_LOADED;
	static const of::common::String B_GLOBAL_LOADINGSCREENINFO;
	static const of::common::String B_GLOBAL_SLOW_LOADING;

	static const of::common::String B_FORCE_SAME_SEED;
};


#endif
