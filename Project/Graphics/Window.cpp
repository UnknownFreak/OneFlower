#include "Window.hpp"

#include <Object/GameObject.hpp>
#include <Object/BaseComponent.hpp>
#include "Render.hpp"
#include <Physics/Colliders/EntityCollider.hpp>
#include <Physics/Colliders/VisionCollider.hpp>
#include <Graphics/PlayerInteractionPrompt.hpp>
#include <File/GameConfig.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_swizzle.hpp>
#include <utils/StringUtils.hpp>

Enums::EngineResourceType Interfaces::IEngineResource<Graphics::RenderWindow>::type = Enums::EngineResourceType::Graphics;
namespace Graphics
{
	void RenderWindow::Cull(std::vector<GameObject*>& )
	{
	}

	void RenderWindow::AddRenderable(GameObject* )
	{
	}
	void RenderWindow::RemoveRenderable(GameObject* )
	{
	}
	TransparencyMasker& RenderWindow::getMasker()
	{
		return masker;
	}

	void RenderWindow::userSetup()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplSwizzle_Init(mGfxContext, mWindow);

		//auto& gameConfig = Engine::GetModule<EngineModule::GameConfig>();
		//mWindow->setSize(gameConfig.videoMode.first, gameConfig.videoMode.second);
		mWindow->setTitle("Vk Window");

		mSwapchain->setVsync(sw::gfx::VSyncTypes::vSyncOn);
		mCmdBuffer = mGfxContext->createCommandBuffer(3);

		cam.setPosition({ 0.0F, 0.0F, 5.5F });

		mUniformBuffer = mGfxContext->createBuffer(sw::gfx::BufferType::UniformBuffer);


		sw::gfx::ShaderAttributeList attribFsq = {};
		attribFsq.mEnableBlending = true;

		mFsq = mSwapchain->createShader(attribFsq);
		mFsq->load("swizzle/data/shaders/fsq.shader");

		mFsqMat = mGfxContext->createMaterial(mFsq);
		ImGui_ImplSwizzle_SetMaterial(mFsqMat);
	}

	SwBool RenderWindow::userUpdate(F32 )
	{
		
		return mWindow->isVisible();
	}

	void RenderWindow::userCleanup()
	{
	}

	void RenderWindow::ProcessCulling()
	{
	}

	RenderWindow::RenderWindow() :
		drawHitbox(Engine::GetModule<Globals>().boolGlobals[Globals::GLOBAL_DRAW_HITBOX]),
		ui(Engine::GetModule<Graphics::UI::UIHandler>()),
		cam(glm::radians(45.0F), 1280, 720), mController(cam)
	{
	}

	RenderWindow::~RenderWindow()
	{
	}

	std::shared_ptr<swizzle::gfx::GfxContext>& RenderWindow::getGfxContext()
	{
		return mGfxContext;
	}

	std::shared_ptr<swizzle::gfx::CommandBuffer>& RenderWindow::getCommandBuffer()
	{
		return mCmdBuffer;
	}

	void RenderWindow::draw()
	{
		//mFpsCounter.tick(dt);
		std::string title;
		title.reserve(1024);
		title += "Frames: " + std::to_string(mSwapchain->getFrameCounter()) + "\n";
		title += "FPS: " + std::to_string(mFpsCounter.getFps()) + "\n\n";

		title += std::string(mGfxContext->getSelectedDeviceName()) + "\n";

		auto iter = mGfxContext->getStatisticsIterator();

		do
		{
			OPTICK_EVENT("Parse Stats");
			if (iter->getType() == sw::gfx::GfxStatsType::MemoryStats)
			{
				sw::gfx::MemoryStatistics* memStat = (sw::gfx::MemoryStatistics*)iter->getStatisticsData();

				title += "Memory Heap: " + std::string(memStat->mName) + "\n";
				title += "  Mem: " + utils::toMemoryString(memStat->mUsed) + "/" + utils::toMemoryString(memStat->mSize);
				title += "; Allocs: " + std::to_string(memStat->mNumAllocations) + "p, " + std::to_string(memStat->mNumVirtualAllocations) + "v\n";
			}
			else if (iter->getType() == sw::gfx::GfxStatsType::DeviceStats)
			{
				sw::gfx::DeviceStatistics* devStats = (sw::gfx::DeviceStatistics*)iter->getStatisticsData();
				title += "Device\n";
				title += "  Num Staged Objects: " + std::to_string(devStats->mNumStagedObjects) + "\n";
				title += "  Num Textures: " + std::to_string(devStats->mNumTextures) + "\n";
				title += "  Num Buffers: " + std::to_string(devStats->mNumBuffers) + "\n";
				title += "  Pipelines: " + std::to_string(devStats->mNumPipelines) + "\n";
			}

		} while (iter->next());

		/*title += "Staged objects: " + std::to_string(stats.mStagedObjects) + "\n";
		title += "Num Textures: " + std::to_string(stats.mNumTextures) + "\n";
		title += "Num Buffers: " + std::to_string(stats.mNumBuffers) + "\n";*/
		title += "Draw call count: " + std::to_string(mCmdBuffer->getDrawCount()) + "\n";
		title += "Vertex count: " + std::to_string(mCmdBuffer->getVertCount()) + "\n";
		title += "Triangle count: " + std::to_string(mCmdBuffer->getTriCount()) + "\n";
		title += "GameObject Transform count: " + std::to_string(positions.size()) + "\n";
		title += "GameObject Model count: " + std::to_string(models.size()) + "\n";

		ImGui_ImplSwizzle_NewFrame(mWindow);
		ImGui::NewFrame();

		ImGui::Begin("Stats");
		{
			OPTICK_EVENT("ImGui::Text");
			ImGui::Text("%s", title.c_str());
		}


		ImGui::End();

		ImGui::Begin("Other");
		{
			ImGui::Text("%s", "foo");
		}


		ImGui::End();

		ui.render();

		ImGui::EndFrame();

		//draw();


		U32 x, y;
		mWindow->getSize(x, y);
		cam.changeAspect((F32)x, (F32)y);

		struct tmp
		{
			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 proj;
			glm::vec4 eye;
		};

		tmp t = {};
		t.view = cam.getView();
		t.proj = cam.getProjection();
		t.eye = glm::vec4(cam.getPosition(), 1.0F);

		mSwapchain->setClearColor({ 0, 0, 0, 1 });

		mSwapchain->prepare();
		mCmdBuffer->begin();

		// upload textures

		ImGui_ImplSwizzle_UploadFontTexture(mCmdBuffer);
		
		ImGui_ImplSwizzle_BeginDraw(mCmdBuffer);
		
		ImGui::Render();
		ImGui_ImplSwizzle_RenderDrawData(ImGui::GetDrawData(), mCmdBuffer);
		ImGui_ImplSwizzle_EndDraw(mCmdBuffer);
		

		ImGui_ImplSwizzle_NewFrame(mWindow);

		mCmdBuffer->beginRenderPass(mSwapchain);
		mCmdBuffer->setViewport(x, y);

		for (size_t i = 0; i < positions.size(); i++)
		{
		
			auto& model = models[i];
		
			// prepare material/ shader bindings
		
			t.model = glm::translate(glm::mat4(1.f), glm::vec3(1.f));
			mCmdBuffer->setShaderConstant(model->shader, (U8*)&t, sizeof(t));
			mCmdBuffer->drawIndexed(model->mesh->mVertexBuffer, model->mesh->mIndexBuffer);
		}

		mCmdBuffer->bindShader(mFsq);
		mCmdBuffer->bindMaterial(mFsq, mFsqMat);
		mCmdBuffer->drawNoBind(3u, 0u);

		mCmdBuffer->endRenderPass();
		mCmdBuffer->end();

		mGfxContext->submit(&mCmdBuffer, 1, mSwapchain);
		mSwapchain->present();

	}

	void RenderWindow::drawUI()
	{
		//mSwapchain->prepare();
		//mCmdBuffer->begin();
		//
		//// upload textures
		//ImGui_ImplSwizzle_NewFrame(mWindow);
		////ui.render();
		//
		//ImGui::NewFrame();
		//ImGui::Begin("Blah");
		//{
		//	ImGui::Text("%s", "sometext");
		//}
		//
		//ImGui::End();
		//ImGui::EndFrame();
		//
		//ImGui_ImplSwizzle_UploadFontTexture(mCmdBuffer);
		//
		//ImGui_ImplSwizzle_BeginDraw(mCmdBuffer);
		//
		//ImGui::Render();
		//ImGui_ImplSwizzle_RenderDrawData(ImGui::GetDrawData(), mCmdBuffer);
		//ImGui_ImplSwizzle_EndDraw(mCmdBuffer);
		//
		//
		//mCmdBuffer->endRenderPass();
		//mCmdBuffer->end();
		//
		//mGfxContext->submit(&mCmdBuffer, 1, mSwapchain);
		//mSwapchain->present();
	}

	void RenderWindow::setFramerate(const unsigned& limit) const
	{
		limit;
	}

	void RenderWindow::moveCamera(const Core::Vector2f& vec)
	{
		vec;
		//auto view = (sf::View&)window->getView();
		//view.move(vec.x, vec.y);
		//window->setView(view);
	}

	void RenderWindow::addRenderable(const int& , const Core::String& , const Core::Vector2& , const float&, const Core::String& , const Enums::TileTypes& , bool )
	{
	}

	void RenderWindow::setTileMapTransparencyHitbox(int , Core::String , Core::Rect<float> , float )
	{
	}

	void RenderWindow::clearDrawList()
	{
	}
}

