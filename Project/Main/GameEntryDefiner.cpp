#include "GameEntry.hpp"

#include <engine/runMode.hpp>

#include <thread>

#include <Module\BuildMode.hpp>

#include<File/GameConfig.hpp>

#include <Graphics/UI/Stats.hpp>
#include <Graphics/UI/BuildInfo.hpp>

#include <Graphics/UI/LoadingScreen.hpp>

#include <Graphics/Editor/EditorWindow.hpp>
#include <module/window/WindowProxy.hpp>
#include <Graphics/sky/skyBox.hpp>

#include <chrono>
#include <thread>
#include <iostream>

#include <graphics/ui/frame.hpp>
#include <module/window/GraphicsProxy.hpp>
#include <module/resource/TextureLoader.hpp>
#include <module/resource/ShaderLoader.hpp>
#include <module/window/GraphicsProxy.hpp>

#include <imgui/imgui_impl_swizzle.hpp>
#include <imgui/of_imgui_extensions.hpp>


#include <object/component/Render.hpp>

#include <ImGuizmo.h>

class WorldGrid : public of::graphics::ParentedRenderable
{

	of::graphics::view::Camera* c;
	common::Resource<swizzle::gfx::Buffer> buf_x;
	common::Resource<swizzle::gfx::Buffer> buf_y;
	common::Resource<swizzle::gfx::Buffer> buf_z;
	common::Resource<swizzle::gfx::Buffer> buf;
	common::Resource<swizzle::gfx::Material> mat;
	common::Resource<swizzle::gfx::Shader> shader;

	glm::vec3 x_line[2] = { {-1000.f, 0.f, 0.f}, {1000.f, 0.f, 0.f} };
	glm::vec3 y_line[2] = { {0.f, -1000.f, 0.f}, {0.f, 1000.f, 0.f} };
	glm::vec3 z_line[2] = { {0.f, 0.f, -1000.f}, {0.f, 0.f, 1000.f} };

	std::vector<glm::vec3> points;

	glm::vec4 color_red = { 1.f, 0.f, 0.f, 0.f };
	glm::vec4 color_green = { 0.f, 1.f, 0.f, 0.f };
	glm::vec4 color_blue = { 0.f, 0.f, 1.f, 0.f };
	glm::vec4 color_gray = { .25f, .25f, .25f, 0.f };

	void loadShader()
	{
		swizzle::gfx::ShaderAttributeList attribs = {};
		attribs.mBufferInput = {
			{ swizzle::gfx::ShaderBufferInputRate::InputRate_Vertex, sizeof(float) * (3U) }
		};

		attribs.mAttributes = {
			{ 0U, swizzle::gfx::ShaderAttributeDataType::vec3f, 0U},
		};
		attribs.mDescriptors = {};
		attribs.mEnableDepthTest = false;
		attribs.mEnableBlending = false;
		attribs.mPushConstantSize = sizeof(glm::mat4) * 4u;
		attribs.mPrimitiveType = swizzle::gfx::PrimitiveType::line;

		shader = of::engine::GetModule<of::module::shader::Loader>().requestShader("grid.shader", attribs);
	}

public:

	WorldGrid() : c(m_parent->getCamera())
	{
		for (float f = -20.f; f < 20.f; f+= 1.f)
		{
			points.push_back({f, 0.f, -20.f});
			points.push_back({f, 0.f, 20.f});
			// temporary, need lineStrip to remove
			points.push_back({f, 0.f, -20.f});
		}
		for (float f = -20.f; f < 20.f; f += 1.f)
		{
			points.push_back({ -20.f, 0.f, f });
			points.push_back({ 20.f, 0.f, f });
			// temporary, need lineStrip to remove
			points.push_back({ -20.f, 0.f, f });
		}

		auto& wnd = of::engine::GetModule<of::module::window::Proxy>();
		auto gfx = wnd.getGfxContext();

		loadShader();
		mat = gfx->createMaterial(shader, swizzle::gfx::SamplerMode::SamplerModeClamp);

		buf = gfx->createBuffer(swizzle::gfx::BufferType::Vertex);
		buf->setBufferData(points.data(), points.size() * sizeof(glm::vec3), sizeof(float) * 3u);

		buf_x = gfx->createBuffer(swizzle::gfx::BufferType::Vertex);
		buf_x->setBufferData(x_line, sizeof(x_line), sizeof(float) * 3u);

		buf_y = gfx->createBuffer(swizzle::gfx::BufferType::Vertex);
		buf_y->setBufferData(y_line, sizeof(y_line), sizeof(float) * 3u);

		buf_z = gfx->createBuffer(swizzle::gfx::BufferType::Vertex);
		buf_z->setBufferData(z_line, sizeof(y_line), sizeof(float) * 3u);

	}

	virtual void updateFrame(const float& )
	{
	}

	virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, of::graphics::view::MVP& mvp)
	{

		mvp.model = glm::translate(glm::mat4(1.f), { 0.f,0.f,0.f });

		transaction->bindShader(shader);
		transaction->bindMaterial(shader, mat);
		transaction->setShaderConstant(shader, (U8*)&mvp, sizeof(mvp));
		transaction->setShaderConstant(shader, (U8*)&color_gray, sizeof(glm::vec4), sizeof(mvp));
		transaction->draw(buf);

		mvp.model = glm::translate(glm::mat4(1.f), { c->getPosition().x,0.f,0.f });
		transaction->bindShader(shader);
		transaction->bindMaterial(shader, mat);
		transaction->setShaderConstant(shader, (U8*)&mvp, sizeof(mvp));
		transaction->setShaderConstant(shader, (U8*)&color_red, sizeof(glm::vec4), sizeof(mvp));
		transaction->draw(buf_x);

		mvp.model = glm::translate(glm::mat4(1.f), { 0.f, c->getPosition().y,0.f });
		transaction->bindShader(shader);
		transaction->bindMaterial(shader, mat);
		transaction->setShaderConstant(shader, (U8*)&mvp, sizeof(mvp));
		transaction->setShaderConstant(shader, (U8*)&color_green, sizeof(glm::vec4), sizeof(mvp));
		transaction->draw(buf_y);

		mvp.model = glm::translate(glm::mat4(1.f), { 0.f,0.f,c->getPosition().z });
		transaction->bindShader(shader);
		transaction->bindMaterial(shader, mat);
		transaction->setShaderConstant(shader, (U8*)&mvp, sizeof(mvp));
		transaction->setShaderConstant(shader, (U8*)&color_blue, sizeof(glm::vec4), sizeof(mvp));
		transaction->draw(buf_z);
	};
};

class Gizmo : public of::graphics::ParentedRenderable
{
	of::graphics::view::Camera* c;
	glm::mat4 mat = glm::mat4(0.f);
	glm::vec3 pos = glm::vec3(0.f);
	glm::vec3 rot = glm::vec3(0.f);
	glm::vec3 scale = glm::vec3(1.f);

public:

	Gizmo() : c(m_parent->getCamera())
	{
		ImGuizmo::RecomposeMatrixFromComponents((float*)&pos, (float*)&rot, (float*)&scale, (float*)&mat);
	}

	virtual void updateFrame(const float&)
	{
	}

	virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& , of::graphics::view::MVP& )
	{
		ImGuizmo::BeginFrame();
		ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());
		auto io = ImGui::GetIO();
		ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
		ImGuizmo::Enable(true);

		ImGuizmo::DecomposeMatrixToComponents((float*)&mat, (float*)&pos, (float*)&rot, (float*)&scale);
		ImGuizmo::RecomposeMatrixFromComponents((float*)&pos, (float*)&rot, (float*)&scale, (float*) &mat);

		ImGuizmo::Manipulate((float*)&c->getView(), (float*)&c->getProjection(), ImGuizmo::UNIVERSAL, ImGuizmo::MODE::LOCAL, (float*)&mat);
	};

	glm::vec3* getPos()
	{
		return &pos;
	}
};

class EditorController : public of::graphics::view::CameraController
{
	std::mutex mtx;
public:
	EditorController()
		: CameraController()
		, mTarget(0.0F)
		, mDirection(0.0F)
		, mAngleH(0.0F)
		, mAngleV(0.0F)
		, mFollow(nullptr)
	{
		mCamera->lookAt(mCamera->getPosition(), mTarget);
		rotate(0.f, -34.f);
	}
	~EditorController()
	{
	};

private:

	void pan(const glm::vec3& pos)
	{
		auto delta = pos - mTarget;

		delta = delta * 0.1f;

		glm::vec3 motion(delta.x, delta.y, delta.z);
		mTarget += motion;
	}

	void zoom(const float& zoomDelta)
	{
		if (zoomDelta == 0.f)
			return;
		mZoomConstant -= zoomDelta;
		if (mZoomConstant < 0.2f)
			mZoomConstant = 0.2f;
	}

	void mouseSlideXY(float dx, float dy)
	{
		glm::vec3 xySlide = mDirection;
		xySlide.y = 0;
		glm::vec3 left = cross(mDirection, glm::vec3(0.0F, 1.0F, 0.0F));
		left = glm::normalize(left);
		mTarget += left * -dx;
		mTarget += xySlide * dy;
	}

	void mouseSlide(float dx, float dy)
	{
		glm::vec3 right = glm::normalize(cross(glm::vec3(0.0F, 1.0F, 0.0F), mDirection));
		glm::vec3 up = cross(mDirection, right);
		mTarget += right * dx;
		mTarget += up * -dy;
	}

	void rotate(float dx, float dy)
	{
		mAngleH -= dx;
		mAngleV -= dy;
		if (mAngleV > 89)
		{
			mAngleV = 89;
		}
		if (mAngleV < -89)
		{
			mAngleV = -89;
		}

		glm::vec3 dir = { -1.0F, 0.0F, 0.0F };

		F32 rotateRad = glm::radians(mAngleV);

		glm::mat3 rotV = glm::mat3(glm::cos(rotateRad), -glm::sin(rotateRad), 0.0f,
			glm::sin(rotateRad), glm::cos(rotateRad), 0.0f,
			0.0f, 0.0f, 1.0f);

		dir = rotV * dir;
		dir = glm::normalize(dir);

		rotateRad = glm::radians(mAngleH);
		glm::mat3 rotH = glm::mat3(glm::cos(rotateRad), 0.0f, -glm::sin(rotateRad),
			0.0f, 1.0f, 0.0f,
			glm::sin(rotateRad), 0.0f, glm::cos(rotateRad));

		dir = rotH * dir;
		mDirection = glm::normalize(dir);
	}

	float mZoomConstant = 10.f;
	glm::vec3 mZoom;
	glm::vec3 mTarget;
	glm::vec3 mDirection;

	F32 mAngleH;
	F32 mAngleV;

	std::shared_ptr<of::object::component::Transform> mFollow;

public:

	void follow(std::shared_ptr<of::object::component::Transform> transform, const glm::vec3& = {})
	{
		mFollow = transform;
	}

	virtual void update(const float&) override
	{
		float dx = 0.f, dy = 0.f;
		swizzle::input::GetMouseDelta(dx, dy);
		ImGuiContext& g = *ImGui::GetCurrentContext();

		if (mFollow != nullptr)
		{
			pan(mFollow->pos);
			if (swizzle::input::IsMouseButtonPressed(swizzle::input::Mouse::MiddleClick) && g.HoveredWindow == nullptr)
			{
				rotate(dx * 0.1f, dy * 0.1f);
			}
		}
		else
		{
			if (g.HoveredWindow == nullptr)
			{

				if (swizzle::input::IsKeyPressed(swizzle::input::Keys::KeyLShift) && swizzle::input::IsMouseButtonPressed(swizzle::input::Mouse::MiddleClick))
				{
					rotate(dx * 0.1f, dy * 0.1f);
				}
				else if (swizzle::input::IsKeyPressed(swizzle::input::Keys::KeyLCtrl) && swizzle::input::IsMouseButtonPressed(swizzle::input::Mouse::MiddleClick))
				{
					mouseSlideXY(dx * 0.05f, dy * 0.05f);
				}
				else if (swizzle::input::IsMouseButtonPressed(swizzle::input::Mouse::MiddleClick))
				{
					mouseSlide(dx * 0.05f, dy * 0.05f);
				}
			}
		}

		swizzle::input::GetMouseScrollDelta(dx, dy);
		if (g.HoveredWindow == nullptr)
			zoom(dy * 1.5f);

		mZoom = { mZoomConstant, mZoomConstant, mZoomConstant};

		auto pos = mTarget + (mDirection * mZoom);


		mCamera->setPosition(pos);
		mCamera->lookAt(pos, mTarget);
	}
};

class CustomTrackerPoint : public of::graphics::ParentedRenderable
{
	std::shared_ptr<of::object::component::Transform> transform = std::make_shared<of::object::component::Transform>();
	std::shared_ptr<EditorController>& controller;
	bool mFollowing = false;

public:

	CustomTrackerPoint(std::shared_ptr<EditorController>& controller): controller(controller) {}

	virtual void updateFrame(const float&)
	{
	}

	virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>&, of::graphics::view::MVP&)
	{
		ImGui::Begin("TrackerPoint");
		ImGui::SliderFloat3("Pos", (float*)&transform->pos, -10.f, 10.f);
		if (mFollowing)
		{
			ImGui::Text("Following object == true");
		}
		else
		{
			ImGui::Text("Following object == false");

		}
		if (ImGui::Button("Set"))
		{
			controller->follow(transform);
			mFollowing = true;
		}
		if (ImGui::Button("Unset"))
		{
			controller->follow(nullptr);
			mFollowing = false;
		}
		ImGui::End();
	};
};

GameEntry::GameEntry() : 
	gfx(std::make_shared<of::graphics::window::Application>()),
	time(of::engine::GetModule<of::module::Time>()),
	input(of::engine::GetModule<Input::InputHandler>()),
	world(of::engine::GetModule<of::module::SceneManager>()), m_exit(false)
{
	of::engine::GetModule<of::module::window::WindowProxy>().setHandle(gfx);
	ups = std::make_shared<Graphics::UI::Stats>("UPS", 200.f, 70.f, Graphics::UI::Rel::Right);
	loadingScreenInfo = std::make_shared<Graphics::UI::LoadingScreenInfo>();
}


int GameEntry::Run()
{
	auto width = of::engine::GetModule<EngineModule::GameConfig>().videoMode.first;

	gfx->initialize();
	world.initialize();

	//gfx.setFramerate(of::engine::GetModule<EngineModule::GameConfig>().getFramerateLimit());

	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::UI::Stats>("FPS", 400.f, 70.f, Graphics::UI::Rel::Right));
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), ups);
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::UI::BuildInfo>(Engine::GetBuildMode().getDetailedBuildInfo(), 400.f, 10.f, Graphics::UI::Rel::Right));
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::UI::Stats>("FPS", float(width - (200 * 2)), 70.f));

	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::UI::LoadingScreen>());
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), loadingScreenInfo);

	auto cameraController = std::make_shared<EditorController>();
	gfx->setCameraController(cameraController);

	if (of::engine::getRunMode() == of::engine::RunMode::EDITOR)
	{
		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::Editor::MainEditorWindow>());
		gfx->addRenderable(of::graphics::window::RenderLayer::EDITOR, of::common::uuid(), std::make_shared<WorldGrid>());
		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Gizmo>());
		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<CustomTrackerPoint>(cameraController));

	}

	std::thread physics_thread(&GameEntry::physicsUpdate, this);

	gfx->loop();
	m_exit = true;
	physics_thread.join();

	//gfx.clearDrawList();
	return EXIT_SUCCESS;
}

void GameEntry::physicsUpdate()
{
	if (of::engine::getRunMode() != of::engine::RunMode::EDITOR)
	{
//		world.createMainMenu();
	}
	time.physicsElapsed = time.physicsClock.secondsAsFloat(true);
	const float update_time = time.update_ms;
	while (!m_exit)
	{
		while (world.isLoading)
		{
			time.physicsElapsed = time.update_ms;
			world.Update();
			loadingScreenInfo->update();
		}
		while (time.physicsElapsed >= time.update_ms)
		{
			time.physicsElapsed -= time.update_ms;
			{
				input.update(update_time);
				world.Simulate(update_time);
				time.Simulate(update_time);
				ups->update();
				ups->print();
			}
		}
		time.physicsElapsed += time.physicsClock.secondsAsFloat(true);
	}
	std::cout << "Physics Exited!!" << std::endl;

}
