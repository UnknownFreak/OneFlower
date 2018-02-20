#include "IModel.hpp"


IModel::IModel() : IRequestable("OneFlower.main",0, OneVersion(1,0,0)), m_render_sprite(NULL)
{

}

IModel::IModel(const IModel& copy) : IRequestable(copy), m_render_sprite(copy.m_render_sprite), updateRequired(copy.updateRequired)
{

}

IModel& IModel::operator=(const IModel& right)
{
	ID = right.ID;
	fromMod = right.fromMod;
	mode = right.mode;
	objectVersion = right.objectVersion;

	m_render_sprite = right.m_render_sprite;
	updateRequired = right.updateRequired;
	
	return *this;
}

void IModel::setRenderSprite(SpriteRef & texture)
{
	m_render_sprite = &texture;
}
bool IModel::isFaceable()
{
	return false;
}

void IModel::preRender(const size_t& update_ms)
{
	updateFrame(update_ms);
}

void IModel::setPosition(const Core::Vector2 & vec)
{
	m_render_sprite->setPosition(vec.x, vec.y);
}

void IModel::setRotation(const float rot)
{
	m_render_sprite->setRotation(rot);
}

void IModel::setScale(const Core::Vector2 & scale)
{
	m_render_sprite->setScale(scale.x, scale.y);
}

void IModel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_render_sprite)
		m_render_sprite->draw(target, states);
}
