#ifndef DIALOGCOMPONENT_HPP
#define DIALOGCOMPONENT_HPP

#include "IBaseComponent.hpp"
#include "../Text/MessageDefiner.hpp"
#include "../Text/FloatingText.hpp"
#include <string>
#include <SFML\System\Time.hpp>
#include <cereal\access.hpp>
#include <SFML\Graphics.hpp>

class DialogComponent : public IBaseComponent<DialogComponent>
{
public:
	sf::Sprite sprt;
	std::string dialogTexture;
	std::string fontName;
	std::string dialogMessage;
	
	sf::RenderTexture *rex;

	FloatingText *msg;

	float duration;
	int offsetX;
	int offsetY;
	int textOffsetX;
	int textOffsetY;
	DialogComponent();
	DialogComponent(float duration);
	DialogComponent(const DialogComponent &diag);
	~DialogComponent();

	void show();
	void close();
	void setMessage(std::string text, float duration = -1, int length = -1);
	void updateLocation();
	bool open;
	bool dCreated;

private:
	void createDialog();
	void createDialog(bool b);
	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive, const DialogComponent& dc);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive, DialogComponent& dc);
};


#endif DIALOGCOMPONENT_HPP