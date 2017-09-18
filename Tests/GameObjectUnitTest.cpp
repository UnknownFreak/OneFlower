#define _EDITOR_

#include "CppUnitTest.h"

#include <Core\Component\GameObject.h>
#include <Core\Component\TransformComponent.hpp>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;



class MockedComponent : public IBaseComponent<MockedComponent>
{
public:
	MockedComponent* copy()
	{
		return nullptr;
	}
};

const unsigned int IBaseComponent<MockedComponent>::typeID = 9999;
Core::String IBaseComponent<MockedComponent>::componentName = "MockedComponent";

class NullComponent : public IBaseComponent<NullComponent>
{
public:
	NullComponent* copy()
	{
		return nullptr;
	}
};

const unsigned int IBaseComponent<NullComponent>::typeID = 123456;
Core::String IBaseComponent<NullComponent>::componentName = "NullComponent";


namespace Tests
{

	TEST_CLASS(GameObjectUnitTest)
	{
	public:
		static Core::StringConverter con;
		static GameObject go;

		TEST_CLASS_CLEANUP(Cleanup)
		{
			con.deconstruct();
		}

		TEST_METHOD(TestGameObjectName)
		{
			Assert::AreEqual(go.name.c_str(), "test");
		}

		TEST_METHOD(TestGetComponent)
		{
			Component::TransformComponent* tf = go.GetComponent<Component::TransformComponent>();
			Assert::IsNotNull(tf);
		}
		TEST_METHOD(TestComponentAttachedTo)
		{
			Component::TransformComponent* tf = go.GetComponent<Component::TransformComponent>();
			GameObject* goptr = &go;
			Assert::AreEqual(tf->attachedOn, goptr);
		}
		TEST_METHOD(TestAddComponent)
		{
			MockedComponent* mocked = (MockedComponent*)go.AddComponent<MockedComponent>();
			GameObject* goptr = &go;
			Assert::AreEqual(mocked->attachedOn, goptr);
			Assert::AreEqual(mocked->typeID, unsigned(9999), L"Component TypeID is not the same");

		}
		TEST_METHOD(TestGetComponentNotAdded)
		{
			NullComponent* nc = go.GetComponent<NullComponent>();
			Assert::IsNull(nc);
		}
	};
	GameObject GameObjectUnitTest::go("test");
	Core::StringConverter GameObjectUnitTest::con;

}

template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<GameObject>(const GameObject& q) {
	return Tests::GameObjectUnitTest::con.toUtf16(((GameObject&)q).name);
}
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<GameObject>(const GameObject* q) {
	return Tests::GameObjectUnitTest::con.toUtf16(((GameObject*)q)->name);
}
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<GameObject>(GameObject* q) {
	return Tests::GameObjectUnitTest::con.toUtf16(((GameObject*)q)->name);
}