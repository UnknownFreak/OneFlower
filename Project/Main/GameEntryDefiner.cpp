#define IMGUI_DEFINE_MATH_OPERATORS

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

#include <imgui/imgui_stdlib.hpp>
#include <imgui/of_imgui_extensions.hpp>
#include <imgui/fileSelector.hpp>

#include <graphics/Editor/EditorBasicToolTip.hpp>

#include <object/component/Render.hpp>

#include <ImGuizmo.h>
#include <stb/stb_image.h>
#include <algorithm>

#include <physics/physics.hpp>

#include <glm/glm.hpp>
#pragma warning(push, 0)
#include <glm/gtc/quaternion.hpp>
#pragma warning(pop)

#include <swizzle/asset2/Assets.hpp>
#include <module/resource/MeshLoader.hpp>
#include <module/resource/Model.hpp>

#include<Input/PlayerController.hpp>

bool paused = false;

class WorldGrid : public of::graphics::ParentedRenderable
{

	of::graphics::view::Camera* c;
	common::Resource<swizzle::gfx::GfxBuffer> buf_x;
	common::Resource<swizzle::gfx::GfxBuffer> buf_y;
	common::Resource<swizzle::gfx::GfxBuffer> buf_z;
	common::Resource<swizzle::gfx::GfxBuffer> buf;
	common::Resource<swizzle::gfx::Material> mat;
	common::Resource<swizzle::gfx::Shader> shader;

	glm::vec3 x_line[2] = { {-100.f, 0.f, 0.f}, {100.f, 0.f, 0.f} };
	glm::vec3 y_line[2] = { {0.f, -100.f, 0.f}, {0.f, 100.f, 0.f} };
	glm::vec3 z_line[2] = { {0.f, 0.f, -100.f}, {0.f, 0.f, 100.f} };

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
		attribs.mEnableDepthTest = true;
		attribs.mEnableDepthWrite = true;
		attribs.mEnableBlending = true;
		attribs.mPushConstantSize = sizeof(glm::mat4) * 4u;
		attribs.mPrimitiveType = swizzle::gfx::PrimitiveType::line;

		shader = of::engine::GetModule<of::module::shader::Loader>().requestShader("grid", "grid.shader", attribs);
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
		auto gfx = wnd.getGfxDevice();

		loadShader();
		mat = gfx->createMaterial(shader, swizzle::gfx::SamplerMode::SamplerModeClamp);

		buf = gfx->createBuffer(swizzle::gfx::GfxBufferType::Vertex, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
		buf->setBufferData(points.data(), points.size() * sizeof(glm::vec3), sizeof(float) * 3u);

		buf_x = gfx->createBuffer(swizzle::gfx::GfxBufferType::Vertex, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
		buf_x->setBufferData(x_line, sizeof(x_line), sizeof(float) * 3u);

		buf_y = gfx->createBuffer(swizzle::gfx::GfxBufferType::Vertex, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
		buf_y->setBufferData(y_line, sizeof(y_line), sizeof(float) * 3u);

		buf_z = gfx->createBuffer(swizzle::gfx::GfxBufferType::Vertex, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
		buf_z->setBufferData(z_line, sizeof(z_line), sizeof(float) * 3u);

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

		transaction->bindShader(shader);
		transaction->bindMaterial(shader, mat);
		transaction->setShaderConstant(shader, (U8*)&mvp, sizeof(mvp));
		transaction->setShaderConstant(shader, (U8*)&color_red, sizeof(glm::vec4), sizeof(mvp));
		transaction->draw(buf_x);

		transaction->bindShader(shader);
		transaction->bindMaterial(shader, mat);
		transaction->setShaderConstant(shader, (U8*)&mvp, sizeof(mvp));
		transaction->setShaderConstant(shader, (U8*)&color_green, sizeof(glm::vec4), sizeof(mvp));
		transaction->draw(buf_y);

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

	glm::quat getRotation()
	{
		return glm::quat(rot);
	}

	void setRotation(glm::quat& quat)
	{
		rot = glm::eulerAngles(quat);
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

class CourierStats : public of::graphics::ParentedRenderable, public of::utils::lifetime::LifetimeWarranty
{
	std::shared_ptr<of::messaging::ChannelTopic> m_channel;
	of::common::String string;
	int val = 0;
	bool m_add = false;
	of::common::uuid instanceId;
public:

	CourierStats() : m_channel(of::engine::GetModule<of::messaging::Courier>().getChannel(of::messaging::Topic::Update)) 
	{
	}

	virtual void updateFrame(const float&)
	{
	}
	void updateCount()
	{
		if (m_add)
		{
			m_add = false;
			for (int i = 0; i < val; i++)
			{
				of::engine::GetModule<of::module::ObjectInstanceHandler>().addObject();
			}
		}
		string = std::to_string(m_channel->getSubscribersCount());
	}

	virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>&, of::graphics::view::MVP&)
	{
		ImGui::Begin("CourierStats");
		ImGui::Text(string.c_str());
		ImGui::SliderInt("Object count", &val, 0, 100000);
		if(ImGui::Button("Add object"))
		{
			m_add = true;
		}
		ImGui::End();
	};
};


class PxControllerRenderable : public of::graphics::ParentedRenderable
{
	physx::PxController* actor;
	glm::vec3 pos;

	common::Resource<swizzle::gfx::GfxBuffer> buf;
	common::Resource<swizzle::gfx::GfxBuffer> index;
	common::Resource<swizzle::gfx::Material> mat;
	common::Resource<swizzle::gfx::Shader> shader;
	common::Resource<swizzle::gfx::Texture> texture;
	glm::vec4 playerControllerColor = { 0.3f, 0.3f, 1.f, 0.f };

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
		attribs.mEnableDepthTest = true;
		attribs.mEnableDepthWrite = true;
		attribs.mEnableBlending = true;
		attribs.mPushConstantSize = sizeof(glm::mat4) * 4u;
		attribs.mPrimitiveType = swizzle::gfx::PrimitiveType::line;

		shader = of::engine::GetModule<of::module::shader::Loader>().requestShader("pxcontroller", "grid.shader", attribs);
	}

	void connectToPoint(std::vector<glm::ivec3>& tris, int point, const int pointCount, const int refStart)
	{
		for (int i = 0; i < pointCount; i++)
		{

			int a = i + refStart;
			int b = i + refStart + 1;
			if (i == pointCount-1)
			{
				b -= pointCount;
			}
			tris.push_back(glm::ivec3(point, a,b));
		}
	}

	void connectToCircle(std::vector<glm::ivec3>& tris, const int pointCount, const int lowerStart, const int upperStart)
	{
		for (int i = 0; i < pointCount; i++)
		{
			int c = i + lowerStart;
			int a = i + upperStart;
			int b = i + upperStart + 1;
			if (i == pointCount - 1)
			{
				b -= pointCount;
			}
			tris.push_back(glm::ivec3(c, a, b));
		}
	}

public:

	PxControllerRenderable(physx::PxController* controller) : actor(controller)
	{
		std::vector<glm::vec3> points;
		std::vector<glm::ivec3> tris;
		auto capsule = (physx::PxCapsuleController*)actor;
		auto height = actor->getPosition().y - actor->getFootPosition().y;
		auto topHeight = capsule->getHeight() *0.8f * 0.5f;
		topHeight += capsule->getRadius() * 0.8f;

		auto radii = capsule->getRadius() * 0.8f;
		//height += capsule->getRadius() * 0.8f;
		{

			points.push_back(glm::vec3(0, -height, 0));
			
			for (int i = 0; i < 16; i++)
			{
				auto angle = (std::_Pi / 8.f) * i;
				auto x = radii * 0.3 * cos(angle);
				auto y = radii * 0.3 * sin(angle);
				points.push_back(glm::vec3(x, -(height * 0.98f), y));
			}
			connectToPoint(tris, 0, 16, 1);
			
			for (int i = 0; i < 16; i++)
			{
				auto angle = (std::_Pi / 8.f) * i;
				auto x = radii * 0.7 * cos(angle);
				auto y = radii * 0.7 * sin(angle);
				points.push_back(glm::vec3(x, -(height * 0.9f), y));
			}
			connectToCircle(tris, 16, 1, 17);
			
			for (int i = 0; i < 16; i++)
			{
				auto angle = (std::_Pi / 8.f) * i;
				auto x = radii * cos(angle);
				auto y = radii * sin(angle);
				points.push_back(glm::vec3(x, -(height * 0.8f), y));
			}
			connectToCircle(tris, 16, 17, 33);

			for (int i = 0; i < 16; i++)
			{
				auto angle = (std::_Pi / 8.f) * i;
				auto x = radii * cos(angle);
				auto y = radii * sin(angle);
				points.push_back(glm::vec3(x, (topHeight * 0.8f), y));
			}
			connectToCircle(tris, 16, 33, 49);

			for (int i = 0; i < 16; i++)
			{
				auto angle = (std::_Pi / 8.f) * i;
				auto x = radii * 0.7 * cos(angle);
				auto y = radii * 0.7 * sin(angle);
				points.push_back(glm::vec3(x, (topHeight * .9f), y));
			}
			connectToCircle(tris, 16, 49, 65);

			for (int i = 0; i < 16; i++)
			{
				auto angle = (std::_Pi / 8.f) * i;
				auto x = radii * 0.3 * cos(angle);
				auto y = radii * 0.3 * sin(angle);
				points.push_back(glm::vec3(x, (topHeight * .98f), y));
			}
			connectToCircle(tris, 16, 65, 81);

			points.push_back(glm::vec3(0, topHeight, 0));
			connectToPoint(tris, 97, 16, 81);
		}

		auto& wnd = of::engine::GetModule<of::module::window::Proxy>();
		auto gfx = wnd.getGfxDevice();
		loadShader();
		mat = gfx->createMaterial(shader, swizzle::gfx::SamplerMode::SamplerModeClamp);
		
		buf = gfx->createBuffer(swizzle::gfx::GfxBufferType::Vertex, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
		buf->setBufferData(points.data(), points.size() * sizeof(glm::vec3), sizeof(glm::vec3));

		index = gfx->createBuffer(swizzle::gfx::GfxBufferType::Index, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
		index->setBufferData(tris.data(), tris.size() * sizeof(glm::ivec3), sizeof(glm::ivec3));
		
	}

	virtual void updateFrame(const float&)
	{
		auto vec = actor->getPosition();
		pos.x = (float)vec.x;
		pos.y = (float)vec.y;
		pos.z = (float)vec.z;
	}

	virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, of::graphics::view::MVP& mvp)
	{
		mvp.model = glm::translate(glm::mat4(1.f), pos);

		transaction->bindShader(shader);
		transaction->bindMaterial(shader, mat);
		transaction->setShaderConstant(shader, (U8*)&mvp, sizeof(mvp));
		transaction->setShaderConstant(shader, (U8*)&playerControllerColor, sizeof(glm::vec4), sizeof(mvp));
		transaction->drawIndexed(buf, index);
	};
};

static size_t mId = 0x100000000;

template<class T>
class PxMeshedActorRenderable : public of::graphics::ParentedRenderable, public of::utils::lifetime::LifetimeWarranty
{
	T* mActor;
	of::resource::Model model;
	
	glm::vec3 pos;
	glm::vec3 scale;
	glm::quat rot;

	glm::vec4 renderingColor = { 0.3f, 0.3f, 1.f, 0.f };

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
		attribs.mEnableDepthTest = true;
		attribs.mEnableDepthWrite = true;
		attribs.mEnableBlending = true;
		attribs.mPushConstantSize = sizeof(glm::mat4) * 4u;
		attribs.mPrimitiveType = swizzle::gfx::PrimitiveType::line;

		model.shader = of::engine::GetModule<of::module::shader::Loader>().requestShader("pxactor shader", "grid.shader", attribs);
	}

public:

	PxMeshedActorRenderable(T* iactor, of::resource::Model mesh, float scale = 1.f, glm::vec4 renderingColor = {0.3f, 0.3f, 1.f, 0.f}) : mActor(iactor), model(mesh), scale(scale), renderingColor(renderingColor)
	{
		auto& wnd = of::engine::GetModule<of::module::window::Proxy>();
		auto gfx = wnd.getGfxDevice();
		loadShader();

		model.material = gfx->createMaterial(model.shader, swizzle::gfx::SamplerMode::SamplerModeClamp);

		auto channel = of::engine::GetModule<of::messaging::Courier>().getChannel(of::messaging::Topic::Update);
		channel->addSubscriber(of::messaging::Subscriber(mId++ , warrantyFromThis(), [&](const of::messaging::Message&)
			{
				auto vec = mActor->getGlobalPose().p;
				auto r = mActor->getGlobalPose().q;
				pos.x = (float)vec.x;
				pos.y = (float)vec.y;
				pos.z = (float)vec.z;
				rot.w = r.w;
				rot.x = r.x;
				rot.y = r.y;
				rot.z = r.z;
			}
		));

	}

	virtual void updateFrame(const float&)
	{
	}

	virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, of::graphics::view::MVP& mvp)
	{
		mvp.model = glm::translate(glm::mat4(1.f), pos);
		mvp.model = glm::scale(mvp.model, scale);
		mvp.model *= glm::mat4_cast(rot);

		model.render(transaction, mvp, [&]() {
			transaction->setShaderConstant(model.shader, (U8*)&renderingColor, sizeof(glm::vec4), sizeof(mvp));
			}
		);
	};
};

class TestRunner : public of::graphics::ParentedRenderable
{

	struct Step
	{

	};

	struct Test
	{
		std::string name;
		of::imgui::ObjectiveState executionState = of::imgui::ObjectiveState::Active;

		std::vector<Step> testSteps;

		bool runTest();

	};

	struct TestResult
	{
		std::vector<std::pair<int, std::string>> testFailureStrings;
 	};

	struct Suite
	{
		std::string name;
		TestResult results;
		std::vector<Test> tests;

		void runTests();

		bool isSuiteRunning();

		TestResult& getTestResults();

	};

	std::vector<Suite> test;

public:

	TestRunner()
	{
		test = { {"test", {}, { {"a"}, {"b", of::imgui::ObjectiveState::Complete}, {"b", of::imgui::ObjectiveState::Failed}}}, {"test2"}};
	}


	virtual void updateFrame(const float&)
	{
	}

	virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>&, of::graphics::view::MVP&)
	{
		ImGui::SetNextWindowSize({ float(m_parent->getWindowWidth()), float(m_parent->getWindowHeight()) });
		ImGui::SetNextWindowPos({ 0.f, 0.f });
		if (ImGui::Begin("Test Runner"))
		{
			ImGui::Text("RunnerPanel");
			ImGui::Text("|<Run All>|<Run Suite>|<Run Failed>|<Run Selected>|   |<TOTAL>|PASSED|FAILED|   |SETTINGS|");
			ImGui::Text("");
			ImGui::ProgressBar(0, {400.f, 0});
			ImGui::Text("____________________________________________________________________________________________________________________________________________________________________________________");

			if (ImGui::BeginChild(ImGui::GetID("TestRunnerSidePanel"), {400.f, 0}))
			{
				ImGui::Text("Tests");
				
				for (auto& var : test)
				{
					ImGui::Text(var.name.c_str());
					for (auto& tc : var.tests)
					{
						ImGui::Bullet();
						ImGui::SameLine();
						ImGui::Text(tc.name.c_str());
						ImGui::SameLine();
						ImGui::Text("                     ");
						ImGui::SameLine();
						of::imgui::objectiveIcon("## bleh", tc.executionState);

					}
					ImGui::Text("__________________________________________");
				}
				
			}
			ImGui::EndChild();
			ImGui::SameLine();
			if (ImGui::BeginChild(ImGui::GetID("TestRunnerConfigPanel")))
			{
				ImGui::Text("|CONFIGURATOR PANEL");
				ImGui::Text("|");
				ImGui::Text("|");
				ImGui::Text("|");
				ImGui::Text("|");
				ImGui::Text("|");
				ImGui::Text("|");
				ImGui::Text("|");
				ImGui::Text("|");
			}
			ImGui::EndChild();
		}
		ImGui::End();
	};

};


class Heightmap : public of::graphics::ParentedRenderable
{

	size_t chunksCountX = 1;
	size_t chunksCountY = 1;
	bool link = false;
	int waterLevel = 64;
	int resolution = 1024;
	int chunkSize = 100;
	of::common::String heightMapPath;
	bool changed = true;
	bool& m_paused;

	struct HeightMapVertex
	{
		float x, y, z;
		float nx, ny, nz;
		float u, v;
	};

	class HeightmapData : public of::graphics::ParentedRenderable
	{
		bool done;
		bool set = false;
		common::Resource<swizzle::gfx::GfxBuffer> buf;
		common::Resource<swizzle::gfx::GfxBuffer> index;
		common::Resource<swizzle::gfx::Material> mat;
		common::Resource<swizzle::gfx::Shader> shader;
		common::Resource<swizzle::gfx::Texture> texture;

		std::vector<glm::vec3> points;
		std::vector<HeightMapVertex> verts;
		std::vector<glm::ivec3> tris;
		glm::vec4 black = { 0.f, 0.f, 0.0f, 0.f };

		void loadShader()
		{
			swizzle::gfx::ShaderAttributeList attribs = {};
			attribs.mBufferInput = {
				{ swizzle::gfx::ShaderBufferInputRate::InputRate_Vertex, sizeof(float) * (3U + 3U + 2U) }
			};

			attribs.mAttributes = {
				{ 0U, swizzle::gfx::ShaderAttributeDataType::vec3f, 0U},
				{ 0U, swizzle::gfx::ShaderAttributeDataType::vec3f, sizeof(float) * 3U },
				{ 0U, swizzle::gfx::ShaderAttributeDataType::vec2f, sizeof(float) * 6U }
			};
			attribs.mDescriptors = {
				{swizzle::gfx::DescriptorType::TextureSampler, swizzle::gfx::Count(1u), {swizzle::gfx::StageType::fragmentStage}},
				//{swizzle::gfx::DescriptorType::UniformBuffer, swizzle::gfx::Count(1u), {swizzle::gfx::StageType::fragmentStage}}, 
			};
			attribs.mEnableDepthTest = true;
			attribs.mEnableBlending = false;
			attribs.mEnableDepthWrite = true;
			attribs.mPushConstantSize = sizeof(glm::mat4) * 4u;
			attribs.mPrimitiveType = swizzle::gfx::PrimitiveType::triangle;

			shader = of::engine::GetModule<of::module::shader::Loader>().requestShader("terrain shader", "terrain.shader", attribs);
		}

		F32 getHeight(U8* image, S32 x, S32 y, S32 ch, F32 xp, F32 yp, F32 max)
		{
			F32 value = 0.0f;
			if (image)
			{
				U32 xCoord = U32(F32(x) * xp);
				if (xCoord >= (U32)x)
				{
					xCoord = x - 1;
				}
				U32 yCoord = U32(F32(y) * yp);

				if (yCoord >= (U32)y)
				{
					yCoord = y - 1;
				}

				U32 idx = ((yCoord * x) + xCoord) * ch;

				U8 val = image[idx];
				F32 conv = F32(val) / 255.0f;

				value = conv * max;
			}
			return value;
		}

		void loadHeightMap(std::string heightmap, std::vector<HeightMapVertex>& v, std::vector<glm::ivec3>& t,
			const glm::vec2& start, const glm::vec2& end, const size_t chunkCountX, const size_t chunkCountY)
		{
			S32 ix = 0;
			S32 iy = 0;
			S32 ic = 0;

			// we assume start is negative coords
			F32 totalX = end.x - start.x;
			F32 totalY = end.y - start.y;

			F32 ChunkSizeX = totalX / (float)chunkCountX;
			F32 ChunkSizeY = totalY / (float)chunkCountY;

			F32 step = 1.f;
			F32 UVDeltaX = step / ChunkSizeX;
			F32 UVDeltaY = step / ChunkSizeY;

			//U32 totalXI = (U32)totalX;
			//U32 totalYI = (U32)totalY;

			U8* image = stbi_load(heightmap.c_str(), &ix, &iy, &ic, 4);
			U32 lastSize = 0;
			for (U32 cx = 0; cx < chunkCountX; cx ++)
			{
				for (U32 cy = 0; cy < chunkCountY; cy++)
				{
					F32 startX = start.x + cx * ChunkSizeX;
					F32 endX = startX + ChunkSizeX;
					F32 startY = start.y + cy * ChunkSizeY;
					F32 endY = startY + ChunkSizeY;
					std::vector<HeightMapVertex> vertsTemp;
					std::vector<glm::ivec3> trisTemp;

					U32 totalXCnt = 0;
					U32 totalYCnt = 0;
					F32 ux = 0;
					for (F32 x = startX; x < endX + 1; x += step)
					{
						F32 uy = 0;
						for (F32 y = startY; y < endY + 1; y += step)
						{
							F32 px = (x + end.x) / totalX;
							F32 py = (y + end.y) / totalY;
							HeightMapVertex vert{};
							vert.x = x;
							vert.y = getHeight(image, ix, iy, ic, px, py, 10.0f);
							vert.z = y;
							vert.nz = 1.0f;

							vert.u = ux;
							vert.v = uy;

							uy += UVDeltaY;

							vertsTemp.push_back(vert);
						}
						ux += UVDeltaX;

						totalYCnt++;
						totalXCnt++;
					}

					for (U32 y = 0; y < totalYCnt -1; ++y)
					{
						for (U32 x = 0; x < totalXCnt -1; ++x)
						{
							U32 currRow = (y * totalYCnt) + x;
							U32 nextRow = ((y + 1) * totalYCnt) + x;

							currRow += lastSize;
							nextRow += lastSize;

							glm::ivec3 t1{ currRow + 1, nextRow + 1, currRow };
							glm::ivec3 t2{ currRow, nextRow + 1, nextRow };
							trisTemp.push_back(t1);
							trisTemp.push_back(t2);
						}
					}
					lastSize += (U32) vertsTemp.size();

					copy( vertsTemp.begin(), vertsTemp.end(), std::back_inserter(v));
					copy( trisTemp.begin(), trisTemp.end(), std::back_inserter(t));

				}
			}
			stbi_image_free(image);
		}

	public:
	
		HeightmapData()
		{
			done = false;
			auto& wnd = of::engine::GetModule<of::module::window::Proxy>();
			auto gfx = wnd.getGfxDevice();

			loadShader();
			mat = gfx->createMaterial(shader, swizzle::gfx::SamplerMode::SamplerModeClamp);
			texture = of::engine::GetModule<of::module::texture::Loader>().requestTexture("flower.png");
			mat->setDescriptorTextureResource(0u, texture);

			buf = gfx->createBuffer(swizzle::gfx::GfxBufferType::Vertex, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
			//buf->setBufferData(points.data(), 0, sizeof(float) * 3u);


			index = gfx->createBuffer(swizzle::gfx::GfxBufferType::Index, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
			//index->setBufferData(tris.data(), 0, sizeof(float));
		}

		size_t generate(const glm::vec2& a, const glm::vec2& b, const size_t chunksX, const size_t chunksY, const of::common::String& heightmap)
		{
			verts.clear();
			tris.clear();

			// calculate region splicing & chunk size.

			loadHeightMap(heightmap, verts, tris, a, b, chunksX, chunksY);

			done = true;
			return 0u;
		}

		virtual void updateFrame(const float&)
		{
			if (done)
			{
				buf->setBufferData(verts.data(), verts.size() * sizeof(HeightMapVertex), sizeof(HeightMapVertex));
				index->setBufferData(tris.data(), tris.size() * sizeof(glm::ivec3), sizeof(glm::ivec3));
				done = false;
				set = true;
			}
		}

		virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, of::graphics::view::MVP& mvp)
		{
			if (set)
			{
				mvp.model = glm::translate(glm::mat4(1.f), { 0.f,0.f,0.f });

				transaction->bindShader(shader);
				transaction->bindMaterial(shader, mat);
				transaction->setShaderConstant(shader, (U8*)&mvp, sizeof(mvp));
				//transaction->setShaderConstant(shader, (U8*)&black, sizeof(glm::vec4), sizeof(mvp));
				transaction->drawIndexed(buf, index);
			}
		};
	};

	class HeightmapOutline : public of::graphics::ParentedRenderable
	{
		bool& changed;
		of::graphics::view::Camera* c;
		common::Resource<swizzle::gfx::GfxBuffer> buf;
		common::Resource<swizzle::gfx::Material> mat;
		common::Resource<swizzle::gfx::Shader> shader;

		glm::vec3 line[5] = { 
			{-10.f, 0.f, 0.f},
			{-10.f, 0.f, 0.f},
			{10.f, 0.f, 0.f},
			{10.f, 0.f, 0.f},
			{-10.f, 0.f, 0.f},
		};

		glm::vec4 black = { 0.f, 1.f, 1.0f, 0.f };

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

			shader = of::engine::GetModule<of::module::shader::Loader>().requestShader("heightmap outline", "grid.shader", attribs);
		}

	public:

		HeightmapOutline(bool& changed) : c(m_parent->getCamera()), changed(changed)
		{
			auto& wnd = of::engine::GetModule<of::module::window::Proxy>();
			auto gfx = wnd.getGfxDevice();

			loadShader();
			mat = gfx->createMaterial(shader, swizzle::gfx::SamplerMode::SamplerModeClamp);

			buf = gfx->createBuffer(swizzle::gfx::GfxBufferType::Vertex, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
			buf->setBufferData(line, sizeof(line), sizeof(float) * 3u);

		}

		void setData(const glm::vec2& start, const glm::vec2& end)
		{
			line[0].x = start.x;
			line[0].z = start.y;

			line[1].x = start.x;
			line[1].z = end.y;

			line[2].x = end.x;
			line[2].z = end.y;

			line[3].x = end.x;
			line[3].z = start.y;

			line[4].x = start.x;
			line[4].z = start.y;
		}

		virtual void updateFrame(const float&)
		{
			if (changed)
			{
				buf->setBufferData(line, sizeof(line), sizeof(float) * 3u);
				changed = false;
			}
		}

		virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, of::graphics::view::MVP& mvp)
		{

			mvp.model = glm::translate(glm::mat4(1.f), { 0.f,0.f,0.f });

			transaction->bindShader(shader);
			transaction->bindMaterial(shader, mat);
			transaction->setShaderConstant(shader, (U8*)&mvp, sizeof(mvp));
			transaction->setShaderConstant(shader, (U8*)&black, sizeof(glm::vec4), sizeof(mvp));
			transaction->draw(buf);
		};
	};

	std::shared_ptr<HeightmapOutline> outline;
	std::shared_ptr<HeightmapData> data;

	of::imgui::FileSelector selector;

public:

	Heightmap(bool& p) : selector("SelectTexture", "Data/Heightmaps/", ".png"), m_paused(p)
	{
		outline = std::make_shared<HeightmapOutline>(changed);
		data = std::make_shared<HeightmapData>();
		m_parent->addRenderable(of::graphics::window::RenderLayer::EDITOR, of::common::uuid(), outline);
		m_parent->addRenderable(of::graphics::window::RenderLayer::EDITOR, of::common::uuid(), data);
	}

	virtual void updateFrame(const float&)
	{
	}

	virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>&, of::graphics::view::MVP&)
	{
		if (ImGui::Begin("Landmass Generator"))
		{
			changed |= ImGui::InputScalarN("Chunk Count", ImGuiDataType_U64, (void*) &chunksCountX, 2);
			ImGui::SameLine();
			ImGui::Checkbox("Link", &link);
			ImGui::InputText("Path", &heightMapPath);
			ImGui::SameLine();
			if (ImGui::Button("..."))
			{
				selector.open();
			}
			if (selector.hasFileBeenSelected())
			{
				heightMapPath = selector.getSelectedFile();
			}

			ImGui::InputInt("Water level", &waterLevel);
			Graphics::Editor::BasicToolTip(
				"Scalar between 0-255, it's defining the point on the heightmap used where it will put the water-line,"
				" note this does not mean the water will be put at this value."
			);
			changed |= ImGui::InputInt("Chunk size", &chunkSize);
			Graphics::Editor::BasicToolTip(
				"Size in units that one chunk is, e.g a chunk size of 10 would make "
				"the chunk (starting at x,y = 0,0), end at 9,9, and the next starting at 10,0, etc."
			);

			ImGui::InputInt("Resolution", &resolution);
			Graphics::Editor::BasicToolTip(
				"The resolution of the chunk, this affects how many vertices each chunk will contain, "
				"the higher, the more memory used, recommended to use a setting to the power of 2 based on the chunk size."
				"e.g a chunk size of 16, will have the resolution 256. This makes each triangle side lengths 1, 1 and sqrt(2)"
			);

			ImGui::Text("Estimated vert count: %d", resolution * chunksCountX * chunksCountY);
			ImGui::Text("Est size (Bytes): %d", resolution * chunksCountX * chunksCountY * (sizeof(glm::vec3) + sizeof(glm::vec3) + sizeof(glm::vec2)));

			float sizeX = chunkSize / 2.f * chunksCountX;
			float sizeY = chunkSize / 2.f * chunksCountY;
			ImGui::Text("Instance size: (-x, -y, x, y) %.1f, %.1f, %.1f, %.1f", -sizeX, -sizeY, sizeX, sizeY);

			outline->setData({-sizeX, -sizeY}, {sizeX, sizeY});

			if (ImGui::Button("Generate"))
			{
				m_paused = true;
				data->generate({-sizeX, -sizeY}, {sizeX, sizeY}, chunksCountX, chunksCountY, heightMapPath);

				// re-generate collision mesh

				m_paused = false;
			}

			if (selector.isOpen())
				selector.show();
			selector.ImGuiRenderModal();
		}
		ImGui::End();
	};
};


//static std::shared_ptr<PxSimulationStats> simulationStats;
static std::shared_ptr<CourierStats> courierStats;


GameEntry::GameEntry() : 
	gfx(std::make_shared<of::graphics::window::Application>()),
	time(of::engine::GetModule<of::module::Time>()),
	input(of::engine::GetModule<Input::InputHandler>()),
	world(of::engine::GetModule<of::module::SceneManager>()),
	courier(of::engine::GetModule<of::messaging::Courier>()), m_exit(false)
{
	of::engine::GetModule<of::module::window::WindowProxy>().setHandle(gfx);
	ups = std::make_shared<Graphics::UI::Stats>("UPS", 200.f, 120.f, Graphics::UI::Rel::Right);
	loadingScreenInfo = std::make_shared<Graphics::UI::LoadingScreenInfo>();
	courier.createChannel(of::messaging::Topic::Update);
	courier.getChannel(of::messaging::Topic::Update)->setMessageValidator(std::make_shared<of::messaging::IsMessageTypeValidator<of::messaging::BasicMessage<float>>>());
}

physx::PxRigidStatic* mActor;
physx::PxRigidDynamic* mActor2;

int GameEntry::Run()
{
	gfx->initialize();
	auto& physicsHandler = of::engine::GetModule<of::module::physics::PhysicsHandler>();
	physicsHandler.Initialize();
	auto model = of::engine::GetModule<of::module::mesh::Loader>().requestModel("wedge.swm", of::module::Settings::meshPath, true);
	auto model2 = of::engine::GetModule<of::module::mesh::Loader>().requestModel("testArrow.swm", of::module::Settings::meshPath, true);
	mActor = physicsHandler.createActor<physx::PxRigidStatic>({ 0.f, 1.f, 0.f }, model);
	mActor2 = physicsHandler.createActor<physx::PxRigidDynamic>({ 0.f, 8.f, -5.f }, model2);

	physicsHandler.attachTriggerShape(mActor2, model2, 1.4f);

	mActor->setName("Static actor");
	mActor2->setName("dynamic trigger actor");

	world.initialize();
	auto controller = of::engine::GetModule<of::module::ObjectInstanceHandler>().player->add<of::object::component::PlayerController>();
	//	simulationStats = std::make_shared<PxSimulationStats>(paused);
	courierStats = std::make_shared<CourierStats>();
	//gfx.setFramerate(of::engine::GetModule<EngineModule::GameConfig>().getFramerateLimit());

	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::UI::Stats>("FPS", 400.f, 120.f, Graphics::UI::Rel::Right));
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), ups);
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::UI::BuildInfo>(Engine::GetBuildMode().getDetailedBuildInfo(), 400.f, 50.f, Graphics::UI::Rel::Right));

	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::UI::LoadingScreen>());
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), loadingScreenInfo);
	//gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), simulationStats);
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), courierStats);

	gfx->addRenderable(of::graphics::window::RenderLayer::HITBOXES, of::common::uuid(), std::make_shared<PxControllerRenderable>(controller->mActor));

	gfx->addRenderable(of::graphics::window::RenderLayer::HITBOXES, of::common::uuid(), std::make_shared<PxMeshedActorRenderable<physx::PxRigidStatic>>(mActor, model));
	gfx->addRenderable(of::graphics::window::RenderLayer::HITBOXES, of::common::uuid(), std::make_shared<PxMeshedActorRenderable<physx::PxRigidDynamic>>(mActor2, model2));
	gfx->addRenderable(of::graphics::window::RenderLayer::HITBOXES, of::common::uuid(), std::make_shared<PxMeshedActorRenderable<physx::PxRigidDynamic>>(mActor2, model2, 1.4f,
		glm::vec4{0.6,0.3, 1.f, 0.f}));

	auto cameraController = std::make_shared<EditorController>();
	gfx->setCameraController(cameraController);

	if (of::engine::getRunMode() == of::engine::RunMode::EDITOR)
	{
		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::Editor::MainEditorWindow>());
		//gfx->addRenderable(of::graphics::window::RenderLayer::EDITOR, of::common::uuid(), std::make_shared<WorldGrid>());
		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Gizmo>());
		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<CustomTrackerPoint>(cameraController));
		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Heightmap>(paused));
		//gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<TestRunner>());

	}

	std::thread physics_thread(&GameEntry::physicsUpdate, this);

	gfx->loop();
	m_exit = true;
	physics_thread.join();
	of::engine::GetModule<of::module::physics::PhysicsHandler>().shutDown();

	//gfx.clearDrawList();
	return EXIT_SUCCESS;
}

void GameEntry::physicsUpdate()
{
	if (of::engine::getRunMode() != of::engine::RunMode::EDITOR)
	{
//		world.createMainMenu();
	}
	auto& physicsHandler = of::engine::GetModule<of::module::physics::PhysicsHandler>();
	time.physicsElapsed = time.physicsClock.secondsAsFloat(true);
	const float update_time = time.update_ms;
	while (!m_exit)
	{
		while (world.isLoading)
		{
			time.physicsElapsed = time.update_ms;
			world.Update();
			loadingScreenInfo->update();
			time.physicsClock.secondsAsFloat(true);
		}
		while (time.physicsElapsed >= time.update_ms)
		{
			time.physicsElapsed -= time.update_ms;
			if (paused == false)
			{
				input.update(update_time);
				world.Simulate(update_time);
				time.Simulate(update_time);
				physicsHandler.simulate(update_time);

				courierStats->updateCount();
				courier.post(of::messaging::Topic::Update, of::messaging::BasicMessage<float>(update_time));
				ups->tiq();
			}
			ups->update();
			ups->print();
		}
		time.physicsElapsed += time.physicsClock.secondsAsFloat(true);
	}
	std::cout << "Physics Exited!!" << std::endl;

}
