#ifndef Requirement_HPP
#define Requirement_HPP
#include <memory>

namespace Requirement
{
	struct Requirement
	{
		inline virtual ~Requirement() {  };
		virtual bool fullfilled() = 0;
		inline virtual void start() {};
		inline virtual void reset() {};
		inline virtual void stop() {};

		inline virtual std::unique_ptr<Requirement> clone() const = 0;
	};
	
}

#endif