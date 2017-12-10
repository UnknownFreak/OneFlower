#include "LoadZoneComponent.hpp"
#include "../WorldManager.hpp"
#include <Core\Component\GameObject.h>

#include <Physics\Collider.hpp>

const unsigned int IBaseComponent<Component::Portal>::typeID = 1032;
Core::String IBaseComponent<Component::Portal>::componentName = "PortalComponent";


void Component::Portal::loadZone()
{
	Engine::Get<WorldManager>().loadZone(zoneToLoadID.first, zoneToLoadID.second);
}

void Component::Portal::attachOn(GameObject * go)
{
	Portal::BaseComponent::attachOn(go);
}

Component::Portal::Portal()
{
}

Component::Portal::Portal(const Portal & copy) : zoneToLoadID(copy.zoneToLoadID), 
posToPlaceCharacter(copy.posToPlaceCharacter),
loadZoneOnHitboxContact(copy.loadZoneOnHitboxContact)
{
}

Component::Portal & Component::Portal::operator=(const Portal & right)
{
	this->loadZoneOnHitboxContact = right.loadZoneOnHitboxContact;
	this->posToPlaceCharacter= right.posToPlaceCharacter;
	this->zoneToLoadID = right.zoneToLoadID;
	
	return *this;
}

void Component::Portal::onCollision(Physics::Collider & collider)
{
	if (loadZoneOnHitboxContact && collider.contact->tag == "Player")
		loadZone();
}

void Component::Portal::getMessage(const BaseMessage message)
{
	if(message.msg == "Teleport")
		loadZone();
	attachedOn->destroy();
}

Component::Portal* Component::Portal::copy() const
{
	return new Portal(*this);
}
