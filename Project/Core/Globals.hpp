#ifndef Globals_HPP
#define Globals_HPP
#include "IEngineResource\IEngineResource.hpp"

#include <map>
#include <vector>

#include <AssetManager\Requestor\Requestor.hpp>
#include <AssetManager\IRequestable.hpp>

#include "String.hpp"

class Globals : public IEngineResource<Globals>
{


	template<class T, class U> 
	void putVariableInto(Requestor<T>& container, U& containerToPut)
	{
		std::vector<std::pair<Core::String, size_t>> idVector = container.listAllObjectKeys();
		for each (std::pair<Core::String, size_t> it in idVector)
		{
			{
				Reference<T>*& ref = container.request(it.first, it.second);
				T ps = ref->getUnique();
				containerToPut.insert({ ps.name, ps.value });
			}
			container.requestRemoval(it.first, it.second);
		}
	}

public:
	Globals();

	std::map<Core::String, long> longGlobals;
	std::map<Core::String, double> doubleGlobals;
	std::map<Core::String, Core::String> stringGlobals;

	std::map<Core::String, std::vector<Core::String>> stringList;
	std::map<Core::String, std::vector<long>> longList;
	std::map<Core::String, std::vector<double>> doubleList;

	// Inherited via IEngineResource
	virtual const ResourceType & getType() override;

};


#endif
