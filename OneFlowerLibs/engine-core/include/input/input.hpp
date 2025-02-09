#pragma once

#include <input/inputSource.hpp>

#include <vector>

namespace of::input
{

	class Input
	{
		std::vector<std::shared_ptr<InputSource>> inputSources;
		std::weak_ptr<InputSource> mainWindowSource;
	public:

		Input();
		Input& operator=(const Input&) = delete;

		courier::ChannelId createWindowSource(std::string_view windowName);

		std::weak_ptr<InputSource> getWindowSource(const courier::ChannelId windowId);
		void removeWindowSource(const courier::ChannelId windowId);


		void setMainWindowSource(const courier::ChannelId windowId);
		std::weak_ptr<InputSource> getMainWindowSource();

	};

	Input& get();


}