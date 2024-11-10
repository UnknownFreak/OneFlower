#pragma once
#include <asset/header.hpp>
#include <set>

namespace of::editor
{

	struct EditorContext
	{
		of::common::String openedFileName;
		of::asset::Header header;

		void buildModOrderFile(const of::common::String& filename, std::set<of::common::String>& dependencies);
		void saveGameDatabase(const of::common::String& filename);

		void loadAllEditorVariables();

	};

	void initEditorContext();
	void shutdownEditorContext();

	EditorContext& getEditorContext();

}