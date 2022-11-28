#include <file/Handler.hpp>


of::module::EngineResourceType of::module::interface::IEngineResource<of::file::Handler>::type = of::module::EngineResourceType::FileHandler;

namespace of::file
{
	Handler::Handler()
	{
		openedFile.name = "<Not Set>";
	}

	file::Loader& Handler::getLoader()
	{
		return of::engine::GetModule<file::Loader>();
	}

	of::module::EngineResourceType& Handler::getType() const
	{
		return type;
	}
}