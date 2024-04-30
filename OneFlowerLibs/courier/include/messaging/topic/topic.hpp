#pragma once

namespace of::messaging
{
	
	enum class Topic
	{
		/*
		Update is for generic object updates such as state or trigger changes.
		Multi threaded, cannot interact with physics engine
		*/
		Update,
		/*
		Physics update is for dynamic object updates such as adding object torque/ force, or doing other 
		physics updates.
		Single threaded.
		*/
		PhysicsUpdate,
		/*
		Single Thread Update is for generic low priority updating logic. 
		Single threaded, can interact with physics engine
		*/
		SingleThreadUpdate,
	};
}