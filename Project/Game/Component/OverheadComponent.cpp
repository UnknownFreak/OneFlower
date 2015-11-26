#include "OverheadComponent.hpp"
#include "GameObject.h"
#include "TransformComponent.hpp"
#include "RenderComponent.h"
#include "../../Engine.hpp"
#include <string>
const unsigned int IBaseComponent<OverheadComponent>::typeID = 1005;
std::string IBaseComponent<OverheadComponent>::componentName = "OverheadComponent";
OverheadComponent::OverheadComponent(): msg(GUI::Text::Message(*Engine::Graphic.font.requestFont("Arial.ttf"))),offset(0,0),spriteSize(0,0)
{
	msg.setSize(25);
}

void OverheadComponent::attachOn(GameObject* attachTo)
{
	BaseComponent::attachOn(attachTo);
	pos = &attachedOn->GetComponent<TransformComponent>()->position;
	if(attachedOn->GetComponent<RenderComponent>())
		spriteSize = attachedOn->GetComponent<RenderComponent>()->size;
	msg = attachedOn->name;

	Engine::GUI.requestOverheadRemoval(attachedOn);
	Engine::GUI.addOverhead(attachedOn);

	REGISTER_EDITOR_VARIABLE(Vector2,offset,Offset);
	REGISTER_EDITOR_VARIABLE(sf::Uint8,msg.color.r,ColorRed);
	REGISTER_EDITOR_VARIABLE(sf::Uint8,msg.color.g,ColorGreen);
	REGISTER_EDITOR_VARIABLE(sf::Uint8,msg.color.b,ColorBlue);
}
bool OverheadComponent::updateFromEditor()
{
	msg.setColor(msg.color);

	return true;
}
void OverheadComponent::setPosition()
{
	msg.setPosition(pos->x - spriteSize.x / 2 + offset.x,pos->y - spriteSize.y / 2 + offset.y);
}
void OverheadComponent::setPosition(Vector2 pos)
{
	msg.setPosition(pos.x + offset.x,pos.y + offset.y);
}
void OverheadComponent::setPosition(double x,double y)
{
	msg.setPosition(x + offset.x,y + offset.y);
}