#ifndef ObjectEditView_HPP
#define ObjectEditView_HPP

#include <Interfaces/IRequestable.hpp>

namespace Graphics
{
	namespace Editor
	{

		class ObjectEditView
		{
		public:

			Interfaces::IRequestable* ptr = nullptr;

			ObjectEditView();
			void render();
		};
	}
}


#endif