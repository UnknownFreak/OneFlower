#ifdef _UNITTESTS_
#include <cereal/types/polymorphic.hpp>
#include <CppUnitTest.h>

#include <Core\EngineModule\EngineModuleManager.hpp>

TEST_MODULE_CLEANUP(module_cleanup)
{
	Engine::Dispose();
}

#endif