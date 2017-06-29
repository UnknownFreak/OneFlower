#include "StaticModel.hpp"

StaticModel::StaticModel() : IModel(), m_TopLeft(-1,-1), m_BottomRight(-1,-1)
{

}

void StaticModel::setAnimation(Core::String _animationName)
{

}

void StaticModel::setTextureMap(Core::String _modOrigin, Core::String _textureMapName)
{

}

void StaticModel::updateFrame()
{
	if (updateRequired)
	{
		if (m_TopLeft.x != -1)
			m_render_sprite->setTextureRect(sf::IntRect(m_TopLeft.x, m_TopLeft.y, m_BottomRight.x, m_BottomRight.y));
		else
		{
			const Core::Vector2 v(m_render_sprite->getTexture()->getSize().x, m_render_sprite->getTexture()->getSize().y);
			m_render_sprite->setTextureRect(sf::IntRect(0, 0, v.x, v.y));
		}
		updateRequired = false;
	}
}

