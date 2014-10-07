#include "MovementComponent.hpp"
#include "GameObject.h"
#include "TransformComponent.hpp"
#include <string>
#include <vector>

unsigned int IBaseComponent<MovementComponent>::typeID = 1011;

MovementComponent::MovementComponent() {
	componentName = "MovementComponent";
}

std::string MovementComponent::getTypeName() {
	return componentName;
}

void MovementComponent::moveGameobject(std::vector<std::string> actions) {	
	int left = 0;
	int right = 0;

	for(std::vector<std::string>::iterator it = actions.begin(); it != actions.end(); ++it) {
		if((*it) == "MoveLeft")
			left++;
		if((*it) == "MoveRight")
			right++;
	}
	
	

	int moveSpeed = 1;

	int direction = right - left;

	this->attachedOn->GetComponent<TransformComponent>()->position.x += moveSpeed * direction;
}