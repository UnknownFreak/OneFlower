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

	Input::Input() : mainWindowSource()
	{
	}

	courier::ChannelId Input::createWindowSource(std::string_view windowName)
	{
		std::string s = windowName.data();
		auto shared = std::make_shared<InputSource>(s);
		inputSources.emplace_back(shared);
		return shared->getId();
	}

	std::weak_ptr<InputSource> Input::getWindowSource(const courier::ChannelId windowId)
	{
		for (auto& it : inputSources)
		{
			if (it->getId() == windowId)
			{
				return it;
			}
		}
		return {};
	}

	void Input::removeWindowSource(const courier::ChannelId windowId)
	{
		for (auto it = inputSources.begin(); it != inputSources.end(); it++)
		{
			if (it->get()->getId() == windowId)
			{
				if (mainWindowSource.lock()->getId() == it->get()->getId())
				{
					mainWindowSource.reset();
				}
				inputSources.erase(it);
				break;
			}
		}
	}

	void Input::setMainWindowSource(const courier::ChannelId windowId)
	{
		mainWindowSource = getWindowSource(windowId);
	}

	std::weak_ptr<InputSource> Input::getMainWindowSource()
	{
		return mainWindowSource;
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