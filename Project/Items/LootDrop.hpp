#ifndef LootDrop_Hpp
#define LootDrop_Hpp

#include <object/component/BaseComponent.hpp>
#include "LootTable.hpp"

namespace of::object::component
{
	class LootDrop : public Base
	{
		virtual void onMessage(const of::object::messaging::Message& message) override;
		virtual void initialize() override {};
		virtual void deconstruct() override {};

	public:
		bool looted;
		of::file::FileId lootTableId;
		Items::LootTable table;

		std::unordered_map<of::file::FileId, size_t> lootDrops;


		void loot(GameObject* object);
		bool isLooted() const;

		virtual LootDrop* copy() const override
		{
			return new LootDrop(*this);
		}

		virtual std::unique_ptr<Base> ucopy() const override
		{
			return std::make_unique<LootDrop>(*this);
		}

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

		of::common::uuid getType() const override
		{
			return typeId;
		};

		of::common::String getTypeName() const override
		{
			return "LootDrop";
		};

		static constexpr of::common::uuid typeId = "6e45ab1f-7a29-417b-b9fb-d6db1789696b";
	};
}


#endif