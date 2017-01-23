#pragma once
class GameObject;
#include <Core/Vector.h>
//HIGH: move this outside of physics
namespace Physics
{
	class Collider
	{
	public:
		struct Hit
		{
			//HIGH:Rework this
			enum Edge
			{
				None = 0,
				Right = 1,
				Left = -1,
				Bottom = 1,
				Top = -1,
			};
		};
		GameObject* contact = NULL;
		//Hit::Edge
		Vector2	direction;
		//Hit::None;
		double newton = 0;
		double timeEnter = 1;
		double timeExit = 0;
	};
};