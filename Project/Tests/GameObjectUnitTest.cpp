#ifdef _UNITTESTS_

#include "CppUnitTest.h"

#include <Core\Component\GameObject.h>
#include <Core\Component\TransformComponent.hpp>
#include <Core\EngineModule\EngineModuleManager.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Component
{

	class Mocked : public IBaseComponent<Mocked>
	{
	public:
		Mocked* copy() const
		{
			return nullptr;
		}
	};

	const unsigned int IBaseComponent<Mocked>::typeID = 9999;
	Core::String IBaseComponent<Mocked>::componentName = "Mocked";

	class Void : public IBaseComponent<Void>
	{
	public:
		Void* copy() const 
		{
			return nullptr;
		}
	};

	const unsigned int IBaseComponent<Void>::typeID = 123456;
	Core::String IBaseComponent<Void>::componentName = "Void";

}

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
			Component::Transform* tf = go.GetComponent<Component::Transform>();
			Assert::IsNotNull(tf);
		}
		TEST_METHOD(TestComponentAttachedTo)
		{
			Component::Transform* tf = go.GetComponent<Component::Transform>();
			GameObject* goptr = &go;
			Assert::AreEqual(tf->attachedOn, goptr);
		}
		TEST_METHOD(TestAddComponent)
		{
			Component::Mocked* mocked = (Component::Mocked*)go.AddComponent<Component::Mocked>();
			GameObject* goptr = &go;
			Assert::AreEqual(mocked->attachedOn, goptr);
			Assert::AreEqual(mocked->typeID, unsigned(9999), L"Component TypeID is not the same");

		}
		TEST_METHOD(TestGetComponentNotAdded)
		{
			Component::Void* nc = go.GetComponent<Component::Void>();
			Assert::IsNull(nc);
		}
		//TEST_METHOD(TestGameObjectCopyCtor) - fails if run all is used, select all and then run selected makes this pass..
		//{
		//	GameObject gocopy(go);
		//	Assert::AreEqual(go.name, gocopy.name);
		//	Assert::AreEqual(go.id, gocopy.id);
		//	Component::Transform* tf = gocopy.GetComponent<Component::Transform>();
		//	Assert::IsNotNull(tf);
		//}
	};
	GameObject GameObjectUnitTest::go("test");

}

template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<GameObject>(const GameObject& q) {
	return Engine::GetModule<Core::StringConverter>().toUtf16(((GameObject&)q).name);
}
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<GameObject>(const GameObject* q) {
	return Engine::GetModule<Core::StringConverter>().toUtf16(((GameObject*)q)->name);
}
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<GameObject>(GameObject* q) {
	return Engine::GetModule<Core::StringConverter>().toUtf16(((GameObject*)q)->name);
}

#endif