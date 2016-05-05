#ifndef Movement_HPP
#define Movement_HPP
#include "../../../Vector.h"

namespace Physics
{
	struct Movement
	{
		double torque = 0;
		double speed = 0;
		Vector2 direction;
		Vector2 rotation;

		void addTorque(Vector2 rotate,double force);
		void addTranslation(Vector2 direct,double force);
		void reset();

	};
}

#endif