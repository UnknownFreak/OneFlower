#ifndef DataTree_HPP
#define DataTree_HPP

#include <unordered_map>

#include <asset/iAsset.hpp>

#include "ObjectEditView.hpp"

namespace Graphics
{
	namespace Editor
	{
		struct DataTreeItem
		{
			of::common::String name;
			of::asset::IAsset* ptr = nullptr;
			of::asset::ObjectType type = of::asset::ObjectType::Undefined;
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
			std::unordered_map<of::asset::AssetId, std::unique_ptr<of::asset::IAsset>>& map;

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