#include "IModel.hpp"

IModel::IModel() : IRequestable("OneFlower.main",0), m_render_sprite(NULL)
{

}

IModel::IModel(const IModel& copy) : IRequestable(copy), m_render_sprite(copy.m_render_sprite), updateRequired(copy.updateRequired)
{

}

IModel& IModel::operator=(const IModel& left)
{
	m_render_sprite = left.m_render_sprite;
	ID = left.ID;
	fromMod = left.fromMod;
	mode = left.mode;
	updateRequired = left.updateRequired;
	return *this;
}

void IModel::setRenderSprite(SpriteRef & texture)
{
	m_render_sprite = &texture;
};

void IModel::preRender()
{
	if (updateRequired)
	{
		updateFrame();
		updateRequired = false;
	}
}

void IModel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_render_sprite)
		m_render_sprite->draw(target, states);
}
