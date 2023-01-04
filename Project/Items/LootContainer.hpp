#ifndef LootContainer_Hpp
#define LootContainer_Hpp

#include <file/FileId.hpp>

#include <object/component/BaseComponent.hpp>

namespace of::object::component
{
	class LootContainer : public Base
	{
		void setLooted();
		virtual void onMessage(const of::object::messaging::Message& message) override;
	public:
		bool looted;
		bool isStaticContainer;

		std::unordered_map<of::file::FileId, size_t> lootDrops;


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
		virtual void onCollision(GameObject* the_collidee) override;
		virtual void Update() override;
		virtual void Simulate(const float& fElapsedTime) override;
		virtual void onDeath() override;
		virtual void onDelete() override;

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

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
		of::common::uuid getType() const override
		{
			return typeId;
		};

		of::common::String getTypeName() const override
		{
			return "LootContainer";
		};

		static constexpr of::common::uuid typeId = "6f45ab1c-7a29-417b-b9fb-d6db1789696b";
	};
}


#endif