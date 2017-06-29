#include "IModel.hpp"

IModel::IModel() : m_render_sprite(NULL)
{

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
