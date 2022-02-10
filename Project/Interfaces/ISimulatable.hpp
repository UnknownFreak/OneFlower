#ifndef ISimulatable_HPP
#define ISimulatable_HPP

namespace Interfaces
{
	struct ISimulatable
	{
		virtual void Simulate(const float& fElapsedTime) = 0;
		virtual ~ISimulatable() = default;
};
}

#endif