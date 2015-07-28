#ifndef FLOATINGDAMAGE_HPP
#define FLOATINGDAMAGE_HPP

#include "Message.hpp"
#include "FloatingText.hpp"
class FloatingDamage: public FloatingText
{
private:

public:
	FloatingDamage();
	FloatingDamage(std::string iconName,sf::Font& font,double duration = 3,int len = -1,double offsetX = 0,double offsetY = 0);
	FloatingDamage(FloatingDamage &fdmg);

	FloatingDamage& operator=(int damageDone);
};

#endif