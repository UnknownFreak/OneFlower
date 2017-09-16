#ifndef Movement_HPP
#define Movement_HPP
#include <Core/Vector.h>

namespace Physics
{
	struct Movement
	{
		double torque = 0;
		double speed = 0;
		Core::Vector2 direction;
		Core::Vector2 rotation;

		void addTorque(Core::Vector2 rotate, double force);
		void addTranslation(Core::Vector2 direct, double force);
		void reset();
	};
}

#endif