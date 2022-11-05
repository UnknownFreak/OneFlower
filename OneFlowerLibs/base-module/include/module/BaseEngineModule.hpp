#ifndef BaseEngineModule_HPP
#define BaseEngineModule_HPP

#include <module/EngineResourceTypes.hpp>

namespace OneFlower::Module
{
	class BaseEngineModule
	{

	protected:
		bool disabled = false;

		virtual EngineResourceType& getType() const = 0;

	public:
		virtual ~BaseEngineModule() {};

		void disable() { disabled = true; }
	};
}


#endif