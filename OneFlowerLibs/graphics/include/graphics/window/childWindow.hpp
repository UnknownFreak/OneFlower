#pragma once

#include "renderLayer.hpp"

#include <utils/common/string.hpp>
#include <unordered_map>
#include <map>

#include <glm/vec3.hpp>

#include <graphics/renderable.hpp>

#include <swizzle/Swizzle.hpp>
#include <swizzle/ApplicationTemplate.hpp>
#include <ImGuiSwzzle.hpp>

#include <graphics/view/camera.hpp>
#include <graphics/view/cameraController.hpp>

#include <graphics/sky/skyBox.hpp>

namespace of::graphics::window
{
	class ChildWindow : public swizzle::Application
	{

		ChildWindow(swizzle::Application& parent, const of::common::String& windowName);

		virtual void userSetup() override
		{
		};
		virtual SwBool userUpdate(F32 dt) override
		{
		};
		virtual void userCleanup() override
		{
		};



	public:

		void render()
		{
		}

	private:

		swizzle::Application& m_parent;

	};
}