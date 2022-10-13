#ifndef SkyBox_Hpp
#define SkyBox_Hpp

#include <memory>

#include "mvp.hpp"

#include "Model.hpp"

#include <Helpers/String.hpp>

#include <swizzle/gfx/CommandBuffer.hpp>

namespace Graphics
{
	class Skybox
	{
		bool loaded = false;
	public:
		std::shared_ptr<Model> mModel;

	public:
		Skybox();
		Skybox(const Core::String& skyboxTextureFolder);

		void setSkyBox(const Core::String& skyboxTextureFolder);

		void render(common::Unique<swizzle::gfx::DrawCommandTransaction>& trans, MVP mvp);
		
		inline std::shared_ptr<swizzle::gfx::Texture> getTexture() const { return mModel->texture; };
	};
}

#endif