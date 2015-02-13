#ifndef FLOATINGDAMAGE_HPP
#define FLOATINGDAMAGE_HPP

#include "Message.hpp"
#include "FloatingText.hpp"
class FloatingDamage : public FloatingText
{
private:

public:
	FloatingDamage();
	FloatingDamage(std::string iconName, sf::Font& font, double duration = 3, int len = -1, int offsetX = 0, int offsetY = 0);
	FloatingDamage(FloatingDamage &fdmg);
	~FloatingDamage();

	FloatingDamage& operator=(int damageDone);

};

#endif