#ifndef DIALOGCOMPONENT_HPP
#define DIALOGCOMPONENT_HPP

#include "IBaseComponent.hpp"
#include "../GUI/Text/FloatingText.hpp"
#include "../GUI/Message.hpp"
#include <string>
#include <SFML\System\Time.hpp>
#include <SFML\Graphics.hpp>
#include "../../Vector.h"

class DialogComponent: public IBaseComponent < DialogComponent >
{
public:
	//sf::Sprite sprt;
	std::string fontName;
	std::string dialogMessage;

	//sf::RenderTexture *rex;

	FloatingText *msg;
	Vector2 position;
	DialogComponent();
	DialogComponent(double duration);
	DialogComponent(const DialogComponent &diag);
	~DialogComponent();

	void show();
	void close();
	void setMessage(std::string text,double duration = -1,int length = -1);
	void updateLocation();
	bool open;
	bool dCreated;
	bool updateFromEditor();
protected:
	void attachOn(GameObject* go);

private:

	void tryLoadTextureAndFont();

	void createDialog();
	void createDialog(bool b);

	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive,const DialogComponent& dc);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive,DialogComponent& dc);
};

#endif DIALOGCOMPONENT_HPP