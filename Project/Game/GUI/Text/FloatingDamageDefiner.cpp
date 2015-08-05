#include "FloatingDamage.hpp"
#include <iostream>
FloatingDamage::FloatingDamage(std::string iconName,sf::Font& font,double duration,int len,double offsetX,double offsetY): FloatingText(iconName,font,true,duration,len,offsetX,offsetY)
{
}
FloatingDamage::FloatingDamage(FloatingDamage& fdmg) : FloatingText(fdmg.iconName,fdmg.font,fdmg.drawIcon,fdmg.duration,fdmg.maxLength,fdmg.offset.x,fdmg.offset.y)
{
	setColor(fdmg.color);
}

FloatingDamage& FloatingDamage::operator=(int damageDone)
{
	//Test stuffs
	if(damageDone < 0)
		createBody("Miss");
	else
		createBody(std::to_string(damageDone));

	return *this;
}