#ifndef IObjectViewModel_HPP
#define IObjectViewModel_HPP

#include <Interfaces/IObject.hpp>

namespace Graphics::Editor::ViewModels
{
	bool renderInfo(Interfaces::IObject* ptr, const bool& showIdentifier);
}

#endif