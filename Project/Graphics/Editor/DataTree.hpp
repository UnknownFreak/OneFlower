#ifndef DataTree_HPP
#define DataTree_HPP

#include <unordered_map>

#include <file/FileId.hpp>
#include <file/archive/Requestable.hpp>

#include "ObjectEditView.hpp"

namespace Graphics
{
	namespace Editor
	{
		struct DataTreeItem
		{
			of::common::String name;
			of::file::archive::Requestable* ptr = nullptr;
			of::file::ObjectType type = of::file::ObjectType::Undefined;
			std::vector<DataTreeItem> items;
			inline bool operator< (const DataTreeItem& item)
			{
				return name < item.name;
			}
		};

		class DataTree
		{
			size_t mapSize = 0;
			DataTreeItem objectTree;
			ObjectEditView editView;

			float& height;
			std::unordered_map<of::file::FileId, std::unique_ptr<of::file::archive::Requestable>>& map;

			bool treeNeedsUpdate();
			void buildTree();
			void drawTree(DataTreeItem& item);

		public:
			DataTree(float& height);
			void render();
			void clear();
		};
	}
}

#endif