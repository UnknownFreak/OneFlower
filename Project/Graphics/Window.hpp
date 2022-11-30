#ifndef ONE_WINDOW_HPP
#define ONE_WINDOW_HPP

#include <map>
#include <mutex>

#include <glm/glm.hpp>

#include <swizzle/Swizzle.hpp>

#include <module/IEngineModule.hpp>
#include <Helpers/Rect.hpp>
#include <Graphics/TransparencyMasker.hpp>
#include "UI/UIHandler.hpp"
#include "Model.hpp"

#include "Camera.hpp"
#include "CameraController.hpp"
#include "SkyBox.hpp"

#include <swizzle/asset2/Assets.hpp>
#include <Graphics/UI/Stats.hpp>

namespace Component
{
	class Base;
}
class GameObject;
namespace Graphics
{
	class RenderWindow : public of::module::interface::IEngineResource<RenderWindow>, public sw::Application
	{

		class DynamicWindowListener : public swizzle::EventHandler<swizzle::core::WindowEvent>
		{
			std::unordered_map<of::common::String, std::function<void(const swizzle::core::WindowEvent&)>> events;
		public:
			DynamicWindowListener() = default;

			inline virtual void publishEvent(const swizzle::core::WindowEvent& evt)
			{
				for (auto& it : events)
				{
					it.second(evt);
				}
			}

			void addListener(const of::common::String& name, std::function<void(const swizzle::core::WindowEvent&)> fn)
			{
				events[name] = fn;
			}
			void removeListener(const of::common::String& name)
			{
				events.erase(name);
			}
		};

		DynamicWindowListener listener;

		Graphics::UI::Stats* fps = nullptr;

		common::Resource<sw::gfx::Shader> mFsq;
		common::Resource<sw::gfx::Material> mFsqMat;

		PerspectiveCamera cam;
		CameraController mController;

		std::unordered_map<of::common::uuid, std::shared_ptr<Model>> models;
		std::unordered_map<of::common::uuid, std::shared_ptr<Component::Transform>> positions;

		common::Resource<sw::gfx::CommandBuffer> mUploadBuffer;
		common::Resource<sw::gfx::CommandBuffer> mCmdBuffer;

		TransparencyMasker masker;
		const bool& drawHitbox;

		void ProcessCulling();
		Skybox mSkybox;

		void drawStats();

	public:

		Graphics::UI::UIHandler& ui;

		float shadowAngle = 0.f;
		float timeOfDay = 0.f;
		float shadowLengthX = 0.f;
		float shadowLengthY = 0.f;
		float theta = 3;
		Core::Rect<float> renderBox;
	public:

		RenderWindow();
		~RenderWindow();

		std::shared_ptr<swizzle::gfx::GfxContext> getGfxContext();
		std::shared_ptr<swizzle::gfx::CommandBuffer> getCommandBuffer();
		std::shared_ptr<swizzle::gfx::CommandBuffer> getUploadBuffer();
		std::shared_ptr<swizzle::gfx::Swapchain> getSwapchain();

		void draw();
		void drawUI();

		void setFramerate(const unsigned& limit) const;

		void moveCamera(const glm::vec2& vec);

		void setTileMapTransparencyHitbox(int index, of::common::String group, Core::Rect<float> rect, float z);
		void addRenderable(const int& index, const of::common::String& group, const glm::vec2& pos, const float& z, const of::common::String& textureCoords, const Enums::TileTypes& type, bool addShadow=false);
		void clearDrawList();

		void Cull(std::vector<GameObject*>& colliders);

		void AddRenderable(GameObject* theObject);
		void RemoveRenderable(GameObject* theObject);

		DynamicWindowListener& getEventListener();

		of::module::EngineResourceType & getType() const
		{
			return type;
		}

		TransparencyMasker& getMasker();

		// Inherited via Application
		virtual void userSetup() override;
		virtual SwBool userUpdate(F32 dt) override;
		virtual void userCleanup() override;

		void postInitialize();

};
}


#endif //WINDOW_HPP