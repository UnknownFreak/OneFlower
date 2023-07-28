#include <object/component/Render.hpp>

#include <Object/GameObject.hpp>
#include <module/window/GraphicsProxy.hpp>
#include <module/window/WindowProxy.hpp>

#include <module/resource/TextureLoader.hpp>
#include <module/resource/MeshLoader.hpp>
#include <module/resource/ShaderLoader.hpp>

#include <messaging/courier.hpp>

namespace of::object::component
{
	void Render::loadAndSetModel()
	{
		auto& wnd = of::engine::GetModule<of::module::window::Proxy>();
		//auto temp = wnd.getUploadBuffer();
		//auto trans = temp->begin();
		auto gfx = wnd.getGfxDevice();

		textureName = "temporary.png";
		meshName = "test.swm";
		shaderName = "simple.shader";

		model = std::make_shared<of::resource::Model>();

		model->mesh = of::engine::GetModule<of::module::mesh::Loader>().requestMesh(meshName);
		{

			model->mMeshBuffer = gfx->createBuffer(swizzle::gfx::GfxBufferType::Vertex, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
			model->mIndexBuffer = gfx->createBuffer(swizzle::gfx::GfxBufferType::Index, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
			model->mBoneBuffer = gfx->createBuffer(swizzle::gfx::GfxBufferType::UniformBuffer, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
			model->mMeshBuffer->setBufferData((U8*)model->mesh->getVertexDataPtr(), model->mesh->getVertexDataSize(),
				sizeof(float) * (3u + 3u + 2u + 4u + 4u));

			model->mIndexBuffer->setBufferData((U8*)model->mesh->getIndexDataPtr(), model->mesh->getIndexDataSize(), sizeof(U32) * 3u);

			model->mBoneBuffer->setBufferData((U8*)model->mesh->getAnimationDataPtr(0, 0), model->mesh->getNumberOfBones() * sizeof(glm::mat4),
				sizeof(glm::mat4));

		}

		if (of::engine::GetModule<of::module::mesh::Loader>().getResult() == false)
		{
			model->texture = of::engine::GetModule<of::module::texture::Loader>().requestTexture("missingMeshTexture.png");
		}
		else
			model->texture = of::engine::GetModule<of::module::texture::Loader>().requestTexture(textureName);
		model->shader = of::engine::GetModule<of::module::shader::Loader>().requestShader(shaderName, shaderName);

		model->material = gfx->createMaterial(model->shader, swizzle::gfx::SamplerMode::SamplerModeClamp);

		model->material->setDescriptorTextureResource(0u, model->texture);
		model->material->setDescriptorBufferResource(1u, model->mBoneBuffer, ~0ull);

		initialized = true;
		//wnd.getCommandBuffer()->end(std::move(trans));
		//wnd.getGfxContext()->submit(&temp, 1, nullptr);
	}
	void Render::onMessage(const of::object::messaging::Message& message)
	{
		using namespace of::object::messaging;

		if (message.messageTopic == Topic::of(Topics::ON_DEATH))
		{
			if (model.get())
			{
				//		model->setAnimation("onDeath");
			}
		}
	}

	void Render::initialize()
	{
		loadAndSetModel();
		transform = attachedOn->get<of::object::component::Transform>();
		of::engine::GetModule<of::module::window::WindowProxy>().get()->addRenderable(of::graphics::window::RenderLayer::MODELS, attachedOn->id, attachedOn->getShared<Render>());

		of::engine::GetModule<of::messaging::Courier>().addSubscriber(of::messaging::Topic::Update, of::messaging::Subscriber(instanceId, warrantyFromThis(), [this](const of::messaging::Message& msg) {update(msg.as<of::messaging::BasicMessage<float>>().value); }));
	}

	void Render::deconstruct()
	{
		of::engine::GetModule<of::module::window::WindowProxy>().get()->removeRenderable(attachedOn->id);
		of::engine::GetModule<of::messaging::Courier>().removeSubscriber(of::messaging::Topic::Update, instanceId);
	}

	std::unique_ptr<of::object::component::Base> Render::ucopy() const
	{
		return std::make_unique<Render>(*this);
	}

	void Render::update(const float& fElapsedTime)
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
			model->render(transaction, mvp, transform->buffered, transform->facingAngle);
		}
	}
	void Render::updateFrame(const float& dt)
	{
		dt;
	}
}