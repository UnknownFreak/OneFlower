#include "ModelContainer.hpp"

ModelContainer::~ModelContainer()
{
	_modelMap::iterator it = container.begin();
	_modelMap::iterator eit = container.end();
	for (it; it != eit; it++)
	{
		delete it->second;
	}
}

IModel * ModelContainer::RequestModel()
{
	return nullptr;
}
