#ifndef SkyBox_Hpp
#define SkyBox_Hpp

#include <graphics/renderable.hpp>

#include <memory>

#include <graphics/view/mvp.hpp>

#include <module/resource/Model.hpp>

#include <utils/common/string.hpp>

#include <swizzle/gfx/CommandBuffer.hpp>

namespace of::graphics::sky
{
	class Skybox : public Renderable
	{
		bool loaded = false;
	public:
		std::shared_ptr<of::resource::Model> mModel;

	public:
		Skybox();
		Skybox(const of::common::String& skyboxTextureFolder);

		void setSkyBox(const of::common::String& skyboxTextureFolder);

		void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& trans, view::MVP& mvp) override;
		
		inline std::shared_ptr<swizzle::gfx::Texture> getTexture() const { return mModel->texture; };

		// Inherited via Renderable
		virtual void updateFrame(const float& dt) override;
	};
}

#endif