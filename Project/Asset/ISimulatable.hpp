#ifndef ISimulatable_HPP
#define ISimulatable_HPP

struct ISimulatable
{
	virtual void Simulate() = 0;
	virtual ~ISimulatable() = default;
};

#endif