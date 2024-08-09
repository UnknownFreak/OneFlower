#include <physics/errorCallback.hpp>
#include <logger/Logger.hpp>
#include <iostream>

namespace of::physics
{
	void ErrorCallBack::reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line)
	{
		of::logger::get().getLogger("PhysX").Always(code, message, file, line);
		std::cout << message << " " << file << " " << line << std::endl;
	}
}