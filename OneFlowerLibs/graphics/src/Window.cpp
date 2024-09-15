#include <graphics/window/Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <graphics/view/mvp.hpp>

#include <module/resource/internalLoaders.hpp>

#include <module/resource/ShaderLoader.hpp>
#include <graphics/sky/skyBox.hpp>

#include <engine/settings.hpp>

#include <imgui/imgui.h>

#include <utils/StringUtils.hpp>

#include "logger/Logger.hpp"
#include <gfx/buffer.hpp>

namespace of::graphics::window
{
	void Application::setupImGui()
	{
		swizzle::gfx::FrameBufferCreateInfo fboInfo{};
		fboInfo.mDepthType = swizzle::gfx::FrameBufferDepthType::DepthNone;
		fboInfo.mSwapCount = 3u;
		fboInfo.mColorAttachFormats = { swizzle::gfx::FrameBufferAttachmentType::Default };
		mWindow->getSize(fboInfo.mWidth, fboInfo.mHeight);

		mImGuiFbo = mGfxDevice->createFramebuffer(fboInfo);

		mImGuiRenderTarget = ::common::CreateRef<ImGuiSwizzleRenderTarget>(mImGuiFbo);

		//FSQ - fullscreen quad
		sw::gfx::ShaderAttributeList attribFsq = {};
		attribFsq.mDescriptors = {
			{sw::gfx::DescriptorType::TextureSampler, sw::gfx::Count(1u), {sw::gfx::StageType::fragmentStage}}
		};
		attribFsq.mPushConstantSize = 0u;
		attribFsq.mEnableBlending = true;
		attribFsq.mPrimitiveType = swizzle::gfx::PrimitiveType::triangle;

		mFsq = of::module::shader::get().requestShader("fsq", "fsq.shader", attribFsq);

		mFsqMat = mGfxDevice->createMaterial(mFsq, swizzle::gfx::SamplerMode::SamplerModeClamp);

		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui::GetStyle().AntiAliasedFill = true;
		ImGui::GetStyle().AntiAliasedLines = true;

		// TODO: do some font combination magic & move to font handler?
		// Will we be using imgui for the entire ui as well or do our own.
		//auto& io = ImGui::GetIO();
		ImFontConfig config;
		config.OversampleH = 1;
		config.OversampleV = 1;
		config.PixelSnapH = true;
		config.GlyphOffset.y = 1;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//ImFont* font = io.Fonts->AddFontDefault(&config);
		//font;
		
		std::string s2 = of::common::SystemFonts + "arial.ttf";
		ImGui::GetIO().Fonts->AddFontFromFileTTF(s2.c_str(), 16.f, &config,
			ImGui::GetIO().Fonts->GetGlyphRangesDefault());
		// endTodo

		ImGui_ImplSwizzle_Init(mWindow, mGfxDevice,  mImGuiRenderTarget);
		mFsqMat->setDescriptorTextureResource(0u, mImGuiRenderTarget->getTexture());

	}

	void Application::drawStats()
    {
		std::string title;
		title.reserve(1024);
		title += "Frames: " + std::to_string(mSwapchain->getFrameCounter()) + "\n";

		title += std::string(mGfxDevice->getDeviceName()) + "\n";

		auto iter = mGfxDevice->getStatisticsIterator();

		do
		{
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

		ImGui::Begin("Stats");
		{
			ImGui::Text("%s", title.c_str());
		}

		ImGui::End();
    }

    void Application::draw(const float dt)
    {
		// TODO: move to userSetup.
		//mSwapchain->setClearColor(swizzle::gfx::ClearColor{ 0.f,0.f,0.f,0.f });

		view::MVP mvp{};

		// IMGUI
		ImGui_ImplSwizzle_NewFrame(dt);
		ImGui::NewFrame();
		
		drawStats();
		auto xx = std::unique_ptr<swizzle::gfx::DrawCommandTransaction>(nullptr);
		for (auto& ir : imGuiRenderables)
		{
			ir.second->updateFrame(dt);
			ir.second->render(xx, mvp);
		}
		
		ImGui::EndFrame();

		U32 x, y;
		mWindow->getSize(x, y);
		
		mvp.model = glm::translate(glm::mat4(1.f), { cam.getPosition() });
		mvp.view = cam.getView();
		mvp.proj = cam.getProjection();
		mvp.eye = glm::vec4(cam.getPosition(), 1.0F);

		mSwapchain->setClearColor(swizzle::gfx::ClearColor(0, 0, 0, 0));
		mSwapchain->prepare();
		auto transaction = mCmdBuffer->begin();

		// IMGUI
		ImGui_ImplSwizzle_UploadFontTexture(transaction);

		auto dTransaction = mImGuiRenderTarget->beginRenderPass(mCmdBuffer, std::move(transaction));

		ImGui::Render();
		ImGui_ImplSwizzle_DrawData(ImGui::GetDrawData(), dTransaction);
		transaction = mCmdBuffer->endRenderPass(std::move(dTransaction));


		dTransaction = mCmdBuffer->beginRenderPass(mSwapchain, std::move(transaction));

		dTransaction->setViewport(x, y);

		skyBox.render(dTransaction, mvp);

		for (auto& kv : renderables)
		{
			for (auto& renderable : kv.second)
			{
				renderable.second->updateFrame(dt);
				renderable.second->render(dTransaction, mvp);
			}
		}

		if (drawHitboxes)
		{
			for (auto& renderable : hitBoxRenderables)
			{
				renderable.second->updateFrame(dt);
				renderable.second->render(dTransaction, mvp);
			}
		}

		dTransaction->bindShader(mFsq);
		dTransaction->bindMaterial(mFsq, mFsqMat);
		dTransaction->drawNoBind(3u, 0u);

		transaction = mCmdBuffer->endRenderPass(std::move(dTransaction));
		mCmdBuffer->end(std::move(transaction));

		mGfxDevice->submit(&mCmdBuffer, 1u, mSwapchain);
		mSwapchain->present();

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
    }

	Application::Application() : cam(glm::radians(45.f), 1920, 1080), drawHitboxes(of::settings::get().renderHitboxes())
	{
		cam.setPosition({ 0.f, 0.f, 5.f });
	}

	void Application::setup()
    {
	}

	void Application::setSkybox(const of::common::String& skyboxFolderName)
	{
		skyBox.setSkyBox(mGfxDevice, skyboxFolderName);
	}

    void Application::addRenderable(const RenderLayer renderLayer, const of::common::uuid& id, std::shared_ptr<Renderable> renderable)
    {
		if (renderLayer == RenderLayer::SKYBOX)
		{
			of::logger::get().Warning("Adding skybox via renderable is no longer supported");
		}
		else if (renderLayer == RenderLayer::IMGUI)
			imGuiRenderables[id] = renderable;
		else if (renderLayer == RenderLayer::HITBOXES)
			hitBoxRenderables[id] = renderable;
		else
		{
			renderables[renderLayer][id] = renderable;
		}
    }

	void Application::updateRenderable(const RenderLayer renderLayer, const of::common::uuid& id, std::shared_ptr<Renderable> renderable)
	{
		renderLayer, id, renderable;
	}

    void of::graphics::window::Application::removeRenderable(const of::common::uuid& id)
    {
        for (auto& it : renderables)
        {
            it.second.erase(id);
        }
    }

	view::Camera* Application::getCamera()
	{
		return &cam;
	}

	U32 Application::getWindowHeight()
	{
		U32 x, y;
		mWindow->getSize(x, y);
		return y;
	}

	U32 Application::getWindowWidth()
	{
		U32 x, y;
		mWindow->getSize(x, y);
		return x;
	}

    void of::graphics::window::Application::userSetup()
    {
		auto resolution = of::settings::get().getScreenResolution();

		mWindow->setSize(resolution.width, resolution.height);
		mWindow->setBorderless(of::settings::get().isBorderless());
		mWindow->setFullscreen(of::settings::get().isFullscreen());

        mSwapchain->setVsync(sw::gfx::VSyncTypes::vSyncOn);
        mCmdBuffer = mGfxDevice->createCommandBuffer(3);
        mUploadBuffer = mGfxDevice->createCommandBuffer(1);

		mGfxDevice->enablePipelineStatistics(true);

		gfx::init(mGfxDevice);
		module::mesh::init(mGfxDevice);
		module::shader::init(mGfxDevice, mSwapchain);
		module::texture::init(mGfxDevice, mCmdBuffer);

		setup();
		setupImGui();
    }

    SwBool of::graphics::window::Application::userUpdate(F32 dt)
    {
		if(camController)
			camController->update(dt);
		draw(dt);
		return mWindow->isVisible();
    }

    void of::graphics::window::Application::userCleanup()
    {
		workerThread.join();
		module::mesh::shutdown();
		module::shader::shutdown();
		module::texture::shutdown();

    }

	std::shared_ptr<of::graphics::view::CameraController> of::graphics::window::Application::setCameraController(std::shared_ptr<of::graphics::view::CameraController> controller)
	{
		auto& prev = camController;
		camController = controller;
		return prev;
	}
	
	glm::vec3 Application::getCameraPos() const
	{
		return cam.getPosition();
	}

	glm::vec3 Application::getCursorRay()
	{
		S32 x = 0, y = 0;
		mWindow->getCursorPos(x, y);
		if (x < 0)
			x = 0;
		if (y < 0)
			y = 0;
		return cam.projectRayFromCursor(float(x), float(y));
	}

	void Application::SetWindowSource(std::weak_ptr<Application> window)
	{
		sWindow = window;
	}
	std::weak_ptr<Application> Application::GetWindowSource()
	{
		return sWindow;
	}
}
