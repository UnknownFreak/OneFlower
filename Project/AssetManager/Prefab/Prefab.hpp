#ifndef Prefab_HPP
#define Prefab_HPP

#include <vector>
#include <Core/String.hpp>
#include <Core/Component/BaseComponent.hpp>
#include "../ObjectSaveMode.hpp"
class GameObject;
class Prefab
{
	friend class BaseComponent;
public:

	Prefab() = default;
	Prefab(const GameObject* go);
	Prefab(const Prefab& pre);
	~Prefab();

	GameObject* createFromPrefab();

private:
#ifdef _DEBUG
public:
#endif

	std::vector<BaseComponent*> base;
	size_t ID;
	Core::String name;
	Core::String tag;
	Core::String fromMod = "OneFlower.main";
	ObjectSaveMode mode = ObjectSaveMode::ADD;
	const unsigned int getTypeID(size_t index);

//protected:
	//template<class Archive>
	//friend void save(Archive &ar, const Prefab &pre);
	//template<class Archive>
	//friend void load(Archive &ar, Prefab &pre);


#pragma region Prefab
	template <class Archive>
	void load(Archive& ar)
	{
		ar(ID);
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
		ar(fromMod);
		ar(mode);
	}
	template <class Archive>
	void save(Archive& ar) const
	{
		ar(ID);
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
		ar(fromMod);
		ar(mode);
	}
#pragma endregion

};

#endif