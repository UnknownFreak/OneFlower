#include <world/LoadingStateInfo.hpp>

namespace of::world
{
	LoadingStateInfo::LoadingStateInfo(const LoadingState& theState, const bool& isLoading) : theState(theState), isLoading(isLoading)
	{
	}
}