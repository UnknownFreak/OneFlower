#pragma once

#include <module/IEngineModule.hpp>
#include <module/ModuleManager.hpp>
#include <file/Header.hpp>
#include <file/Loader.hpp>
#include <file/archive/Requestor.hpp>

namespace of::file
{

	class Handler : public of::module::interface::IEngineResource<Handler>
	{
	public:

		Handler();

		void buildModOrderFile(const of::common::String& modFile, std::set<of::common::String>& dependencies);

		void saveGameDatabase(std::string filename, Header& modhdr);

		void loadAllEditorVariables();

		file::archive::Requestor archive;
		file::Loader modLoader;

		file::Header openedFile;
		file::Loader& getLoader();

		of::module::EngineResourceType& getType() const;
	};

}