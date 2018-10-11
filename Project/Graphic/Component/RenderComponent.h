#ifndef RenderComponent_H
#define RenderComponent_H
#include <Core/Component/IBaseComponent.hpp>
#include <Core/Vector.h>
#include <Asset/SpriteRef.hpp>
//#include "../../Vector.h"
#include <Model\SpriteSheetAnimation.hpp>
#include <Model\IModel.hpp>

namespace Component
{
	class RenderComponent : public IBaseComponent < RenderComponent >
	{
	public:
		enum class Facing
		{
			Right,
			Left
		};

		~RenderComponent();

		RenderComponent();
		RenderComponent(const RenderComponent & rc);
		RenderComponent(Core::String texture);

		//Name of spritesheet and rect position
		RenderComponent(Core::String texture, int x, int y);

		virtual RenderComponent* copy() const;

		IModel* model = nullptr;;

		std::pair<Core::String, size_t> modelName;

		//Closer the bigger the number, Farther away less the number
		int renderlayer = 1;
		
		Core::Vector2 position;

		int outline = 0;

		//Name of texture;
		Core::String textureName = "test.png";

		SpriteRef sprite;

		//Reload texture with textureName
		void setTexture();

		//Set texture with name of Texture
		void setTexture(Core::String texture);

		//Set texture with name of Texture and the size of rect for spritesheet and its location
		void setTexture(Core::String texture, double x, double y, int width, int height);

		//Set current animation, For animations only
		void setAnimation(Core::String animationName);

		// should be removed and replaced by IModel
		void updateFrame(const size_t& update_ms);

		bool updateFromEditor();

		void getMessage(const BaseMessage message);

		Facing facingDirection;

		template < class Archive>
		void serialize(Archive& archive)
		{
			float x = sprite.getScale().x;
			float y = sprite.getScale().y;
			//	archive(rc.getTypeName());
			archive(componentName);
			archive(renderlayer);
			archive(textureName);
			archive(x);
			archive(y);
			archive(modelName.first, modelName.second);
		}

	protected:
		void attachOn(GameObject* go);

	private:

		void setFacing(Facing f);
		Core::String currentAnimation = "Default";
	};
}
#endif