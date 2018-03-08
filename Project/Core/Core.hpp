#ifndef Core_HPP
#define Core_HPP

#include <SFML\Window\Event.hpp>

#include "Component\BaseComponent.hpp"
#include "Component\GameObject.h"
#include "Component\Message\BaseMessage.hpp"
#include "Component\TransformComponent.hpp"
#include "EngineSettings.hpp"
#include "String.hpp"
#include "Vector.h"

#ifndef _UNITTESTS_
namespace Engine
{
	extern sf::Event event;
}
#endif
#endif