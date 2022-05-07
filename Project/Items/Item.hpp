#ifndef Item_HPP
#define Item_HPP

#include <swizzle/gfx/Texture.hpp>

#include <cereal/cereal.hpp>

#include <Helpers/String.hpp>
#include <Helpers/Enum/Rarity.hpp>
#include <Helpers/Enum/ItemType.hpp>
#include <Interfaces/IRequestable.hpp>

namespace Items
{
	class Base : public Interfaces::IRequestable
	{
		std::shared_ptr<swizzle::gfx::Texture> iconTexture;
		Core::uuid uniqId;
	public:

		void loadIcon();

		Enums::ItemType type;
		Enums::Rarity rarity;
		unsigned int value;

		Core::String itemIconName;
		Core::String itemName;
		bool stacking = true;
		size_t stackSize;

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Interfaces::IRequestable>(this));
			ar(type);
			ar(rarity);
			ar(value);
			ar(itemName);
			ar(itemIconName);
			ar(stacking);
			ar(stackSize);
		}

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Interfaces::IRequestable>(this));
			ar(type);
			ar(rarity);
			ar(value);
			ar(itemName);
			ar(itemIconName);
			ar(stacking);
			ar(stackSize);
			loadIcon();
		}
		virtual Interfaces::TypeInfo getTrait() const override;

	};
}

#endif