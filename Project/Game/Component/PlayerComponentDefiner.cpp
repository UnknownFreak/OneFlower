#include "PlayerComponent.hpp"
#include "GameObject.h"
#include "../../Engine.hpp"
#include "RigidComponent.hpp"

const unsigned int IBaseComponent<PlayerComponent>::typeID = 1252352;
std::string IBaseComponent<PlayerComponent>::componentName = "PlayerComponent";

void PlayerComponent::setAnimation(std::string animation)
{
	//TODO: Change when message strucure change
	BaseMessage msg;
	msg.msg = animation;
	msg.value = 0;
	RenderComponent* render = attachedOn->GetComponent<RenderComponent>();
	if (render)
		attachedOn->sendMessage(msg, render);
}

void PlayerComponent::attachOn(GameObject* toAttach)
{
	BaseComponent::attachOn(toAttach);
	rigid = toAttach->GetComponent<RigidComponent>();
	if(!rigid)
	{
		toAttach->AddComponent<RigidComponent>();
		rigid = toAttach->GetComponent<RigidComponent>();
	}
	//REGISTER_EDITOR_VARIABLE(int,movementSpeed,MovementSpeed);

	//toAttach->AddComponent<MovementComponent>();
	//Engine::Input.registerCallback(std::bind(&PlayerComponent::manoeuvre,this,Vector2(0,0)),sf::Keyboard::D,Input::Action::Release);
	Engine::Input.registerCallback(std::bind(&PlayerComponent::manoeuvre, this, Vector2(1,0)),sf::Keyboard::D,Input::Action::Hold);
	Engine::Input.registerCallback(std::bind(&PlayerComponent::setAnimation, this, "walk"), sf::Keyboard::D, Input::Action::Press);
	Engine::Input.registerCallback(std::bind(&PlayerComponent::setAnimation, this, "idle"), sf::Keyboard::D, Input::Action::Release);

	Engine::Input.registerCallback(std::bind(&PlayerComponent::manoeuvre, this, Vector2(-1,0)),sf::Keyboard::A,Input::Action::Hold);
	Engine::Input.registerCallback(std::bind(&PlayerComponent::setAnimation, this, "walk"), sf::Keyboard::A, Input::Action::Press);
	Engine::Input.registerCallback(std::bind(&PlayerComponent::setAnimation, this, "idle"), sf::Keyboard::A, Input::Action::Release);

	Engine::Input.registerCallback(std::bind(&PlayerComponent::manoeuvre, this, Vector2(0,-1)),sf::Keyboard::W,Input::Action::Hold);
	Engine::Input.registerCallback(std::bind(&PlayerComponent::setAnimation, this, "jump"), sf::Keyboard::W, Input::Action::Press);

	Engine::Input.registerCallback(std::bind(&PlayerComponent::manoeuvre, this, Vector2(0,1)),sf::Keyboard::S,Input::Action::Hold);
	Engine::Input.registerCallback(std::bind(&PlayerComponent::setAnimation, this, "crouch"), sf::Keyboard::S, Input::Action::Press);
	Engine::Input.registerCallback(std::bind(&PlayerComponent::setAnimation, this, "stand_up"), sf::Keyboard::S, Input::Action::Release);


}

void PlayerComponent::manoeuvre(Vector2 Direction)
{
	rigid->movement.addTranslation(Direction,movementSpeed);
}
#ifdef _EDITOR_
void PlayerComponent::setMovementSpeed(int speed)
{
	movementSpeed = speed;
}
#endif