#include "Window.hpp"

#include <Object/GameObject.hpp>
#include <Object/BaseComponent.hpp>
#include <Object/ObjectInstanceHandler.hpp>

#include "Render.hpp"
#include "mvp.hpp"

#include <Graphics/PlayerInteractionPrompt.hpp>
#include <File/GameConfig.hpp>
#include <File/Resource/ShaderLoader.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_swizzle.hpp>
#include <utils/StringUtils.hpp>

#include <swizzle/asset/TextureLoader.hpp>

#include <module/window/GraphicsProxy.hpp>


of::module::EngineResourceType of::module::interface::IEngineResource<Graphics::RenderWindow>::type = of::module::EngineResourceType::Graphics;
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
	RenderWindow::DynamicWindowListener& RenderWindow::getEventListener()
	{
		return listener;
	}

	TransparencyMasker& RenderWindow::getMasker()
	{
		return masker;
	}

	void RenderWindow::userSetup()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		// TODO: do some font combination magic & move to font handler?
		// Will we be using imgui for the entire ui as well or do our own.
		auto& io = ImGui::GetIO();
		ImFont* font = io.Fonts->AddFontDefault();
		font;
		ImFontConfig config;
		config.MergeMode = true;
		std::string s2 = of::common::SystemFonts + "msgothic.ttc";
		ImGui::GetIO().Fonts->AddFontFromFileTTF(s2.c_str(), 13.f, &config, 
			ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
		// endTodo
		ImGui_ImplSwizzle_Init(mGfxContext, mWindow);

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

		mFsq = of::engine::GetModule<File::Resource::Shader::Loader>().requestShader("fsq.shader", attribFsq);
		
		mFsqMat = mGfxContext->createMaterial(mFsq);
		ImGui_ImplSwizzle_SetMaterial(mFsqMat);

		auto& gameConfig = of::engine::GetModule<EngineModule::GameConfig>();
		mWindow->setSize(gameConfig.videoMode.first, gameConfig.videoMode.second);

		mSkybox.setSkyBox("dark");

		auto& proxy = of::engine::GetModule<of::module::window::Proxy>();
		proxy.setProxy(mGfxContext, mCmdBuffer, mUploadBuffer, mSwapchain);

	}

	SwBool RenderWindow::userUpdate(F32 )
	{
		//if (world.isLoading)
		//{
		//
		//}
		//else
		{
			draw();
		}
		fps->update();
		fps->print();
		return mWindow->isVisible();
	}

	void RenderWindow::userCleanup()
	{
		mWindow->removeEventListener(&listener);
	}

	void RenderWindow::postInitialize()
	{
		fps = ui.getUIContext<Graphics::UI::Stats>(Enums::UIContextNames::FPS);
		mWindow->addEventListener(&listener);
	}

	void RenderWindow::ProcessCulling()
	{
	}

	void RenderWindow::drawStats()
	{
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
				title += "; Allocs: " + std::to_string(memStat->mNumAllocations) + "p, " +
					std::to_string(memStat->mNumVirtualAllocations) + "v\n";
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
			else if (iter->getType() == sw::gfx::GfxStatsType::InstanceStats)
			{
				sw::gfx::InstanceStatistics* instStats = (sw::gfx::InstanceStatistics*)iter->getStatisticsData();
				title += "Instance\n";
				title += "  Alloc Count " + std::to_string(instStats->mAllocCount) + "\n";
				title += "  Internal Alloc Count " + std::to_string(instStats->mInternalAllocCount) + "\n";
			}
			else if (iter->getType() == sw::gfx::GfxStatsType::GfxPipelineStats)
			{
				sw::gfx::GfxPipelineStatistics* gfxStats = (sw::gfx::GfxPipelineStatistics*)iter->getStatisticsData();
				title += "Graphics Pipeline statistics\n";
				title += "  Input Assemby Vertices " + std::to_string(gfxStats->mInputAssemblyVertices) + "\n";
				title += "  Input Assemby Primitives " + std::to_string(gfxStats->mInputAssemblyPrimitives) + "\n";
				title += "  Vertex Shader Invocations " + std::to_string(gfxStats->mVertexShaderInvocations) + "\n";
				title += "  Clipping Invocations " + std::to_string(gfxStats->mClippingInvocations) + "\n";
				title += "  Clipping Primitives " + std::to_string(gfxStats->mClippingInvocations) + "\n";
				title += "  Fragment Shader Invocations " + std::to_string(gfxStats->mFragmentShaderInvocations) + "\n";
				title += "  Tesselation Control Shader Patches " +
					std::to_string(gfxStats->mTesselationControlShaderPatches) + "\n";
				title += "  Tesselation Evaluation Shader Invocations " +
					std::to_string(gfxStats->mTesselationEvaluationShaderInvocations) + "\n";
				title += "  Compute Shader Invocations " + std::to_string(gfxStats->mComputeShaderInvocations) + "\n";
			}

		} while (iter->next());


		title += "Draw call count: " + std::to_string(mCmdBuffer->getDrawCount()) + "\n";
		title += "Vertex count: " + std::to_string(mCmdBuffer->getVertCount()) + "\n";
		title += "Triangle count: " + std::to_string(mCmdBuffer->getTriCount()) + "\n";
		title += "GameObject Transform count: " + std::to_string(positions.size()) + "\n";
		title += "GameObject Model count: " + std::to_string(models.size()) + "\n";

		auto player = of::engine::GetModule<EngineModule::ObjectInstanceHandler>().getPlayer();
		auto pos = player->getComponent<Component::Transform>()->pos;
		title += "Player pos: " + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ", " + std::to_string(pos.z) + "\n";

		ImGui::Begin("Stats");
		{
			OPTICK_EVENT("ImGui::Text");
			ImGui::Text("%s", title.c_str());
		}

		ImGui::End();
	}

	RenderWindow::RenderWindow() :
		drawHitbox(of::engine::GetModule<Globals>().boolGlobals[Globals::GLOBAL_DRAW_HITBOX]),
		ui(of::engine::GetModule<Graphics::UI::UIHandler>()),
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
		
		ImGui_ImplSwizzle_NewFrame(mWindow);
		ImGui::NewFrame();
		
		drawStats();
		ui.render();
		
		ImGui::EndFrame();

		U32 x, y;
		mWindow->getSize(x, y);
		cam.changeAspect((F32)x, (F32)y);

		MVP t = {};
		t.model = glm::translate(glm::mat4(1.f), { cam.getPosition() });
		t.view = cam.getView();
		t.proj = cam.getProjection();
		t.eye = glm::vec4(cam.getPosition(), 1.0F);


		mSwapchain->prepare();
		auto transaction = mCmdBuffer->begin();


		ImGui_ImplSwizzle_UploadFontTexture(transaction);
		
		auto dTransaction = mCmdBuffer->beginRenderPass(ImGui_ImplSwizzle_GetFramebuffer(), std::move(transaction));
		
		ImGui::Render();
		ImGui_ImplSwizzle_RenderDrawData(ImGui::GetDrawData(), dTransaction);
		transaction = mCmdBuffer->endRenderPass(std::move(dTransaction));


		dTransaction = mCmdBuffer->beginRenderPass(mSwapchain, std::move(transaction));
		
		dTransaction->setViewport(x, y);
		

		mSkybox.render(dTransaction, t);

		for (auto kv : positions)
		{
		
			auto model = models[kv.first];
			//t.model = glm::scale(glm::mat4(1.f), glm::vec3(1.f));
			t.model = glm::translate(glm::mat4(1.f), kv.second->buffered);
			t.model = glm::rotate(t.model, 0.f, glm::vec3(1.f, 0.f, 0.f));
			t.model = glm::rotate(t.model, 0.f, glm::vec3(0.f, 1.f, 0.f));
			t.model = glm::rotate(t.model, kv.second->facingAngle, glm::vec3(0.f, 0.f, 1.f));
		
			kv.second->facingAngle += 1.f / 255.f;
			if (model)
			{
				dTransaction->bindShader(model->shader);
				dTransaction->bindMaterial(model->shader, model->material);
				dTransaction->setShaderConstant(model->shader, (U8*)&t, sizeof(t));
				dTransaction->drawIndexed(model->mMeshBuffer, model->mIndexBuffer);
			}
		}

		dTransaction->bindShader(mFsq);
		dTransaction->bindMaterial(mFsq, mFsqMat);
		dTransaction->drawNoBind(3u, 0u);

		transaction = mCmdBuffer->endRenderPass(std::move(dTransaction));
		mCmdBuffer->end(std::move(transaction));

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

	void RenderWindow::addRenderable(const int& , const of::common::String& , const glm::vec2& , const float&, const of::common::String& , const Enums::TileTypes& , bool )
	{
	}

	void RenderWindow::setTileMapTransparencyHitbox(int , of::common::String , Core::Rect<float> , float )
	{
	}

	void RenderWindow::clearDrawList()
	{
	}
}

