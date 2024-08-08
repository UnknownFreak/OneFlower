#define IMGUI_DEFINE_MATH_OPERATORS

#include "GameEntry.hpp"

#include <engine/runMode.hpp>

#include <thread>

#include <Module\BuildMode.hpp>

#include<File/GameConfig.hpp>

#include <Graphics/UI/Stats.hpp>
#include <Graphics/UI/BuildInfo.hpp>

#include <Graphics/UI/LoadingScreen.hpp>

#include <module/window/WindowProxy.hpp>
#include <Graphics/sky/skyBox.hpp>

#include <chrono>
#include <iostream>

#include <graphics/ui/frame.hpp>
#include <module/window/GraphicsProxy.hpp>
#include <module/resource/TextureLoader.hpp>
#include <module/resource/ShaderLoader.hpp>
#include <module/window/GraphicsProxy.hpp>

#include <imgui/imgui_stdlib.hpp>
#include <imgui/of_imgui_extensions.hpp>
#include <imgui/fileSelector.hpp>

#include <imgui/basicToolTip.hpp>

#include <component/render.hpp>

#include <stb/stb_image.h>
#include <algorithm>

#include <physics/physics.hpp>

#include <glm/glm.hpp>
#pragma warning(push, 0)
#include <glm/gtc/quaternion.hpp>
#pragma warning(pop)

#include <swizzle/asset2/Assets.hpp>
#include <module/resource/MeshLoader.hpp>
#include <graphics/model/Model.hpp>

#include<Input/PlayerController.hpp>

#include <physics/physics.hpp>

#include <component/collider.hpp>
#include <component/triggerCollider.hpp>
#include <component/doorHinge.hpp>

#include <editor.hpp>

#include <timer/timer.hpp>

bool paused = false;
static size_t mId = 0x100000000;

constexpr float pi = glm::pi<float>();

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

	virtual void updateFrame(const float )
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

class Sniffer : public of::courier::MessageValidator, public of::utils::lifetime::IsAlive
{
	std::shared_ptr<of::courier::MessageValidator> validator;
	std::shared_ptr<of::courier::ChannelTopic> m_channel;

	size_t m_messageCount = 0;
	size_t m_messagePerSecond = 0;
	size_t m_messagePerSecond2 = 0;

	size_t subscriberId;
public:
	of::timer::TickTimer m_tickTimer;

public:
	Sniffer(const of::courier::Topic t, std::string name)
	{
		m_channel = of::courier::get().getChannel(t);
		validator = m_channel->getValidator();
		subscriberId = of::courier::get().addSubscriber(of::courier::Topic::Object, of::courier::Subscriber(isAlive(),
			[this](const of::courier::Message& msg) {
				if (msg.msgType == of::courier::MessageType::Notify)
				{
					m_messagePerSecond2 = m_messagePerSecond;
					m_messagePerSecond = 0;
				}
			}));
		m_tickTimer.maxTime = 1.0f;
		m_tickTimer.autoReset = true;
		m_tickTimer.messagesToSend.push_back(std::make_pair(of::courier::Topic::Object, subscriberId));
		m_tickTimer.start();
	}

	~Sniffer()
	{
		m_tickTimer.stop();
		of::courier::get().removeSubscriber(of::courier::Topic::Object, subscriberId);
	}

	bool validate(const of::courier::Message& message)
	{
		if (validator)
		{
			m_messageCount++;
			m_messagePerSecond++;
			return validator->validate(message);
		}
		m_messageCount++;
		m_messagePerSecond++;
		return true;
	}

	size_t messageCount() const
	{
		return m_messageCount;
	}

	size_t subscriberCount() const
	{
		return m_channel->getSubscribersCount();
	}

	size_t messagesPerSecond() const
	{
		return m_messagePerSecond2;
	}

};

class CourierStats : public of::graphics::ParentedRenderable, public of::utils::lifetime::IsAlive
{
	std::shared_ptr<of::courier::ChannelTopic> m_channel;
	of::common::String string;
	int val = 0;
	bool m_add = false;
	of::common::uuid instanceId;
	
	float m_messageTiming;

	std::string m_execTime;
	std::string m_msgCount;
	size_t m_totalMsgCounter = 0;
	std::string m_totalMsgCountStr;

	std::shared_ptr<Sniffer> m_updateSniffer;
	std::shared_ptr<Sniffer> m_physicsSniffer;
	std::shared_ptr<Sniffer> m_singleThreadSniffer;
	std::shared_ptr<Sniffer> m_objectSniffer;

public:

	CourierStats() : m_channel(of::courier::get().getChannel(of::courier::Topic::Update))
	{
		auto& courier = of::courier::get();
		m_updateSniffer = std::make_shared<Sniffer>(of::courier::Topic::Update, "Update");
		m_physicsSniffer = std::make_shared<Sniffer>(of::courier::Topic::PhysicsUpdate, "Physics");
		m_singleThreadSniffer = std::make_shared<Sniffer>(of::courier::Topic::SingleThreadUpdate, "ST");
		m_objectSniffer = std::make_shared<Sniffer>(of::courier::Topic::Object, "Obj");

		courier.getChannel(of::courier::Topic::Update)->setMessageValidator(m_updateSniffer);
		courier.getChannel(of::courier::Topic::PhysicsUpdate)->setMessageValidator(m_physicsSniffer);
		courier.getChannel(of::courier::Topic::SingleThreadUpdate)->setMessageValidator(m_singleThreadSniffer);
		courier.getChannel(of::courier::Topic::Object)->setMessageValidator(m_objectSniffer);

	}

	virtual void updateFrame(const float)
	{
	}

	void updateCount()
	{
		if (m_add)
		{
			m_add = false;
			for (int i = 0; i < val; i++)
			{
				of::engine::GetModule<of::object::InstanceHandler>().addObject();
			}
		}
		string = std::to_string(m_channel->getSubscribersCount());
	}

	void text(const of::common::String& s, size_t value, size_t messagesPerSecond, size_t subscribers)
	{
		ImGui::Text(s.c_str());
		ImGui::SameLine();
		ImGui::Text("%llu", value);
		ImGui::SameLine();
		ImGui::Text("%llu/s", messagesPerSecond);
		ImGui::SameLine();
		ImGui::Text("Subscribers (%llu)", subscribers);
	}

	virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>&, of::graphics::view::MVP&)
	{
		ImGui::Begin("CourierStats");
		ImGui::Text(string.c_str());
		ImGui::Text(m_execTime.c_str());
		ImGui::Text(m_msgCount.c_str());
		ImGui::Text(m_totalMsgCountStr.c_str());

		ImGui::NewLine();

		ImGui::Text("Messages per channel:");
		text(" Update: ", m_updateSniffer->messageCount(), m_updateSniffer->messagesPerSecond(), m_updateSniffer->subscriberCount());
		text("Physics: ", m_physicsSniffer->messageCount(), m_physicsSniffer->messagesPerSecond(), m_physicsSniffer->subscriberCount());
		text("     ST: ", m_singleThreadSniffer->messageCount(), m_singleThreadSniffer->messagesPerSecond(), m_singleThreadSniffer->subscriberCount());
		text(" Object: ", m_objectSniffer->messageCount(), m_objectSniffer->messagesPerSecond(), m_objectSniffer->subscriberCount());

		ImGui::NewLine();

		ImGui::SliderInt("Object count", &val, 0, 100000);
		if(ImGui::Button("Add object"))
		{
			m_add = true;
		}
		ImGui::End();
	};

	void messageTime(std::chrono::duration<float, std::milli> time)
	{
		m_execTime = "ExecTime: " + std::format("{:.3f}", time.count()) + " ms";
	}

	void messageCount(size_t messageCount)
	{
		m_msgCount = "Handled: " + std::to_string(messageCount) + "/frame";
		m_totalMsgCounter += messageCount;
		m_totalMsgCountStr = "TotalHandled: " + std::to_string(m_totalMsgCounter);
	}
};


class PxControllerRenderable : public of::graphics::ParentedRenderable
{
	physx::PxController*& actor;
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

	PxControllerRenderable(physx::PxController*& controller) : actor(controller)
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
				auto angle = (pi/ 8.f) * i;
				auto x = radii * 0.3 * cos(angle);
				auto y = radii * 0.3 * sin(angle);
				points.push_back(glm::vec3(x, -(height * 0.98f), y));
			}
			connectToPoint(tris, 0, 16, 1);
			
			for (int i = 0; i < 16; i++)
			{
				auto angle = (pi / 8.f) * i;
				auto x = radii * 0.7 * cos(angle);
				auto y = radii * 0.7 * sin(angle);
				points.push_back(glm::vec3(x, -(height * 0.9f), y));
			}
			connectToCircle(tris, 16, 1, 17);
			
			for (int i = 0; i < 16; i++)
			{
				auto angle = (pi / 8.f) * i;
				auto x = radii * cos(angle);
				auto y = radii * sin(angle);
				points.push_back(glm::vec3(x, -(height * 0.8f), y));
			}
			connectToCircle(tris, 16, 17, 33);

			for (int i = 0; i < 16; i++)
			{
				auto angle = (pi / 8.f) * i;
				auto x = radii * cos(angle);
				auto y = radii * sin(angle);
				points.push_back(glm::vec3(x, (topHeight * 0.8f), y));
			}
			connectToCircle(tris, 16, 33, 49);

			for (int i = 0; i < 16; i++)
			{
				auto angle = (pi / 8.f) * i;
				auto x = radii * 0.7 * cos(angle);
				auto y = radii * 0.7 * sin(angle);
				points.push_back(glm::vec3(x, (topHeight * .9f), y));
			}
			connectToCircle(tris, 16, 49, 65);

			for (int i = 0; i < 16; i++)
			{
				auto angle = (pi / 8.f) * i;
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

	virtual void updateFrame(const float)
	{
		auto& vec = actor->getPosition();
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

class PxMeshedActorRenderable : public of::graphics::ParentedRenderable, public of::utils::lifetime::IsAlive
{
	physx::PxRigidActor*& mActor;
	of::resource::Model model;
	
	glm::vec3 pos;
	glm::vec3 scale;
	glm::quat rot;

	glm::vec3 shapeOffset;

	glm::vec4 renderingColor = { 0.3f, 0.3f, 1.f, 0.f };
	size_t subscriberId;

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

	PxMeshedActorRenderable(physx::PxRigidActor*& iactor, of::resource::Model mesh, glm::vec3 scale = glm::vec3(1.f), glm::vec4 renderingColor = {0.3f, 0.3f, 1.f, 0.f}, glm::vec3 shapeOffset=glm::vec3(0.f)) : mActor(iactor), model(mesh), scale(scale), renderingColor(renderingColor),
		shapeOffset(shapeOffset)
	{
		auto& wnd = of::engine::GetModule<of::module::window::Proxy>();
		auto gfx = wnd.getGfxDevice();
		loadShader();

		model.material = gfx->createMaterial(model.shader, swizzle::gfx::SamplerMode::SamplerModeClamp);

		auto channel = of::courier::get().getChannel(of::courier::Topic::Update);
		subscriberId = channel->addSubscriber(of::courier::Subscriber(isAlive(), [&](const of::courier::Message&)
			{
				if (mActor)
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
			}
		));

	}

	~PxMeshedActorRenderable()
	{
		auto channel = of::courier::get().getChannel(of::courier::Topic::Update);
		channel->removeSubscriber(subscriberId);
	}

	virtual void updateFrame(const float)
	{
	}

	virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, of::graphics::view::MVP& mvp)
	{
		mvp.model = glm::translate(glm::mat4(1.f), pos);
		mvp.model *= glm::mat4_cast(rot);
		mvp.model = glm::scale(mvp.model, scale);
		mvp.model = glm::translate(mvp.model, shapeOffset);

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


	virtual void updateFrame(const float)
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

		virtual void updateFrame(const float)
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

		virtual void updateFrame(const float)
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

	virtual void updateFrame(const float)
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
			of::imgui::BasicToolTip(
				"Scalar between 0-255, it's defining the point on the heightmap used where it will put the water-line,"
				" note this does not mean the water will be put at this value."
			);
			changed |= ImGui::InputInt("Chunk size", &chunkSize);
			of::imgui::BasicToolTip(
				"Size in units that one chunk is, e.g a chunk size of 10 would make "
				"the chunk (starting at x,y = 0,0), end at 9,9, and the next starting at 10,0, etc."
			);

			ImGui::InputInt("Resolution", &resolution);
			of::imgui::BasicToolTip(
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

template<of::courier::MessageType T>
class IsMessageTypeValidator : public of::courier::MessageValidator
{
	virtual inline bool validate(const of::courier::Message& message) override
	{
		if (message.msgType != T)
		{
			auto& logger = of::engine::GetModule<of::logger::Logger>().getLogger("of::IsMessageTypeValidator");
			logger.Info("Invalid message type passed [requiredType, checked] [", (unsigned int)T, ", ", (unsigned int)message.msgType, + "]");
			return false;
		}
		return true;
	}
};

GameEntry::GameEntry() : 
	gfx(std::make_shared<of::graphics::window::Application>()),
	input(of::engine::GetModule<of::input::InputHandler>()),
	world(of::engine::GetModule<of::module::SceneManager>()),
	courier(of::courier::get()), m_exit(false)
{
	of::engine::GetModule<of::module::window::WindowProxy>().setHandle(gfx);
	ups = std::make_shared<Graphics::UI::Stats>("UPS", 150.f, 120.f, Graphics::UI::Rel::Right);
	loadingScreenInfo = std::make_shared<Graphics::UI::LoadingScreenInfo>();
	courier.createChannel(of::courier::Topic::Update);
	courier.createChannel(of::courier::Topic::PhysicsUpdate);
	courier.createChannel(of::courier::Topic::SingleThreadUpdate);
	courier.createChannel(of::courier::Topic::Object);
	auto validator = std::make_shared<IsMessageTypeValidator<of::courier::MessageType::DeltaTime>> ();
	courier.getChannel(of::courier::Topic::Update)->setMessageValidator(validator);
	courier.getChannel(of::courier::Topic::PhysicsUpdate)->setMessageValidator(validator);
	courier.getChannel(of::courier::Topic::PhysicsUpdate)->setMultiThreaded(false);
	courier.getChannel(of::courier::Topic::SingleThreadUpdate)->setMessageValidator(validator);
	courier.getChannel(of::courier::Topic::SingleThreadUpdate)->setMultiThreaded(false);
}

int GameEntry::Run()
{
	gfx->initialize();

	of::physics::init();

	world.initialize();
	while (world.isLoading)
	{
		world.Update();
	}

	auto door = of::engine::GetModule<of::object::InstanceHandler>().addObject();

	door->initialize();

	door->get<of::component::Transform>()->pos = glm::vec3(1.f, 4.f, 3.f);

	auto collider = std::make_shared<of::component::Collider>();
	collider->mColliderMesh = "door.swm";
	collider->mColliderType = of::component::Collider::ColliderType::RIGID;
	auto triggerCollider = std::make_shared<of::component::TriggerCollider>();
	triggerCollider->mColliderShapeType = of::component::TriggerCollider::ShapeType::BOX;
	triggerCollider->mTriggerShapeScale = glm::vec3(1.4f,1.5f,0.9f);
	triggerCollider->mTriggerShapeOffset.y = 1.5f;

	/*
	auto hinge = new of::object::component::DoorHinge();
	hinge->mHingeOffset = { 0, 0, 1.f };
	//*/
	door->add(collider);
	door->add(triggerCollider);
	/*
	auto p = collider->mActor->getGlobalPose();
	p.q = physx::PxQuat(1.23f, physx::PxVec3(0,1,0));
	collider->mActor->setGlobalPose(p);
	door->add(hinge);

	of::engine::GetModule<of::input::InputHandler>().playerKeyboard.RegisterCallback(of::input::Callback::KeyboardCallbackTemp("KbSp", [&](bool, swizzle::input::Keys, const float& ) {
		std::cout << "Toggle" << std::endl;
		hinge->onMessage({ of::object::messaging::Topic::of(of::object::messaging::Topics::TOGGLE_STATE), std::make_shared<of::object::messaging::Body>()});
		}, false), swizzle::input::Keys::KeySpace, of::input::Action::Press);
	//*/

	auto controller = of::engine::GetModule<of::object::InstanceHandler>().player->add<of::component::PlayerController>();
	//	simulationStats = std::make_shared<PxSimulationStats>(paused);
	courierStats = std::make_shared<CourierStats>();
	//gfx.setFramerate(of::engine::GetModule<EngineModule::GameConfig>().getFramerateLimit());

	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::UI::Stats>("FPS", 300.f, 120.f, Graphics::UI::Rel::Right));
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), ups);
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::UI::BuildInfo>(Engine::GetBuildMode().getDetailedBuildInfo(), 300.f, 20.f, Graphics::UI::Rel::Right));

	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::UI::LoadingScreen>());
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), loadingScreenInfo);
	//gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), simulationStats);
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), courierStats);

	gfx->addRenderable(of::graphics::window::RenderLayer::HITBOXES, of::common::uuid(), std::make_shared<PxControllerRenderable>(controller->mActor));

	auto model = of::engine::GetModule<of::module::mesh::Loader>().requestModel("door.swm", of::engine::path::meshes, true);
	auto model2 = of::engine::GetModule<of::module::mesh::Loader>().requestModel("cube.swm", of::engine::path::meshes, true);
	//*
	gfx->addRenderable(of::graphics::window::RenderLayer::HITBOXES, of::common::uuid(), std::make_shared<PxMeshedActorRenderable>(collider->mActor, model));
	gfx->addRenderable(of::graphics::window::RenderLayer::HITBOXES, of::common::uuid(), std::make_shared<PxMeshedActorRenderable>(collider->mActor, model2, glm::vec3(1.4, 1.5f, 0.9f),
		glm::vec4{0.6, 0.3, 1.f, 0.f}, glm::vec3(0, 1.f, 0)));
		//*/

	if (of::engine::getRunMode() == of::engine::RunMode::EDITOR)
	{
		of::editor::initialize(gfx);
		// TODO: move to editor initialize
		//gfx->addRenderable(of::graphics::window::RenderLayer::EDITOR, of::common::uuid(), std::make_shared<WorldGrid>());
		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Heightmap>(paused));
		//gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<TestRunner>());

	}

	/*
	
	Mod dll loading go here

	*/

	gfx->workerThread = std::thread(&GameEntry::physicsUpdate, this);
	gfx->run();

	of::engine::GetModule<of::object::InstanceHandler>().unloadAll();
	delete of::engine::GetModule<of::object::InstanceHandler>().player;
	of::physics::shutdown();

	if (of::engine::getRunMode() == of::engine::RunMode::EDITOR)
	{
		of::editor::exit();
	}
	//gfx.clearDrawList();
	return EXIT_SUCCESS;
}

void GameEntry::physicsUpdate()
{
	if (of::engine::getRunMode() != of::engine::RunMode::EDITOR)
	{
//		world.createMainMenu();
	}
	auto& physicsHandler = of::physics::get();
	float timeElapsed = 0.f;
	auto& timer = of::timer::get("physicsClock");
	timeElapsed = timer.secondsAsFloat(true);
	while (gfx->running())
	{
		while (world.isLoading)
		{
			timeElapsed = of::timer::constants::update_ms;
			world.Update();
			loadingScreenInfo->update();
			timer.reset();
		}
		ups->tiq();
		while (timeElapsed >= of::timer::constants::update_ms)
		{
			const float update_time = timeElapsed;
			timeElapsed -= update_time;
			if (paused == false)
			{
				input.update(update_time);
				world.Simulate(update_time);
				//time.Simulate(update_time);
				physicsHandler.simulate(update_time);

				courierStats->updateCount();

				auto then = std::chrono::high_resolution_clock::now();
				auto message = of::courier::Message(of::courier::MessageType::DeltaTime, update_time);
				
				courier.post(of::courier::Topic::Update, message);
				courier.post(of::courier::Topic::PhysicsUpdate, message);
				courier.post(of::courier::Topic::SingleThreadUpdate, message);
				courier.handleScheduledMessages();
				courier.handleScheduledRemovals();
				auto delta = std::chrono::high_resolution_clock::now() - then;
				courierStats->messageTime(std::chrono::duration<float, std::milli>(delta));
				courierStats->messageCount(courier.messageCount());

			}
			ups->update();
			ups->print();
		}
		timeElapsed += timer.secondsAsFloat(true);
	}
	std::cout << "Physics Exited!!" << std::endl;

}
