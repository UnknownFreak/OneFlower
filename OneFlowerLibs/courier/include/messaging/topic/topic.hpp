#pragma once

namespace of::messaging
{
	
	enum class Topic
	{
		/*
		Update is for generic object updates such as state or trigger changes.
		Multi threaded, cannot interact with physics engine.
		Examples: Status effect tick times, animations
		*/
		Update,
		/*
		Physics update is for dynamic object updates such as adding object torque/ force, or doing other 
		physics updates.
		Single threaded.
		Examples: Physics forces applied, e.g growing / shrinking hitbox/ adding or removing forces
		*/
		PhysicsUpdate,
		/*
		Single Thread Update is for generic low priority updating logic. 
		Single threaded, can interact with physics engine
		Example: Physics raycast, e.g get mouse click on screen.
		*/
		SingleThreadUpdate,
	};
}