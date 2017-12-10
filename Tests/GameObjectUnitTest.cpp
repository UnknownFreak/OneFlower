#ifdef _UNITTESTS_

#include "CppUnitTest.h"

#include <Core\Component\GameObject.h>
#include <Core\Component\TransformComponent.hpp>
#include <Core\IEngineResource\EngineResourceManager.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



class MockedComponent : public IBaseComponent<MockedComponent>
{
public:
	MockedComponent* copy() const
	{
		return nullptr;
	}
};

const unsigned int IBaseComponent<MockedComponent>::typeID = 9999;
Core::String IBaseComponent<MockedComponent>::componentName = "MockedComponent";

class NullComponent : public IBaseComponent<NullComponent>
{
public:
	NullComponent* copy() const 
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
		static GameObject go;

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
		//TEST_METHOD(TestGameObjectCopyCtor) - fails if run all is used, select all and then run selected makes this pass..
		//{
		//	GameObject gocopy(go);
		//	Assert::AreEqual(go.name, gocopy.name);
		//	Assert::AreEqual(go.id, gocopy.id);
		//	Component::TransformComponent* tf = gocopy.GetComponent<Component::TransformComponent>();
		//	Assert::IsNotNull(tf);
		//}
	};
	GameObject GameObjectUnitTest::go("test");

}

template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<GameObject>(const GameObject& q) {
	return Engine::Get<Core::StringConverter>().toUtf16(((GameObject&)q).name);
}
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<GameObject>(const GameObject* q) {
	return Engine::Get<Core::StringConverter>().toUtf16(((GameObject*)q)->name);
}
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<GameObject>(GameObject* q) {
	return Engine::Get<Core::StringConverter>().toUtf16(((GameObject*)q)->name);
}

#endif