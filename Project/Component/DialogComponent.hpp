#ifndef DIALOGCOMPONENT_HPP
#define DIALOGCOMPONENT_HPP

#include "IBaseComponent.hpp"
#include "../MessageDefiner.hpp"
#include <string>
#include <SFML\System\Time.hpp>
#include <cereal\access.hpp>
#include <SFML\Graphics.hpp>

class DialogComponent : public IBaseComponent<DialogComponent>
{
public:
	sf::Sprite sprt;
	sf::RenderTexture* rex;
	std::string dialogTexture;
	std::string fontName;
	Message msg;
	float duration;
	//DialogComponent();
	DialogComponent(float duration =-1);
	~DialogComponent();
	void show();
	void close();
	void setMessage(std::string text, float duration = -1, int length = -1);
	bool open;

private:
	GameObject* go;
	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive, const DialogComponent& dc);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive, DialogComponent& dc);
};


#endif DIALOGCOMPONENT_HPP