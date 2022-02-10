#ifndef MODEL_HPP
#define MODEL_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <Helpers\String.hpp>
#include <Helpers\Vector.hpp>

#include <Helpers/Enum/ObjectSaveMode.hpp>
#include <Interfaces\IRequestable.hpp>

class IModel : public sf::Drawable, public Interfaces::IRequestable
{
protected:

	std::shared_ptr<sf::Sprite> m_sprite;
	bool updateRequired = true;
	Core::String name;
public:
	
	auto& getSpriteRef() { return m_sprite; }

	virtual void updateFrame(const float& update_ms) = 0;

	IModel();
	
	IModel(const IModel& copy);

	IModel& operator=(const IModel& right);

	virtual ~IModel() = default;

	void setRenderSprite(std::shared_ptr<sf::Sprite>& sprite);

	virtual void setAnimation(Core::String _animation) = 0;

	virtual void setTextureMap(Core::String _modOrigin, Core::String _textureMapName) = 0;

	virtual void preRender(const float& update_ms);

	virtual void setPosition(const Core::Vector2& pos);

	virtual void setRotation(const float rot);

	virtual void setScale(const Core::Vector2& scale);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	Core::String getName() const override;

	Core::String getValue() const override;

	template <class Archive>
	void save(Archive & ar) const
	{
		ar(cereal::base_class<IRequestable>(this));
		ar(name);
	}

	template <class Archive>
	void load(Archive & ar)
	{
		ar(cereal::base_class<IRequestable>(this));
		ar(name);
	}


	// Inherited via IRequestable
	virtual Interfaces::TypeInfo getTrait() const override;

};
#endif
