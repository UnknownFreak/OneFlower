#ifndef Prefab_HPP
#define Prefab_HPP
#include <vector>

#include <Core/String.hpp>
#include <Core/Component/BaseComponent.hpp>

#include <Asset/ComponentFactory.hpp>

#include "IRequestable.hpp"
#include "IObject.hpp"
#include "ObjectSaveMode.hpp"


class GameObject;
namespace Asset
{
	class Prefab : public IRequestable, public IObject
	{
		friend class Component::Base;
	public:

		Prefab();
		Prefab(const GameObject* go);
		Prefab(const Prefab& pre);

		Prefab& operator=(const Prefab& left);

		~Prefab();

		GameObject* createFromPrefab() const;

	private:
	#ifdef _DEBUG
	public:
	#endif

		std::vector<Component::Base*> base;
		const size_t getTypeID(size_t index);

		Core::String getName() const override;
		Core::String getValue() const override;

	#pragma region Prefab
		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IRequestable>(this));
			ar(cereal::base_class<IObject>(this));
			size_t size;
			ar(size);
			for (size_t i = 0; i < size; ++i)
			{
				base.push_back(ComponentFactory::load(ar));
			}
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IRequestable>(this));
			ar(cereal::base_class<IObject>(this));
			ar(base.size());
			size_t size = base.size();
			for (size_t i = 0; i < size; ++i)
			{
				ComponentFactory::save(ar, base[i]);
			}
		}
	#pragma endregion

	};
}

#endif