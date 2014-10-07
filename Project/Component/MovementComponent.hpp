#ifndef MovementComponent_HPP
#define MovementComponent_HPP
#include "IBaseComponent.hpp"

class MovementComponent : public IBaseComponent<MovementComponent>
{
public:
	MovementComponent();

	std::string getTypeName();
	void MovementComponent::moveGameobject(std::vector<std::string> actions);
private:

};

#endif