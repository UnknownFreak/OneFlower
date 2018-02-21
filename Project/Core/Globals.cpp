#include "Globals.hpp"

#include <AssetManager\AssetManagerCore.hpp>

#include "IEngineResource\EngineResourceManager.hpp"

ResourceType IEngineResource<Globals>::type = ResourceType::Globals;

Globals::Globals()
{
	AssetManager& am = Engine::Get <AssetManager>();
	std::vector<std::pair<Core::String, size_t>> intObjects = am.getIntRequestor().listAllObjectKeys();
	std::vector<std::pair<Core::String, size_t>> doubleObjects = am.getDoubleRequestor().listAllObjectKeys();
	std::vector<std::pair<Core::String, size_t>> stringObjects = am.getStringRequestor().listAllObjectKeys();

	for each(std::pair<Core::String, size_t> it in intObjects)
	{
		{
			Reference<PrimitiveSaveable<int>>*& ref = am.getIntRequestor().request(it.first, it.second);
			PrimitiveSaveable<int> ps = ref->getUnique();
			longGlobals.insert({ ps.name, ps.value });
		}
		am.getIntRequestor().requestRemoval(it.first, it.second);
	}
	for each(std::pair<Core::String, size_t> it in doubleObjects)
	{
		{
			Reference<PrimitiveSaveable<double>>*& ref = am.getDoubleRequestor().request(it.first, it.second);
			PrimitiveSaveable<double> ps = ref->getUnique();
			doubleGlobals.insert({ ps.name, ps.value });
		}
		am.getDoubleRequestor().requestRemoval(it.first, it.second);
	}
	for each(std::pair<Core::String, size_t> it in stringObjects)
	{
		{
			Reference<PrimitiveSaveable<Core::String>> *& ref = am.getStringRequestor().request(it.first, it.second);
			PrimitiveSaveable<Core::String> ps = ref->getUnique();
			stringGlobals.insert({ ps.name, ps.value });
		}
		am.getStringRequestor().requestRemoval(it.first, it.second);
	}
}

const ResourceType & Globals::getType()
{
	return type;
}
