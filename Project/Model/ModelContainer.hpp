#ifndef MODELCONTAINER_HPP
#define MODELCONTAINER_HPP
#include "IModel.hpp"

#include <memory>
#include <map>
#include <Core\String.hpp>


class ModelContainer
{
	typedef std::map<std::pair<Core::String, Core::String>, IModel*> _modelMap;
	_modelMap container;

public:

	~ModelContainer();

	IModel* RequestModel();



	template<class Archive>
	void save(Archive& _save) const
	{
		_save(container.size());
		_modelMap::const_iterator it = container.begin();
		_modelMap::const_iterator eit = container.end();
		for (it; it != eit; it++)
		{
			_save(it->first);
			_save(*it->second);
		}
	}

	template<class Archive>
	void load(Archive& _load)
	{
		size_t len;
		size_t it = 0;
		_load(len);

		std::pair < Core::String, Core::String> key;
		for (it ; it < len; it++)
		{
			std::unique_ptr<IModel> mdl;
			_load(key);
			_load(mdl);
			container.insert(key, mdl.release());
		}
	}

};


#endif