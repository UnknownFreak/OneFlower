#ifndef SPRITERMODEL_HPP
#define SPRITERMODEL_HPP

#include "IModel.hpp"
#include <Graphics/Spriter\SpriterEngine\spriterengine.h>
#include "SpriterInstanceContainer.hpp"

#include "SpriterAnimationInfo.hpp"

namespace Model
{

	class SpriterModel : public IModel
	{

		Core::String fileName;

		std::vector<Core::String> modelNames;
		Core::String selectedModelName;

		std::pair<Core::String, Core::uuid> textureMapId;

		void setModel();

	public:

		std::map<Core::String, Core::String> animationModelMapping;

		std::map<Core::String, SpriterAnimationInfo> subInstances;

		SpriterEngine::EntityInstance* myEntity;

		SpriterModel();
		~SpriterModel();

		SpriterModel(const SpriterModel& spriterModel);
		SpriterModel& operator=(const SpriterModel& right);

		// Inherited via IModel
		virtual void updateFrame(const float& update_ms) override;

		virtual void setAnimation(Core::String _animation) override;

		virtual void setTextureMap(Core::String _modOrigin, Core::String _textureMapName) override;

		virtual void setPosition(const Core::Vector2& vec) override;

		virtual void setRotation(const float rot) override;

		virtual void setScale(const Core::Vector2 & scale) override;
		
		
		// Inherited via Drawable
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IModel>(this));
			ar(fileName);
			ar(modelNames);
			ar(selectedModelName);
			ar(textureMapId);
			ar(subInstances.size());
			std::map<const Core::String, SpriterAnimationInfo>::const_iterator it = subInstances.begin();
			std::map<const Core::String, SpriterAnimationInfo>::const_iterator eit = subInstances.end();
			for (; it != eit; it++)
				ar(it->first);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IModel>(this));
			ar(fileName);
			ar(modelNames);
			ar(selectedModelName);
			ar(textureMapId);
			setModel();
			size_t i;
			ar(i);
			Core::String s;
			for (size_t it =0; it < i; i++)
			{
				ar(s);
				SpriterEngine::EntityInstance* subInstance = (SpriterEngine::EntityInstance*)myEntity->getObjectInstance(s);
				subInstance->setCurrentEntity(s);
				subInstances.insert({ s, SpriterAnimationInfo(subInstance)});
			}
		}
		virtual Interfaces::TypeInfo getTrait() const override;

	};
}

#endif