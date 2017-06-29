#ifndef RenderComponent_H
#define RenderComponent_H
#include <Core/Component/IBaseComponent.hpp>
#include <Core/Vector.h>
#include <AssetManager/SpriteRef.hpp>
//#include "../../Vector.h"
#include <Model\SpriteSheetAnimation.hpp>
#include <Model\SpriterEntityInstance.hpp>

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

		// should be removed and replaced by IModel
		enum class AnimationType
		{
			//Static means this sprite has no animation.
			Static,
			//SpriteSheet means this sprite have one or more animations where
			//All animations can fit inside the spreadsheet, and have to be manually mapped
			SpriteSheet,
			//Armature means this sprite have many animations, moving parts, etc.
			//Animations are preset, only need to manually map the spriteparts
			Armature,
		};

		~RenderComponent();

		RenderComponent();
		RenderComponent(const RenderComponent & rc);
		RenderComponent(Core::String texture);

		//Name of spritesheet and rect position
		RenderComponent(Core::String texture, int x, int y);

		virtual RenderComponent* copy();

		//Closer the bigger the number, Farther away less the number
		int renderlayer = 1;
		
		// replace by IModel
		AnimationType animation = AnimationType::Static;

		// replace by IModel
		Core::Vector2i size;

		Core::Vector2 position;

		int outline = 0;

		//Name of texture;
		Core::String textureName = "test.png";

		SpriteRef sprite;

		// should be removed and replaced by IModel
		std::map<Core::String, SpriteSheetAnimation> animations;
		// should be removed and replaced by IModel
		SpriterEntityInstance instance;

		//Reload texture with textureName
		void setTexture();

		//Set texture with name of Texture
		void setTexture(Core::String texture);

		//Set texture with name of Texture and the size of rect for spritesheet and its location
		void setTexture(Core::String texture, double x, double y, int width, int height);

		//Set current animation, For animations only
		void setAnimation(Core::String animationName);

		// should be removed and replaced by IModel
		void updateFrame();

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
			archive(size.x);
			archive(size.y);
			archive(animation);
			//archive(rc.frameSpeed);
			archive(outline);
			if (animation == AnimationType::SpriteSheet)
				;// archive(animations);
			else if (animation == AnimationType::Armature)
				;// archive(instance);
		}

	protected:
		void attachOn(GameObject* go);

	private:

		void setFacing(Facing f);
		Core::String currentAnimation = "Default";
		//template < class Archive>//, GameObject& go>
		//friend void save(Archive& archive, const RenderComponent& rc);
		//template < class Archive>//, GameObject& go>
		//friend void load(Archive& archive, RenderComponent& rc);
	};
}
#endif