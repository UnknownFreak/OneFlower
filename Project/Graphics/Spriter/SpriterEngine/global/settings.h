#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>

#include <Helpers/String.hpp>

namespace SpriterEngine
{
	typedef void(*ErrorFunctionPointer)(const Core::String &errorMessage);

	class Settings
	{
	public:
		static bool renderDebugBoxes;
		static bool renderDebugPoints;
		static bool renderDebugBones;

		static bool enableDebugBones;

		static void simpleError(const Core::String &errorMessage);

		static void nullError(const Core::String &errorMessage);

		static void error(const Core::String &errorMessage);

		static void setErrorFunction(ErrorFunctionPointer errorFunction);

		static void suppressErrorOutput(bool suppress = true);

		static bool reverseYOnLoad;
		static bool reversePivotYOnLoad;
		static bool reverseAngleOnLoad;

	private:
		static ErrorFunctionPointer errFunction;
		static ErrorFunctionPointer previousErrorFunction;
	};
}
#endif // SETTINGS_H
