#ifndef Prefab_HPP
#define Prefab_HPP
#include <vector>
#include <Core/String.hpp>
#include <Core/Component/BaseComponent.hpp>

#include "../IRequestable.hpp"
#include "../ObjectSaveMode.hpp"

class GameObject;
class Prefab : public IRequestable
{
	friend class BaseComponent;
public:

	Prefab();
	Prefab(const GameObject* go);
	Prefab(const Prefab& pre);

	Prefab& operator=(const Prefab& left);

	~Prefab();

	GameObject* createFromPrefab();

private:
#ifdef _DEBUG
public:
#endif

	std::vector<BaseComponent*> base;
	Core::String name;
	Core::String tag;
	const unsigned int getTypeID(size_t index);

#pragma region Prefab
	template <class Archive>
	void load(Archive& ar)
	{
		ar(cereal::base_class<IRequestable>(this));
		size_t size;
		ar(size);
		for (size_t i = 0; i < size; ++i)
		{
			std::unique_ptr<BaseComponent>b;
			ar(b);
			base.push_back(b.release());
		}
		ar(name);
		ar(tag);
	}

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(cereal::base_class<IRequestable>(this));
		ar(base.size());
		size_t size = base.size();
		for (size_t i = 0; i < size; ++i)
		{
			std::unique_ptr<BaseComponent> b(base[i]);
			ar(b);
			//Release the our held object as we do NOT want to deallocate it;
			//the deallocation is being handled by the Prefab itself.
			b.release();
		}
		ar(name);
		ar(tag);
	}
#pragma endregion

};

#endif