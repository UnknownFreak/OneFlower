#ifndef LootContainer_Hpp
#define LootContainer_Hpp

#include <File/ModFileUUIDHelper.hpp>

#include <Object/IBaseComponent.hpp>

namespace Component
{
	class LootContainer : public Component::IBase<LootContainer>
	{
		void setLooted();
	public:
		bool looted;
		bool isStaticContainer;

		std::unordered_map<ModFileUUIDHelper, size_t> lootDrops;


		virtual LootContainer* copy() const override
		{
			return new LootContainer(*this);
		}

		virtual std::unique_ptr<Base> ucopy() const override
		{
			return std::make_unique<LootContainer>(*this);
		}

		void loot(GameObject* object);
		bool isLooted() const;

		// Inherited via IBase
		virtual void onCollision(Interfaces::ICollider* the_collidee) override;
		virtual void Update() override;
		virtual void Simulate(const float& fElapsedTime) override;
		virtual void onDeath() override;
		virtual void onDelete() override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(isStaticContainer);
			ar(lootDrops);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(isStaticContainer);
			ar(lootDrops);
			setLooted();
		}

	};
}


#endif