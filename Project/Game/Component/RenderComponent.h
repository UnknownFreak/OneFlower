#ifndef RenderComponent_H
#define RenderComponent_H
#include <SFML\Graphics\Sprite.hpp>
#include "IBaseComponent.hpp"
#include "../../Vector.h"

class RenderComponent: public IBaseComponent < RenderComponent >
{
public:

	RenderComponent();
	RenderComponent(const RenderComponent & rc);
	RenderComponent(std::string texture);

	//Name of spritesheet and rect position
	RenderComponent(std::string texture,int x,int y);

	//Closer the bigger the number, Farther away less the number
	int renderlayer = 1;
	bool animation = false;
	int frameSpeed = 30;

	Vector2 size;

	Vector2 position;

	int outline = 0;

	//Name of texture;
	std::string textureName = "test.png";

	sf::Sprite sprite;

	//LOW: Remove this not needed
	double currentFrame = 1;

	//Reload texture with textureName
	void setTexture();

	//Set texture with name of Texture
	void setTexture(std::string texture);

	//Set texture with name of Texture and the size of rect for spritesheet and its location
	void setTexture(std::string texture,int x,int y,int width,int height);

	//Reload Texture and parameter for the rect size, and it currently "frame position", Makes animation = true
	void setAnimation(int x,int y,int width,int height);

	//Set texture, set Width and Height for the rect on each sprite for spritesheet, For animations only
	void setAnimation(std::string texture,int width,int height);

	void updateFrame();

	bool updateFromEditor();

	Vector2 oldSizePixel;
protected:
	void attachOn(GameObject* go);

private:
	//LOW: Remove this, dont think it needed
	Vector2 frame;

	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive,const RenderComponent& rc);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive,RenderComponent& rc);
};

#endif