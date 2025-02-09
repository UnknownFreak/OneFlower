#include "input/input.hpp"
#include "input/internalInput.hpp"

#include <logger/Logger.hpp>

#include <courier/courier.hpp>
#include <engine/courier/topic.hpp>
#include <engine/courier/messageType.hpp>
#include <cmath>

static of::input::Input* g_input = nullptr;

namespace of::input
{

	void Input::dispatchEvents()
	{
		
	}

	Input& get()
	{
		return *g_input;
	}

	void init()
	{
		if (g_input == nullptr)
		{
			g_input = new Input();
		}
	}

	void shutdown()
	{
		if (g_input)
		{
			delete g_input;
			g_input = nullptr;
		}
	}
}