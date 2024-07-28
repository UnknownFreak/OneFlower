#ifndef LootContainer_Hpp
#define LootContainer_Hpp

#include <file/FileId.hpp>

#include <component/base.hpp>

namespace of::component
{
	class LootContainer : public Base
	{
		void setLooted();
		virtual void onMessage(const of::object::messaging::Message& message) override;
		virtual void initialize() override {};
		virtual void deconstruct() override {};

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

		void loot(object::GameObject* object);
		bool isLooted() const;

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