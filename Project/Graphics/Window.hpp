#ifndef ONE_WINDOW_HPP
#define ONE_WINDOW_HPP

#include <map>
#include <mutex>

#include <glm/glm.hpp>

#include <swizzle/Swizzle.hpp>

#include <Interfaces/IEngineModule.hpp>
#include <Helpers/Rect.hpp>
#include <Graphics/TransparencyMasker.hpp>
#include "UI/UIHandler.hpp"
#include "Model.hpp"

#include "Camera.hpp"
#include "CameraController.hpp"
#include "SkyBox.hpp"

#include <swizzle/asset2/Assets.hpp>

namespace Component
{
	class Base;
}
class GameObject;
namespace Graphics
{
	class RenderWindow : public Interfaces::IEngineResource<RenderWindow>, public sw::Application
	{

		common::Resource<sw::gfx::Shader> mFsq;
		common::Resource<sw::gfx::Material> mFsqMat;

		PerspectiveCamera cam;
		CameraController mController;

		std::unordered_map<Core::uuid, std::shared_ptr<Model>> models;
		std::unordered_map<Core::uuid, std::shared_ptr<Component::Transform>> positions;

		common::Resource<sw::gfx::CommandBuffer> mUploadBuffer;
		common::Resource<sw::gfx::CommandBuffer> mCmdBuffer;

		TransparencyMasker masker;
		const bool& drawHitbox;

		void ProcessCulling();
		Skybox mSkybox;
		bool m_isClosing = false;
		bool isThreadStopped = false;

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

		void setTileMapTransparencyHitbox(int index, Core::String group, Core::Rect<float> rect, float z);
		void addRenderable(const int& index, const Core::String& group, const glm::vec2& pos, const float& z, const Core::String& textureCoords, const Enums::TileTypes& type, bool addShadow=false);
		void clearDrawList();

		void Cull(std::vector<GameObject*>& colliders);

		void AddRenderable(GameObject* theObject);
		void RemoveRenderable(GameObject* theObject);

		Enums::EngineResourceType & getType() const
		{
			return type;
		}

		TransparencyMasker& getMasker();

		// Inherited via Application
		virtual void userSetup() override;
		virtual SwBool userUpdate(F32 dt) override;
		virtual void userCleanup() override;

		inline bool isClosing() const
		{
			return m_isClosing;
		}

		inline void setThreadStopped()
		{
			isThreadStopped = true;
		}

};
}


#endif //WINDOW_HPP