#ifndef Item_HPP
#define Item_HPP

#include <swizzle/gfx/Texture.hpp>

#include <cereal/cereal.hpp>

#include <utils/common/string.hpp>
#include <Helpers/Enum/Rarity.hpp>
#include <Helpers/Enum/ItemType.hpp>
#include <Interfaces/IRequestable.hpp>

namespace Items
{
	class Base : public Interfaces::IRequestable
	{
		std::shared_ptr<swizzle::gfx::Texture> iconTexture;
		of::common::uuid uniqId;
	public:

		void loadIcon();

		Enums::ItemType type;
		Enums::Rarity rarity;
		unsigned int value;

		of::common::String itemIconName;
		of::common::String itemName;
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