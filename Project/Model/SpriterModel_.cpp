#include "SpriterModel_.hpp"
#include <Graphic\Time\Time.hpp>
namespace Model
{
	{
	}

	SpriterModel::SpriterModel() : myEntity(nullptr)
	{
		objectVersion = OneVersion(1, 0, 0);
	}

	SpriterModel::~SpriterModel()
	{
	}

	SpriterModel::SpriterModel(const SpriterModel & copy) : IModel(copy), fileName(copy.fileName), modelNames(copy.modelNames), selectedModelName(copy.selectedModelName),
		textureMapId(textureMapId)
	{
	}

	SpriterModel & SpriterModel::operator=(const SpriterModel & right)
	{
		if (this == &right)
			return *this;

		ID = right.ID;
		fromMod = right.fromMod;
		mode = right.mode;
		objectVersion = right.objectVersion;

		m_render_sprite = right.m_render_sprite;
		updateRequired = right.updateRequired;
		return *this;
	}
	void SpriterModel::updateFrame(const size_t& update_ms)
	{
	}
	void SpriterModel::setAnimation(Core::String _animation)
	{
	}
	void SpriterModel::setTextureMap(Core::String _modOrigin, Core::String _textureMapName)
	{
	}
	void SpriterModel::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
	}
}