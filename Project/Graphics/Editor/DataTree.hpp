#ifndef DataTree_HPP
#define DataTree_HPP

#include <unordered_map>

#include <File/Mod/ModFileUUIDHelper.hpp>
#include <Interfaces/IRequestable.hpp>

#include "ObjectEditView.hpp"

namespace Graphics
{
	namespace Editor
	{
		struct DataTreeItem
		{
			Core::String name;
			Interfaces::IRequestable* ptr;
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
			std::unordered_map<File::Mod::ModFileUUIDHelper, std::unique_ptr<Interfaces::IRequestable>>& map;

			bool treeNeedsUpdate();
			void buildTree();
			void drawTree(const DataTreeItem& item);

		public:
			DataTree(float& height);
			void render();
			void clear();
		};
	}
}

#endif