#pragma once

namespace of::ai
{
	// used to simulate unloaded objects with a proxy
	// proxy can construct an object when it enters the active zone.
	// objects exiting the zone will be converted into a proxy
	// Proxies need to be constructed/ deconstructed upon player leaving/ loading a new zone/ instance
	class AIBackgroundThread
	{

	public:
		void run();
		void wait();
	};
}