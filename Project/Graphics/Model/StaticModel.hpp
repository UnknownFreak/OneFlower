#ifndef STATIC_MODEL_HPP
#define STATIC_MODEL_HPP
#include "IModel.hpp"
#include <Helpers\Vector.hpp>

class StaticModel : public IModel
{
public:

	Core::Vector2i m_TopLeft;
	Core::Vector2i m_BottomRight;
public:

	StaticModel();
	StaticModel(const StaticModel& copy);
	StaticModel& operator=(const StaticModel& right);

	// Inherited via IModel
	virtual void setAnimation(Core::String _animationName) override;
	virtual void setTextureMap(Core::String _modOrigin, Core::String _textureMapName) override;

	template<class Archive>
	void save(Archive& _save) const
	{
		_save(cereal::base_class<IModel>(this));
		_save(m_TopLeft);
		_save(m_BottomRight);
	}

	template<class Archive>
	void load(Archive& _load)
	{
		_load(cereal::base_class<IModel>(this));
		_load(m_TopLeft);
		_load(m_BottomRight);
	}

protected:

	// Inherited via IModel
	virtual void updateFrame(const float& update_ms) override;


	// Inherited via IRequestable
	virtual Interfaces::TypeInfo getTrait() const override;
};


#endif