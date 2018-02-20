#ifndef SPRITERMODEL_HPP
#define SPRITERMODEL_HPP

#include "IModel.hpp"
#include "SpriterEngine\spriterengine.h"
namespace Model
{

	class SpriterModel : public IModel
	{
		SpriterEngine::EntityInstance* myEntity;


	public:
		SpriterModel();
		~SpriterModel();

		SpriterModel(const SpriterModel& spriterModel);
		SpriterModel& operator=(const SpriterModel& right);


		// Inherited via IModel
		virtual void updateFrame(const size_t& update_ms) override;

		virtual void setAnimation(Core::String _animation) override;

		virtual void setTextureMap(Core::String _modOrigin, Core::String _textureMapName) override;

		// Inherited via Drawable
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	};
}

#endif