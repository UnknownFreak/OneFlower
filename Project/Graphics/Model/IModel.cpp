#include "IModel.hpp"

Core::uuid Interfaces::Trait<IModel>::typeId = Core::uuid("c918cd27-364c-44af-bcb1-9201fb8fa1ef");

IModel::IModel() : IRequestable("OneFlower.main", Core::uuid(), OneVersion(1,0,0)), m_sprite(NULL)
{

}

IModel::IModel(const IModel& copy) : IRequestable(copy), m_sprite(copy.m_sprite), updateRequired(copy.updateRequired)
{

}

IModel& IModel::operator=(const IModel& right)
{
	ID = right.ID;
	fromMod = right.fromMod;
	mode = right.mode;
	objectVersion = right.objectVersion;

	m_sprite = right.m_sprite;
	updateRequired = right.updateRequired;
	
	return *this;
}

void IModel::setRenderSprite(std::shared_ptr<sf::Sprite>& texture)
{
	m_sprite = texture;
}

void IModel::preRender(const float& update_ms)
{
	updateFrame(update_ms);
}

void IModel::setPosition(const Core::Vector2 & vec)
{
	m_sprite->setPosition(vec.x, vec.y);
}

void IModel::setRotation(const float rot)
{
	m_sprite->setRotation(rot);
}

void IModel::setScale(const Core::Vector2 & scale)
{
	m_sprite->setScale(scale.x, scale.y);
}

void IModel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_sprite.get())
		target.draw(m_sprite.operator*(), states);
}

Core::String IModel::getName() const
{
	return name;
}

Core::String IModel::getValue() const
{
	return "<Model Data>";
}

Interfaces::TypeInfo IModel::getTrait() const
{
	return { Interfaces::Trait<IModel>::typeId };
}
