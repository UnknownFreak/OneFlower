#ifndef RenderComponent_H
#define RenderComponent_H
#include <Core/Component/IBaseComponent.hpp>
#include <Core/Vector.h>
#include <AssetManager/SpriteRef.hpp>
//#include "../../Vector.h"
#include <Animations\SpriteSheetAnimation.hpp>
#include <Animations\SpriterEntityInstance.hpp>

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
		RenderComponent(std::string texture);

		//Name of spritesheet and rect position
		RenderComponent(std::string texture, int x, int y);

		virtual RenderComponent* copy();

		//Closer the bigger the number, Farther away less the number
		int renderlayer = 1;
		AnimationType animation = AnimationType::Static;

		Vector2i size;

		Vector2 position;

		int outline = 0;

		//Name of texture;
		std::string textureName = "test.png";

		SpriteRef sprite;

		std::map<std::string, SpriteSheetAnimation> animations;

		SpriterEntityInstance instance;

		//Reload texture with textureName
		void setTexture();

		//Set texture with name of Texture
		void setTexture(std::string texture);

		//Set texture with name of Texture and the size of rect for spritesheet and its location
		void setTexture(std::string texture, double x, double y, int width, int height);

		//Set current animation, For animations only
		void setAnimation(std::string animationName);

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
		std::string currentAnimation = "Default";
		//template < class Archive>//, GameObject& go>
		//friend void save(Archive& archive, const RenderComponent& rc);
		//template < class Archive>//, GameObject& go>
		//friend void load(Archive& archive, RenderComponent& rc);
	};
}
#endif