#include "Window.hpp"

#include <Object/GameObject.hpp>
#include <Object/BaseComponent.hpp>
#include <Object/ObjectInstanceHandler.hpp>

#include "Render.hpp"
#include "mvp.hpp"

#include <Physics/Colliders/EntityCollider.hpp>
#include <Physics/Colliders/VisionCollider.hpp>
#include <Graphics/PlayerInteractionPrompt.hpp>
#include <File/GameConfig.hpp>
#include <File/Resource/ShaderLoader.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_swizzle.hpp>
#include <utils/StringUtils.hpp>

#include <swizzle/asset/TextureLoader.hpp>

#include <Graphics/Editor/ObjectSelector.hpp>

Enums::EngineResourceType Interfaces::IEngineResource<Graphics::RenderWindow>::type = Enums::EngineResourceType::Graphics;
namespace Graphics
{
	void RenderWindow::Cull(std::vector<GameObject*>& )
	{
	}

	void RenderWindow::AddRenderable(GameObject* go)
	{
		models[go->id] = go->getComponent<Render>()->model;
		positions[go->id] =  go->getSharedComponent<Component::Transform>();
	}
	void RenderWindow::RemoveRenderable(GameObject* go)
	{
		models.erase(go->id);
		positions.erase(go->id);
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
		mUploadBuffer = mGfxContext->createCommandBuffer(1);

		cam.setPosition({ 0.0F, 0.0F, 5.5F });


		sw::gfx::ShaderAttributeList attribFsq = {};
		attribFsq.mDescriptors = {
			{sw::gfx::DescriptorType::TextureSampler, sw::gfx::Count(1u), {sw::gfx::StageType::fragmentStage}}
		};
		attribFsq.mPushConstantSize = 0u;
		attribFsq.mEnableBlending = true;

		mFsq = Engine::GetModule<File::Resource::Shader::Loader>().requestShader("fsq.shader", attribFsq);
		
		mFsqMat = mGfxContext->createMaterial(mFsq);
		ImGui_ImplSwizzle_SetMaterial(mFsqMat);

		mSkybox.setSkyBox("dark");
		ui.addUIContext(Enums::UIContextNames::ObjectSelector, std::make_unique<Graphics::Editor::ObjectSelector>());

	}

	SwBool RenderWindow::userUpdate(F32 )
	{
		return mWindow->isVisible();
	}

	void RenderWindow::userCleanup()
	{
		m_isClosing = true;
		while (isThreadStopped == false)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
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

	std::shared_ptr<swizzle::gfx::GfxContext> RenderWindow::getGfxContext()
	{
		return mGfxContext;
	}

	std::shared_ptr<swizzle::gfx::CommandBuffer> RenderWindow::getCommandBuffer()
	{
		return mCmdBuffer;
	}

	std::shared_ptr<swizzle::gfx::CommandBuffer> RenderWindow::getUploadBuffer()
	{
		return mUploadBuffer;
	}

	std::shared_ptr<swizzle::gfx::Swapchain> RenderWindow::getSwapchain()
	{
		return mSwapchain;
	}

	void RenderWindow::draw()
	{
		//mWindow->pollEvents();
		std::string title;
		title.reserve(1024);
		title += "Frames: " + std::to_string(mSwapchain->getFrameCounter()) + "\n";

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

		auto player = Engine::GetModule<EngineModule::ObjectInstanceHandler>().getPlayer();
		auto pos = player->getComponent<Component::Transform>()->pos;
		title += "Player pos: " + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ", " + std::to_string(pos.z) + "\n";

		ImGui_ImplSwizzle_NewFrame(mWindow);
		ImGui::NewFrame();
		
		ImGui::Begin("Stats");
		{
			OPTICK_EVENT("ImGui::Text");
			ImGui::Text("%s", title.c_str());
		}
		
		
		ImGui::End();
		
		ui.render();
		
		ImGui::EndFrame();

		//draw();

		//cam.lookAt(glm::vec3(-15.f, -15.f, 15.f), positions[0]->pos);
		U32 x, y;
		mWindow->getSize(x, y);
		cam.changeAspect((F32)x, (F32)y);

		MVP t = {};
		t.model = glm::translate(glm::mat4(1.f), { cam.getPosition() });
		t.view = cam.getView();
		t.proj = cam.getProjection();
		t.eye = glm::vec4(cam.getPosition(), 1.0F);

		//mSwapchain->setClearColor({ 0,0,0,1 });

		mSwapchain->prepare();
		mCmdBuffer->begin();

		// upload textures

		// TMP: fixme someday
		//mCmdBuffer->uploadTexture(mSkybox.mModel->texture);

		ImGui_ImplSwizzle_UploadFontTexture(mCmdBuffer);
		
		ImGui_ImplSwizzle_BeginDraw(mCmdBuffer);
		
		ImGui::Render();
		ImGui_ImplSwizzle_RenderDrawData(ImGui::GetDrawData(), mCmdBuffer);
		ImGui_ImplSwizzle_EndDraw(mCmdBuffer);
		
		
		ImGui_ImplSwizzle_NewFrame(mWindow);

		mCmdBuffer->beginRenderPass(mSwapchain);
		
		mCmdBuffer->setViewport(x, y);
		

		mSkybox.render(mCmdBuffer, t);

		for (auto kv : positions)
		{
		
			auto& model = models[kv.first];
			//t.model = glm::scale(glm::mat4(1.f), glm::vec3(1.f));
			t.model = glm::translate(glm::mat4(1.f), kv.second->buffered);
			t.model = glm::rotate(t.model, 0.f, glm::vec3(1.f, 0.f, 0.f));
			t.model = glm::rotate(t.model, 0.f, glm::vec3(0.f, 1.f, 0.f));
			t.model = glm::rotate(t.model, kv.second->facingAngle, glm::vec3(0.f, 0.f, 1.f));
		
			kv.second->facingAngle += 1.f / 255.f;
		
			mCmdBuffer->bindShader(model->shader);
			mCmdBuffer->bindMaterial(model->shader, model->material);
			mCmdBuffer->setShaderConstant(model->shader, (U8*)&t, sizeof(t));
			mCmdBuffer->drawIndexed(model->mesh.mVertexBuffer, model->mesh.mIndexBuffer);
		}

		mCmdBuffer->bindShader(mFsq);
		mCmdBuffer->bindMaterial(mFsq, mFsqMat);
		mCmdBuffer->drawNoBind(3u, 0u);

		mCmdBuffer->endRenderPass();
		mCmdBuffer->end();

		mGfxContext->submit(&mCmdBuffer, 1u, mSwapchain);
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

	void RenderWindow::moveCamera(const glm::vec2& vec)
	{
		vec;
		//auto view = (sf::View&)window->getView();
		//view.move(vec.x, vec.y);
		//window->setView(view);
	}

	void RenderWindow::addRenderable(const int& , const Core::String& , const glm::vec2& , const float&, const Core::String& , const Enums::TileTypes& , bool )
	{
	}

	void RenderWindow::setTileMapTransparencyHitbox(int , Core::String , Core::Rect<float> , float )
	{
	}

	void RenderWindow::clearDrawList()
	{
	}
}

