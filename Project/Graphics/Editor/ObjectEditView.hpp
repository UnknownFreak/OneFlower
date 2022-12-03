#ifndef ObjectEditView_HPP
#define ObjectEditView_HPP

#include <file/archive/Requestable.hpp>

namespace Graphics
{
	namespace Editor
	{

		class ObjectEditView
		{
		public:

			of::file::archive::Requestable* ptr = nullptr;

			ObjectEditView();
			void render();
		};
	}
}


#endif