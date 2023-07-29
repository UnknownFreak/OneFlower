#pragma once

#include <memory>
#include <functional>

#include <swizzle/gfx/Texture.hpp>
#include <swizzle/gfx/Material.hpp>
#include <swizzle/asset2/Assets.hpp>

#include <swizzle/gfx/CommandBuffer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <graphics/view/mvp.hpp>

namespace of::resource
{
	class Model
	{
	public:


		std::shared_ptr<swizzle::gfx::Texture> texture;
		std::shared_ptr<swizzle::gfx::Material> material;
		std::shared_ptr<swizzle::gfx::Shader> shader;
		std::shared_ptr<swizzle::asset2::IMeshAsset> mesh;
		std::shared_ptr<swizzle::gfx::GfxBuffer> mMeshBuffer;
		std::shared_ptr<swizzle::gfx::GfxBuffer> mIndexBuffer;
		std::shared_ptr<swizzle::gfx::GfxBuffer> mBoneBuffer;
		bool mValid = false;
		bool mUseBones;

		void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, of::graphics::view::MVP& mvp)
		{
			transaction->bindShader(shader);
			transaction->bindMaterial(shader, material);
			transaction->setShaderConstant(shader, (U8*)&mvp, sizeof(mvp));
			transaction->drawIndexed(mMeshBuffer, mIndexBuffer);
		}

		void renderNoIndex(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, of::graphics::view::MVP& mvp)
		{
			transaction->bindShader(shader);
			transaction->bindMaterial(shader, material);
			transaction->setShaderConstant(shader, (U8*)&mvp, sizeof(mvp));
			transaction->draw(mMeshBuffer);
		}

		void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, of::graphics::view::MVP& mvp, glm::vec3& position, const float& facingAngle)
		{
			mvp.model = glm::translate(glm::mat4(1.f), position);
			mvp.model = glm::rotate(mvp.model, 0.f, glm::vec3(1.f, 0.f, 0.f));
			mvp.model = glm::rotate(mvp.model, 0.f, glm::vec3(0.f, 1.f, 0.f));
			mvp.model = glm::rotate(mvp.model, facingAngle, glm::vec3(0.f, 0.f, 1.f));

			render(transaction, mvp);
		}


		/*
		* Draw mesh with a pre-computed mvp & set additional shader constants via the transaction callback
		*/
		void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, of::graphics::view::MVP& mvp, std::function<void()> transactionCallback)
		{
			transaction->bindShader(shader);
			transaction->bindMaterial(shader, material);
			transaction->setShaderConstant(shader, (U8*)&mvp, sizeof(mvp));
			transactionCallback();
			transaction->drawIndexed(mMeshBuffer, mIndexBuffer);
		}

		std::shared_ptr<Model> clone()
		{
			return std::make_shared<Model>(texture, material, shader, mesh, mMeshBuffer, mIndexBuffer, mBoneBuffer, mValid , mUseBones);
		}

		explicit operator bool() const
		{
			return mValid;
		}

	};
}