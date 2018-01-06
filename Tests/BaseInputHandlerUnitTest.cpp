#ifdef _UNITTESTS_
#include <CppUnitTest.h>
#include <functional>
#include <Input\BaseInputHandler.hpp>

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
			false;
		}
	}

	void pressedCallback()
	{
		pressCount++;
	}
	void holdCallback()
	{
		holdCount++;
	}
	void releaseCallback()
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
				inputHandlerTest.update();
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
		static BaseCallbackholder<FakeInputHandler> inputHandlerTest;


		TEST_METHOD_CLEANUP(inputHandlerTestCleanup)
		{
			reset();
		}

		TEST_METHOD(TestAlwaysPressed)
		{
			inputHandlerTest.RegisterCallback(Callback("pressed", pressedCallback), FakeInputHandler::AlwaysPressed, Input::Action::Press);
			inputHandlerTest.RegisterCallback(Callback("hold", holdCallback), FakeInputHandler::AlwaysPressed, Input::Action::Hold);
			inputHandlerTest.RegisterCallback(Callback("released", releaseCallback), FakeInputHandler::AlwaysPressed, Input::Action::Release);

			update(5);
			
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "pressed", Input::Action::Press);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "hold", Input::Action::Hold);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "released", Input::Action::Release);
		
			Assert::AreEqual(pressCount, 1);
			Assert::AreEqual(holdCount, 5);
			Assert::AreEqual(releasedCount, 0);
		}

		TEST_METHOD(TestNeverPressed)
		{
			inputHandlerTest.RegisterCallback(Callback("pressed", pressedCallback), FakeInputHandler::NeverPressed, Input::Action::Press);
			inputHandlerTest.RegisterCallback(Callback("hold", holdCallback), FakeInputHandler::NeverPressed, Input::Action::Hold);
			inputHandlerTest.RegisterCallback(Callback("released", releaseCallback), FakeInputHandler::NeverPressed, Input::Action::Release);

			update(5);

			inputHandlerTest.removeCallback(FakeInputHandler::NeverPressed, "pressed", Input::Action::Press);
			inputHandlerTest.removeCallback(FakeInputHandler::NeverPressed, "hold", Input::Action::Hold);
			inputHandlerTest.removeCallback(FakeInputHandler::NeverPressed, "released", Input::Action::Release);

			Assert::AreEqual(pressCount, 0);
			Assert::AreEqual(holdCount, 0);
			Assert::AreEqual(releasedCount, 0);

		}

		TEST_METHOD(TestAlternatingPress)
		{
			inputHandlerTest.RegisterCallback(Callback("pressed", pressedCallback), FakeInputHandler::AlterningPressed, Input::Action::Press);
			inputHandlerTest.RegisterCallback(Callback("hold", holdCallback), FakeInputHandler::AlterningPressed, Input::Action::Hold);
			inputHandlerTest.RegisterCallback(Callback("released", releaseCallback), FakeInputHandler::AlterningPressed, Input::Action::Release);
			update(7);


			inputHandlerTest.removeCallback(FakeInputHandler::AlterningPressed, "pressed", Input::Action::Press);
			inputHandlerTest.removeCallback(FakeInputHandler::AlterningPressed, "hold", Input::Action::Hold);
			inputHandlerTest.removeCallback(FakeInputHandler::AlterningPressed, "released", Input::Action::Release);

			Assert::AreEqual(pressCount, 3);
			Assert::AreEqual(holdCount, 3);
			Assert::AreEqual(releasedCount, 3);
		}

		TEST_METHOD(TestRemoveMethodWithPressedInputWithRemoveFlagTrue)
		{
			inputHandlerTest.RegisterCallback(Callback("pressed", pressedCallback), FakeInputHandler::AlwaysPressed, Input::Action::Press);
			inputHandlerTest.RegisterCallback(Callback("hold", holdCallback), FakeInputHandler::AlwaysPressed, Input::Action::Hold);
			inputHandlerTest.RegisterCallback(Callback("released", releaseCallback, true), FakeInputHandler::AlwaysPressed, Input::Action::Release);

			update(5);

			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "pressed", Input::Action::Press);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "hold", Input::Action::Hold);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "released", Input::Action::Release);

			Assert::AreEqual(pressCount, 1);
			Assert::AreEqual(holdCount, 5);
			Assert::AreEqual(releasedCount, 1);

		}

		TEST_METHOD(TestRemoveMethodWithNeverPressedInputWithRemoveFlagTrue)
		{
			inputHandlerTest.RegisterCallback(Callback("pressed", pressedCallback), FakeInputHandler::NeverPressed, Input::Action::Press);
			inputHandlerTest.RegisterCallback(Callback("hold", holdCallback), FakeInputHandler::NeverPressed, Input::Action::Hold);
			inputHandlerTest.RegisterCallback(Callback("released", releaseCallback, true), FakeInputHandler::NeverPressed, Input::Action::Release);

			update(5);

			inputHandlerTest.removeCallback(FakeInputHandler::NeverPressed, "pressed", Input::Action::Press);
			inputHandlerTest.removeCallback(FakeInputHandler::NeverPressed, "hold", Input::Action::Hold);
			inputHandlerTest.removeCallback(FakeInputHandler::NeverPressed, "released", Input::Action::Release);

			Assert::AreEqual(pressCount, 0);
			Assert::AreEqual(holdCount, 0);
			Assert::AreEqual(releasedCount, 0);


		}

		TEST_METHOD(TestRemoveCallbackAndAddAgainGeneratesMorePressCounts)
		{
			inputHandlerTest.RegisterCallback(Callback("pressed", pressedCallback), FakeInputHandler::AlwaysPressed, Input::Action::Press);
			inputHandlerTest.RegisterCallback(Callback("hold", holdCallback), FakeInputHandler::AlwaysPressed, Input::Action::Hold);
			inputHandlerTest.RegisterCallback(Callback("released", releaseCallback), FakeInputHandler::AlwaysPressed, Input::Action::Release);

			update(5);

			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "pressed", Input::Action::Press);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "hold", Input::Action::Hold);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "released", Input::Action::Release);

			Assert::AreEqual(pressCount, 1);
			Assert::AreEqual(holdCount, 5);
			Assert::AreEqual(releasedCount, 0);

			inputHandlerTest.RegisterCallback(Callback("pressed", pressedCallback), FakeInputHandler::AlwaysPressed, Input::Action::Press);
			inputHandlerTest.RegisterCallback(Callback("hold", holdCallback), FakeInputHandler::AlwaysPressed, Input::Action::Hold);
			inputHandlerTest.RegisterCallback(Callback("released", releaseCallback, true), FakeInputHandler::AlwaysPressed, Input::Action::Release);

			update(5);

			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "pressed", Input::Action::Press);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "hold", Input::Action::Hold);
			inputHandlerTest.removeCallback(FakeInputHandler::AlwaysPressed, "released", Input::Action::Release);

			Assert::AreEqual(pressCount, 2);
			Assert::AreEqual(holdCount, 10);
			Assert::AreEqual(releasedCount, 1);

		}

	};
	BaseCallbackholder<FakeInputHandler> BaseInputHandlerTestClass::inputHandlerTest(checkInput);
}
#endif