#ifndef GraphicsCore_HPP
#define GraphicsCore_HPP

#include "Gfx.h"
#include <AssetManager\AssetManagerCore.hpp>
#include "Time\Time.hpp"
namespace Engine
{
	inline Time& time()
	{
		return Time::getTime();
	}
	extern sf::Event event;
	extern Gfx Graphic;
	//extern Time time;
}


#endif
