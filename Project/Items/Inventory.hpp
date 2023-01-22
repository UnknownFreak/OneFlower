#ifndef Inventory_Hpp
#define Inventory_Hpp

#include <memory>

#include <object/GameObject.hpp>
#include <object/component/Stats.hpp>

#include "Item.hpp"
#include "StatChangingItem.hpp"
#include "WeaponItem.hpp"
#include "ArmorItem.hpp"
#include "TrinketItem.hpp"

namespace of::object::component
{
	class Inventory : public Base
	{
		template <class T>
		requires std::derived_from<T, Items::StatChangingItem>
		void swap(std::shared_ptr<T>& theSlot, std::shared_ptr<T>& theItem)
		{
			auto stats = attachedOn->get<of::object::component::Stats>();
			if (theSlot.operator bool())
			{
				stats->removeModifier(theSlot->defence);
				for (auto& x : theSlot->attributeModifier)
					stats->removeModifier(x);
			}
			else
			{
				theSlot = theItem;
			}
			stats->addModifier(theSlot->defence);
			for (auto& x : theSlot->attributeModifier)
				stats->addModifier(x);
		}

		void equipWeapon(std::shared_ptr<Items::Base>& item, const bool& offhand);
		void equipArmor(std::shared_ptr<Items::Base>& item);
		void equipAmmo(std::shared_ptr<Items::Base>& ammo);
		void equipTrinket(std::shared_ptr<Items::Base>& item, const bool& secondary);

		virtual void onMessage(const of::object::messaging::Message& message) override;
		virtual void initialize() override {};
		virtual void deconstruct() override {};

	public:

		virtual Inventory* copy() const override
		{
			return new Inventory(*this);
		}

		virtual std::unique_ptr<Base> ucopy() const override
		{
			return std::make_unique<Inventory>(*this);
		}

		std::shared_ptr<Items::Weapon> mainHand;
		std::shared_ptr<Items::Weapon> offHand;
		std::shared_ptr<Items::Base> ammo;

		std::shared_ptr<Items::Armor> helm;
		std::shared_ptr<Items::Armor> shoulder;
		std::shared_ptr<Items::Armor> gloves;
		std::shared_ptr<Items::Armor> chest;
		std::shared_ptr<Items::Armor> leggings;
		std::shared_ptr<Items::Armor> boots;
		std::shared_ptr<Items::Armor> cape;

		std::shared_ptr<Items::Trinket> amulet;
		std::shared_ptr<Items::Trinket> accessory;
		std::shared_ptr<Items::Trinket> accessory2;
		std::shared_ptr<Items::Trinket> ring;
		std::shared_ptr<Items::Trinket> ring2;

		std::vector<std::shared_ptr<Items::Base>> itemList;

		void equipItem(std::shared_ptr<Items::Base>& item, const bool& offhand);

		void addItem(std::shared_ptr<Items::Base>& item, const size_t& stackSize);
		void removeItem(std::shared_ptr<Items::Base>& item, const size_t& stackSize);

		size_t getItemStack(const of::file::FileId& itemId);

		virtual void update(const float& fElapsedTime) override;

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

		of::common::uuid getType() const override
		{
			return typeId;
		};

		of::common::String getTypeName() const override
		{
			return "Inventory";
		};

		static constexpr of::common::uuid typeId = "6e45ab1c-7a29-417b-b9fb-d6fb1789696b";
	};
}


#endif