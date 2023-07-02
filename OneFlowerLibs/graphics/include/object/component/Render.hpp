#ifndef RenderComponent_HPP
#define RenderComponent_HPP

#include <object/component/Transform.hpp>
#include <graphics/renderable.hpp>

#include <file/FileId.hpp>
#include <resource/Model.hpp>

namespace of::object::component
{


	class Render : public of::object::component::Base, public of::graphics::Renderable
	{
		bool initialized = false;

		of::object::component::Transform* transform;

		of::common::String textureName;
		of::common::String meshName;
		of::common::String shaderName;

		void loadAndSetModel();

		virtual void onMessage(const of::object::messaging::Message& message) override;
		virtual void initialize() override;
		virtual void deconstruct() override;

	public:
		std::shared_ptr<of::resource::Model> model;


		virtual Render* copy() const override
		{
			return new Render(*this);
		}

		virtual std::unique_ptr<Base> ucopy() const override;

		virtual void update(const float& fElapsedTime);

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(textureName);
			ar(meshName);
			ar(shaderName);
		}
		template<class Archive>
		void load(Archive& ar)
		{
			ar(textureName);
			ar(meshName);
			ar(shaderName);
			loadAndSetModel();
		}

		of::common::uuid getType() const override
		{
			return typeId;
		};

		of::common::String getTypeName() const override
		{
			return "Render";
		};

		static constexpr of::common::uuid typeId = "206d37a1-aa09-44ff-bd7b-bfdd4b5a4b87";

		// Inherited via Renderable
		virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, graphics::view::MVP& mvp) override;

		// Inherited via Renderable
		virtual void updateFrame(const float& dt) override;
	};
}

#endif