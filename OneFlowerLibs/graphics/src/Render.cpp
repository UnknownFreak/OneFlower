#include <component/render.hpp>

#include <object/GameObject.hpp>
#include <graphics/window/Window.hpp>

#include <module/resource/TextureLoader.hpp>
#include <module/resource/MeshLoader.hpp>
#include <module/resource/ShaderLoader.hpp>

#include <courier/courier.hpp>

namespace of::component
{
	void Render::loadAndSetModel()
	{
		textureName = "temporary.png";
		meshName = "test.swm";
		shaderName = "simple.shader";

		model.mesh = of::module::mesh::get().requestModel(meshName);

		if (of::module::mesh::get().getResult() == false)
		{
			model.texture = of::module::texture::get().requestTexture("missingMeshTexture.png");
		}
		else
			model.texture = of::module::texture::get().requestTexture(textureName);
		model.shader = of::module::shader::get().requestShader(shaderName, shaderName);

		model.material = of::module::shader::get().createMaterial(model.shader, swizzle::gfx::SamplerMode::SamplerModeClamp);

		model.material->setDescriptorTextureResource(0u, model.texture);
		model.material->setDescriptorBufferResource(1u, model.mesh->mBoneBuffer, ~0ull);

		initialized = true;
	}
	void Render::onMessage(const of::object::messaging::Message& message)
	{
		using namespace of::object::messaging;

		if (message.messageTopic == Topic::of(Topics::ON_DEATH))
		{
			if (model)
			{
				//		model->setAnimation("onDeath");
			}
		}
	}

	void Render::attached()
	{
		loadAndSetModel();
		transform = attachedOn->get<of::component::Transform>();
		if (auto valid = of::graphics::window::Application::GetWindowSource().lock())
		{
			valid->addRenderable(of::graphics::window::RenderLayer::MODELS, attachedOn->id, attachedOn->getShared<Render>());
		}

		if (subscriberId == 0)
		{
			subscriberId = of::courier::get().addSubscriber(of::courier::Topic::Update, of::courier::Subscriber(isAlive(), [this](const of::courier::Message& msg) {update(msg.get<float>()); }));
		}
	}

	void Render::initialize()
	{

	}

	void Render::deconstruct()
	{
		if (auto valid = of::graphics::window::Application::GetWindowSource().lock())
		{
			valid->removeRenderable(attachedOn->id);
		}
		if (subscriberId != 0)
		{
			of::courier::get().removeSubscriber(of::courier::Topic::Update, subscriberId);
		}
	}

	std::unique_ptr<of::component::Base> Render::ucopy() const
	{
		return std::make_unique<Render>(*this);
	}

	void Render::update(const float fElapsedTime)
	{

		fElapsedTime;
		if (model)
		{
			//model->material->setDescriptorTextureResource(0u, model->texture);
			//model->mesh->updateFrame(fElapsedTime);
		}
	}

	void Render::render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, graphics::view::MVP& mvp)
	{
		if (model)
		{
			model.render(transaction, mvp, transform->buffered, transform->facingAngle);
		}
	}
	void Render::updateFrame(const float dt)
	{
		dt;
	}
}