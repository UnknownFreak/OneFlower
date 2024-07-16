#pragma once

namespace of::courier
{
	
	enum class Topic
	{
		/*
		Update is for generic object updates such as state or trigger changes.
		Multi threaded, cannot interact with physics engine.
		Examples: Status effect tick times, animations, gui triggers & logic checking
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
		/*
		Object topic is for object to object communication or engine to object communication
		That should invoke a behavior on a object, but the invocation should not be instantly called (delaying) regular execution
		*/
		Object,
	};
}