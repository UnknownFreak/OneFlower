#ifndef LootDrop_Hpp
#define LootDrop_Hpp

#include <object/component/IBaseComponent.hpp>
#include "LootTable.hpp"

namespace of::object::component
{
	class LootDrop : public of::object::component::IBase<LootDrop>
	{
		virtual void onMessage(const of::object::messaging::Message& message) override;
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

		// Inherited via IBase
		virtual void onCollision(GameObject* the_collidee) override;
		virtual void Update() override;
		virtual void Simulate(const float& fElapsedTime) override;
		virtual void onDeath() override;

		virtual void onDelete() override;
	};
}


#endif