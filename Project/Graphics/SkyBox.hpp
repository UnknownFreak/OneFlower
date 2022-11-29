#ifndef SkyBox_Hpp
#define SkyBox_Hpp

#include <memory>

#include "mvp.hpp"

#include "Model.hpp"

#include <utils/common/string.hpp>

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
		Skybox(const of::common::String& skyboxTextureFolder);

		void setSkyBox(const of::common::String& skyboxTextureFolder);

		void render(common::Unique<swizzle::gfx::DrawCommandTransaction>& trans, MVP mvp);
		
		inline std::shared_ptr<swizzle::gfx::Texture> getTexture() const { return mModel->texture; };
	};
}

#endif