#ifndef MODEL_HPP
#define MODEL_HPP

#include <SFML\Graphics\RenderTarget.hpp>

#include <Core\String.hpp>
#include <Core\Vector.h>

#include <AssetManager\ObjectSaveMode.hpp>
#include <AssetManager\SpriteRef.hpp>
#include <AssetManager\IRequestable.hpp>

class IModel : public sf::Drawable, public IRequestable
{
protected:

	SpriteRef* m_render_sprite;
	bool updateRequired = true;
	
public:
	
	SpriteRef *& getSpriteRef() { return m_render_sprite; }

	virtual void updateFrame(const size_t& update_ms) = 0;

	IModel();
	
	IModel(const IModel& copy);

	IModel& operator=(const IModel& right);

	virtual ~IModel() = default;

	void setRenderSprite(SpriteRef& texture);

	virtual bool isFaceable();

	virtual void setAnimation(Core::String _animation) = 0;

	virtual void setTextureMap(Core::String _modOrigin, Core::String _textureMapName) = 0;

	virtual void preRender(const size_t& update_ms);

	virtual void setPosition(const Core::Vector2& pos);

	virtual void setRotation(const float rot);

	virtual void setScale(const Core::Vector2& scale);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	template <class Archive>
	void save(Archive & ar) const
	{
		ar(cereal::base_class<IRequestable>(this));
	}

	template <class Archive>
	void load(Archive & ar)
	{
		ar(cereal::base_class<IRequestable>(this));
	}

};

#endif