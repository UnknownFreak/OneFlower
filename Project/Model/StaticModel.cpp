#include "StaticModel.hpp"
#include <Core\IEngineResource\EngineResourceManager.hpp>
#include <Logger\Logger.hpp>
StaticModel::StaticModel() : IModel(), m_TopLeft(-1,-1), m_BottomRight(-1,-1)
{

}

void StaticModel::setAnimation(Core::String _animationName)
{
	Engine::Get<OneLogger>().Warning("Trying to set animation <"+ _animationName +"> on a static model.", __FILE__, __LINE__);
}

void StaticModel::setTextureMap(Core::String _modOrigin, Core::String _textureMapName)
{
	Engine::Get<OneLogger>().Warning("Trying to set texture map <" + _modOrigin +", "+ _textureMapName+ "> on a static model.", __FILE__, __LINE__);
}

void StaticModel::updateFrame(const double& update_ms)
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

