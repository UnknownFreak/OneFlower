#include "StaticModel.hpp"
#include <Module\EngineModuleManager.hpp>
#include <Module/Logger/OneLogger.hpp>
#include <SFML/Graphics/Texture.hpp>

Core::uuid Interfaces::Trait<StaticModel>::typeId = Core::uuid("9e906cbe-18a1-429c-baf4-aaa19da707a6");

StaticModel::StaticModel() : IModel(), m_TopLeft{ -1,-1 }, m_BottomRight{ -1, -1 }
{
	// Use this to set current object version
	objectVersion = OneVersion(1, 0, 0);
}

StaticModel::StaticModel(const StaticModel & copy) : IModel(copy), m_TopLeft(copy.m_TopLeft), m_BottomRight(copy.m_BottomRight)
{
}

StaticModel & StaticModel::operator=(const StaticModel & right)
{
	ID = right.ID;
	mode = right.mode;
	fromMod = right.fromMod;
	objectVersion = right.objectVersion;

	updateRequired = right.updateRequired;
	m_sprite = right.m_sprite;
	
	m_BottomRight = right.m_BottomRight;
	m_TopLeft = right.m_TopLeft;
	
	return *this;
}

void StaticModel::setAnimation(Core::String _animationName)
{
	auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("StaticModel"); 
	logger.Warning("Trying to set animation <" + _animationName + "> on a static model.", logger.fileInfo(__FILE__, __LINE__));
}

void StaticModel::setTextureMap(Core::String _modOrigin, Core::String _textureMapName)
{
	auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("StaticModel");
	logger.Warning("Trying to set texture map <" + _modOrigin +", "+ _textureMapName+ "> on a static model.", logger.fileInfo(__FILE__, __LINE__));
}

void StaticModel::updateFrame(const float& )
{
	if (updateRequired)
	{
		if (m_TopLeft.x != -1)
			m_sprite->setTextureRect(sf::IntRect(m_TopLeft.x, m_TopLeft.y, m_BottomRight.x, m_BottomRight.y));
		else
		{
			const Core::Vector2t<unsigned int> v{ m_sprite->getTexture()->getSize().x, m_sprite->getTexture()->getSize().y };
			m_sprite->setTextureRect(sf::IntRect(0, 0, v.x, v.y));
		}
		updateRequired = false;
	}
}

Interfaces::TypeInfo StaticModel::getTrait() const
{
	return { Interfaces::Trait<StaticModel>::typeId, {Interfaces::Trait<IModel>::typeId} };
}

