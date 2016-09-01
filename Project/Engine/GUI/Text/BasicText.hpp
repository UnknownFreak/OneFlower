#ifndef	BASICTEXT_HPP
#define BASICTEXT_HPP

#include<SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include "../../../Vector.h"

namespace GUI
{
	class BasicText : public sf::Drawable
	{
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates renderstates) const;
		// used to save the text
		sf::String message;
		Vector2 pos;
		sf::Text text;
	public:

		void setPosition(Vector2 position);
		void setCharacterSize(unsigned int characterSize);

		BasicText(sf::Font& font, sf::String message, Vector2 position, unsigned int characterSize = 18);
		BasicText(const BasicText& copy);
		BasicText& operator=(const BasicText& right);

		template<class Archive>
		void save(Archive& ar, const BasicText& myText);

		template<class Archive>
		void load(Archive& ar, BasicText& myText);
		
	};
}

#endif