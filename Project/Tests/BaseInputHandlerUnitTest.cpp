#ifdef _UNITTESTS_

#include <functional>

#include <CppUnitTest.h>
#include <Input\BasicInputHandler.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Tests
{

	int pressCount = 0;
	int holdCount = 0;
	int releasedCount = 0;
	bool alternating = false;

	enum class FakeInputHandler {
		AlwaysPressed,
		NeverPressed,
		AlterningPressed,
	};

	typedef Input::Callback::Callback<bool, FakeInputHandler> FakeCallback;
	bool checkInput(FakeInputHandler t)
	{
		switch (t)
		{
		case Tests::FakeInputHandler::AlwaysPressed:
			return true;
		case Tests::FakeInputHandler::NeverPressed:
			return false;
		case Tests::FakeInputHandler::AlterningPressed:
			return alternating;
		default:
			break;
		}
		return false;
	}

	void pressedCallback(bool, FakeInputHandler, const float&)
	{
		pressCount++;
	}
	void holdCallback(bool, FakeInputHandler, const float&)
	{
		holdCount++;
	}
	void releaseCallback(bool, FakeInputHandler, const float&)
	{
		releasedCount++;
	}



	TEST_CLASS(BaseInputHandlerTestClass)
	{

		void update(size_t x)
		{
			size_t i = 0;
			for (; i < x; i++)
			{
				inputHandlerTest.update(0.f);
				alternating = !alternating;
			}
		}

		void reset()
		{
			pressCount = 0;
			holdCount = 0;
			releasedCount = 0;
			alternating = false;
		}

	public:
		static Input::BasicInputHandler<FakeInputHandler> inputHandlerTest;


		TEST_METHOD_CLEANUP(inputHandlerTestCleanup)
		{
			reset();
		}

		TEST_METHOD(TestAlwaysPressed)
		{
			inputHandlerTest.RegisterCallback(FakeCallback("pressed", pressedCallback), FakeInputHandler::AlwaysPressed, Enums::Input::Action::Press);
			inputHandlerTest.RegisterCallback(FakeCallback("hold", holdCallback), FakeInputHandler::AlwaysPressed, Enums::Input::Action::Hold);
			inputHandlerTest.RegisterCallback(FakeCallback("released", releaseCallback), FakeInputHandler::AlwaysPressed, Enums::Input::Action::Release);

			update(5);
			
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "pressed", Enums::Input::Action::Press);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "hold", Enums::Input::Action::Hold);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "released", Enums::Input::Action::Release);
		
			Assert::AreEqual(pressCount, 1);
			Assert::AreEqual(holdCount, 5);
			Assert::AreEqual(releasedCount, 0);
		}

		TEST_METHOD(TestNeverPressed)
		{
			inputHandlerTest.RegisterCallback(FakeCallback("pressed", pressedCallback), FakeInputHandler::NeverPressed, Enums::Input::Action::Press);
			inputHandlerTest.RegisterCallback(FakeCallback("hold", holdCallback), FakeInputHandler::NeverPressed, Enums::Input::Action::Hold);
			inputHandlerTest.RegisterCallback(FakeCallback("released", releaseCallback), FakeInputHandler::NeverPressed, Enums::Input::Action::Release);

			update(5);

			inputHandlerTest.removeCallback(FakeInputHandler::NeverPressed, "pressed", Enums::Input::Action::Press);
			inputHandlerTest.removeCallback(FakeInputHandler::NeverPressed, "hold", Enums::Input::Action::Hold);
			inputHandlerTest.removeCallback(FakeInputHandler::NeverPressed, "released", Enums::Input::Action::Release);

			Assert::AreEqual(pressCount, 0);
			Assert::AreEqual(holdCount, 0);
			Assert::AreEqual(releasedCount, 0);

		}

		TEST_METHOD(TestAlternatingPress)
		{
			inputHandlerTest.RegisterCallback(FakeCallback("pressed", pressedCallback), FakeInputHandler::AlterningPressed, Enums::Input::Action::Press);
			inputHandlerTest.RegisterCallback(FakeCallback("hold", holdCallback), FakeInputHandler::AlterningPressed, Enums::Input::Action::Hold);
			inputHandlerTest.RegisterCallback(FakeCallback("released", releaseCallback), FakeInputHandler::AlterningPressed, Enums::Input::Action::Release);
			update(7);


			inputHandlerTest.removeCallback(FakeInputHandler::AlterningPressed, "pressed", Enums::Input::Action::Press);
			inputHandlerTest.removeCallback(FakeInputHandler::AlterningPressed, "hold", Enums::Input::Action::Hold);
			inputHandlerTest.removeCallback(FakeInputHandler::AlterningPressed, "released", Enums::Input::Action::Release);

			Assert::AreEqual(pressCount, 3);
			Assert::AreEqual(holdCount, 3);
			Assert::AreEqual(releasedCount, 3);
		}

		TEST_METHOD(TestRemoveMethodWithPressedInputWithRemoveFlagTrue)
		{
			inputHandlerTest.RegisterCallback(FakeCallback("pressed", pressedCallback), FakeInputHandler::AlwaysPressed, Enums::Input::Action::Press);
			inputHandlerTest.RegisterCallback(FakeCallback("hold", holdCallback), FakeInputHandler::AlwaysPressed, Enums::Input::Action::Hold);
			inputHandlerTest.RegisterCallback(FakeCallback("released", releaseCallback, true), FakeInputHandler::AlwaysPressed, Enums::Input::Action::Release);

			update(5);

			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "pressed", Enums::Input::Action::Press);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "hold", Enums::Input::Action::Hold);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "released", Enums::Input::Action::Release);

			Assert::AreEqual(pressCount, 1);
			Assert::AreEqual(holdCount, 5);
			Assert::AreEqual(releasedCount, 1);

		}

		TEST_METHOD(TestRemoveMethodWithNeverPressedInputWithRemoveFlagTrue)
		{
			inputHandlerTest.RegisterCallback(FakeCallback("pressed", pressedCallback), FakeInputHandler::NeverPressed, Enums::Input::Action::Press);
			inputHandlerTest.RegisterCallback(FakeCallback("hold", holdCallback), FakeInputHandler::NeverPressed, Enums::Input::Action::Hold);
			inputHandlerTest.RegisterCallback(FakeCallback("released", releaseCallback, true), FakeInputHandler::NeverPressed, Enums::Input::Action::Release);

			update(5);

			inputHandlerTest.removeCallback(FakeInputHandler::NeverPressed, "pressed", Enums::Input::Action::Press);
			inputHandlerTest.removeCallback(FakeInputHandler::NeverPressed, "hold", Enums::Input::Action::Hold);
			inputHandlerTest.removeCallback(FakeInputHandler::NeverPressed, "released", Enums::Input::Action::Release);

			Assert::AreEqual(pressCount, 0);
			Assert::AreEqual(holdCount, 0);
			Assert::AreEqual(releasedCount, 0);


		}

		TEST_METHOD(TestRemoveCallbackAndAddAgainGeneratesMorePressCounts)
		{
			inputHandlerTest.RegisterCallback(FakeCallback("pressed", pressedCallback), FakeInputHandler::AlwaysPressed, Enums::Input::Action::Press);
			inputHandlerTest.RegisterCallback(FakeCallback("hold", holdCallback), FakeInputHandler::AlwaysPressed, Enums::Input::Action::Hold);
			inputHandlerTest.RegisterCallback(FakeCallback("released", releaseCallback), FakeInputHandler::AlwaysPressed, Enums::Input::Action::Release);

			update(5);

			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "pressed", Enums::Input::Action::Press);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "hold", Enums::Input::Action::Hold);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "released", Enums::Input::Action::Release);

			Assert::AreEqual(pressCount, 1);
			Assert::AreEqual(holdCount, 5);
			Assert::AreEqual(releasedCount, 0);

			inputHandlerTest.RegisterCallback(FakeCallback("pressed", pressedCallback), FakeInputHandler::AlwaysPressed, Enums::Input::Action::Press);
			inputHandlerTest.RegisterCallback(FakeCallback("hold", holdCallback), FakeInputHandler::AlwaysPressed, Enums::Input::Action::Hold);
			inputHandlerTest.RegisterCallback(FakeCallback("released", releaseCallback, true), FakeInputHandler::AlwaysPressed, Enums::Input::Action::Release);

			update(5);

			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "pressed", Enums::Input::Action::Press);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "hold", Enums::Input::Action::Hold);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "released", Enums::Input::Action::Release);

			Assert::AreEqual(pressCount, 2);
			Assert::AreEqual(holdCount, 10);
			Assert::AreEqual(releasedCount, 1);

		}

	};
	Input::BasicInputHandler<FakeInputHandler> BaseInputHandlerTestClass::inputHandlerTest(checkInput);
}
#endif