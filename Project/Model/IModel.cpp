#include "IModel.hpp"

IModel::IModel() : IRequestable("OneFlower.main",0), m_render_sprite(NULL)
{

}

IModel::IModel(const IModel& copy) : IRequestable(copy), m_render_sprite(copy.m_render_sprite), updateRequired(copy.updateRequired)
{

}

IModel& IModel::operator=(const IModel& right)
{
	m_render_sprite = right.m_render_sprite;
	ID = right.ID;
	fromMod = right.fromMod;
	mode = right.mode;
	updateRequired = right.updateRequired;
	return *this;
}

void IModel::setRenderSprite(SpriteRef & texture)
{
	m_render_sprite = &texture;
};

void IModel::preRender(const double& update_ms)
{
	updateFrame(update_ms);
}

void IModel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_render_sprite)
		m_render_sprite->draw(target, states);
}
