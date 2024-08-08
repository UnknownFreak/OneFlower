#pragma once

#include <foundation/PxErrorCallback.h>

namespace of::physics
{
	class ErrorCallBack : public physx::PxErrorCallback
	{
	public:
		virtual void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override;
	};

}