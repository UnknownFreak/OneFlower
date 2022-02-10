#pragma once
#ifdef _UNITTESTS_
#include <cereal/types/polymorphic.hpp>

#include <Helpers/String.hpp>
#include <Interfaces/IRequestable.hpp>
#include <Requirement/Requirement.hpp>

#include <Quest/QuestObjective.hpp>

namespace Tests
{

	class DummyObjective : public Questing::QuestObjective
	{

	public:
		bool completeOnCall = false;
		bool failOnCall = false;
		bool completeOrFailOnCall = false;


		virtual size_t onEnemyDefeated(GameObject*) override
		{
			if (completeOnCall)
				return completeObjective();
			else if (failOnCall)
				return failObjective();
			else if (completeOrFailOnCall)
				return completeOrFailObjective();
			return objectiveId;
		}
		virtual size_t onItemPickUp(Items::Base*) override
		{
			if (completeOnCall)
				return completeObjective();
			else if (failOnCall)
				return failObjective();
			else if (completeOrFailOnCall)
				return completeOrFailObjective();
			return objectiveId;
		}
		virtual size_t onItemDropped(Items::Base*)override
		{
			if (completeOnCall)
				return completeObjective();
			else if (failOnCall)
				return failObjective();
			else if (completeOrFailOnCall)
				return completeOrFailObjective();
			return objectiveId;
		}

		// Inherited via QuestObjective
		virtual Questing::ObjectiveState getCurrentState() override
		{
			return Questing::ObjectiveState();
		}
		virtual void restoreState(const Questing::ObjectiveState&) override
		{
		}
	};

	class DummyRequirement : public Requirement::Requirement
	{
	public:
		bool isFullfilled;
		DummyRequirement(const bool& b) : isFullfilled(b) {};
		virtual bool fullfilled() { return isFullfilled; };

		inline virtual std::unique_ptr<Requirement> clone() const override { return nullptr; };
	};


	class MockedSaveable : public Interfaces::IRequestable
	{
	public:
		Core::String test_string;
		MockedSaveable() : MockedSaveable(Core::uuid::nil(), "") {}
		MockedSaveable(Core::uuid id, Core::String test_string = "") : IRequestable("test", id, OneVersion(0, 0, 0), Enums::ObjectType::ColliderChunk), test_string(test_string)
		{
		}
		MockedSaveable(const MockedSaveable& c) : IRequestable(c), test_string(c.test_string)
		{
		}
		MockedSaveable& operator=(const MockedSaveable& r)
		{
			test_string = r.test_string;
			mode = r.mode;
			ID = r.ID;
			fromMod = r.fromMod;
			return *this;
		}

		virtual Interfaces::TypeInfo getTrait() const
		{
			return { Interfaces::Trait<MockedSaveable>::typeId };
		}

		template<class T>
		void save(T& archive) const
		{
			archive(cereal::base_class<IRequestable>(this));
			archive(test_string);
		}
		template<class T>
		void load(T& archive)
		{
			archive(cereal::base_class<IRequestable>(this));
			archive(test_string);
		}
	};

	class MockedSaveable2 : public Interfaces::IRequestable
	{
	public:
		Core::String test_string;
		MockedSaveable2() : MockedSaveable2(Core::uuid::nil(), "") {}
		MockedSaveable2(Core::uuid id, Core::String test_string = "") : IRequestable("test", id, OneVersion(0, 0, 0), Enums::ObjectType::DBZone), test_string(test_string)
		{
		}
		MockedSaveable2(const MockedSaveable2& c) : IRequestable(c), test_string(c.test_string)
		{
		}
		MockedSaveable2& operator=(const MockedSaveable2& r)
		{
			test_string = r.test_string;
			mode = r.mode;
			ID = r.ID;
			fromMod = r.fromMod;
			return *this;
		}
		virtual Interfaces::TypeInfo getTrait() const
		{
			return { Interfaces::Trait<MockedSaveable2>::typeId };
		}

		template<class T>
		void save(T& archive) const
		{
			archive(cereal::base_class<IRequestable>(this));
			archive(test_string);
		}
		template<class T>
		void load(T& archive)
		{
			archive(cereal::base_class<IRequestable>(this));
			archive(test_string);
		}
	};

	class MockedSaveable3 : public MockedSaveable2
	{
	public:
		Core::String another_test_string;
		MockedSaveable3() : MockedSaveable3(Core::uuid::nil(), "") {}
		MockedSaveable3(Core::uuid id, Core::String test_string = "", Core::String another_test_string = "") : MockedSaveable2(id, test_string), another_test_string(another_test_string)
		{
			//objectType = Enums::ObjectType::DialogTree;
		}
		MockedSaveable3(const MockedSaveable3& c) : MockedSaveable3(c.ID, c.test_string, c.another_test_string)
		{
		}
		MockedSaveable3& operator=(const MockedSaveable3& r)
		{
			test_string = r.test_string;
			objectType = r.objectType;
			mode = r.mode;
			ID = r.ID;
			fromMod = r.fromMod;
			return *this;
		}
		virtual Interfaces::TypeInfo getTrait() const
		{
			return { Interfaces::Trait<MockedSaveable3>::typeId,  {Interfaces::Trait<MockedSaveable2>::typeId} };
		}

		template<class T>
		void save(T& archive) const
		{
			archive(cereal::base_class<MockedSaveable2>(this));
			archive(another_test_string);
		}
		template<class T>
		void load(T& archive)
		{
			archive(cereal::base_class<MockedSaveable2>(this));
			archive(another_test_string);
		}
	};
}

Core::uuid Interfaces::Trait<Tests::MockedSaveable>::typeId = Core::uuid("1d8874c2-0012-4e2a-8a22-e243ebfa2567");
Core::uuid Interfaces::Trait<Tests::MockedSaveable2>::typeId = Core::uuid("fad05975-f00a-44c0-a975-70960d2def9f");
Core::uuid Interfaces::Trait<Tests::MockedSaveable3>::typeId = Core::uuid("0192dd17-021e-4542-8729-8e283fb18b70");

CEREAL_REGISTER_TYPE(Tests::MockedSaveable);
CEREAL_REGISTER_TYPE(Tests::MockedSaveable2);
CEREAL_REGISTER_TYPE(Tests::MockedSaveable3);

CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, Tests::MockedSaveable);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, Tests::MockedSaveable2);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, Tests::MockedSaveable3);
#endif