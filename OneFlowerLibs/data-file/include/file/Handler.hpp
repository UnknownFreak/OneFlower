#pragma once

#include <module/IEngineModule.hpp>
#include <file/Header.hpp>
#include <file/Loader.hpp>
#include <file/archive/Requestor.hpp>

namespace of::file
{

	class Handler : public of::module::interface::IEngineResource<Handler>
	{
	public:

		Handler();

		file::archive::Requestor archive;

		file::Header openedFile;
		file::Loader& getLoader();

		of::module::EngineResourceType& getType() const;
	};

}