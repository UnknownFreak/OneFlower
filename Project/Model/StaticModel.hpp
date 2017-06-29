#ifndef STATIC_MODEL_HPP
#define STATIC_MODEL_HPP
#include "IModel.hpp"
#include <Core\Vector.h>

class StaticModel : public IModel
{
	Core::Vector2i m_TopLeft;
	Core::Vector2i m_BottomRight;
public:

	StaticModel();


	// Inherited via IModel
	virtual void setAnimation(Core::String _animationName) override;
	virtual void setTextureMap(Core::String _modOrigin, Core::String _textureMapName) override;

	template<class Archive>
	void save(Archive& _save) const
	{
		ar(m_TopLeft);
		ar(m_BottomRight);
	}

	template<class Archive>
	void load(Archive& _load)
	{
		ar(m_TopLeft);
		ar(m_BottomRight);
	}

protected:

	// Inherited via IModel
	virtual void updateFrame() override;
};


#endif