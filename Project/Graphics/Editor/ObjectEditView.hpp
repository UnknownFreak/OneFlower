#ifndef ObjectEditView_HPP
#define ObjectEditView_HPP

#include <asset/iAsset.hpp>

namespace Graphics
{
	namespace Editor
	{

		class ObjectEditView
		{
		public:

			of::asset::IAsset* ptr = nullptr;

			ObjectEditView();
			void render();
		};
	}
}


#endif