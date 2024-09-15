#pragma once

#include <graphics/renderable.hpp>

#include <graphics/view/mvp.hpp>

#include <graphics/model/Model.hpp>

#include <utils/common/string.hpp>

#include <swizzle/gfx/GfxDevice.hpp>

namespace of::graphics::sky
{
	class Skybox : public Renderable
	{
		bool loaded = false;
	public:
		of::resource::Model mModel;

	public:
		Skybox();

		void setSkyBox(std::shared_ptr<swizzle::gfx::GfxDevice> gfxDevice, const of::common::String& skyboxTextureFolder);

		void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& trans, view::MVP& mvp) override;
		
		inline std::shared_ptr<swizzle::gfx::Texture> getTexture() const { return mModel.texture; };

		// Inherited via Renderable
		virtual void updateFrame(const float dt) override;

	};
}
