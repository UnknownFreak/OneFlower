#ifdef _UNITTESTS_
#include <CppUnitTest.h>

#include <Core\IEngineResource\EngineResourceManager.hpp>

TEST_MODULE_CLEANUP(module_cleanup)
{
	Engine::Dispose();
}

#endif