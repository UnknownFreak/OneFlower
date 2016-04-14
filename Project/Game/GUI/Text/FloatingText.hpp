#ifndef FLOATINGTEXT_HPP
#define FLOATINGTEXT_HPP

#include "Message.hpp"
#include <string>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics.hpp>
#include <exception>
#include "../../../Vector.h"
namespace GUI
{
	namespace Text
	{
		class FloatingText : public Message
		{
		public:

			/*
			Variables
			//*/
			bool drawIcon;
			std::string iconName;
			sf::Sprite iconSprite;
			std::map<int, std::pair<sf::Sprite, Vector2>> icons;
			Vector2 offset;
			/*
			Constructor
			//*/
			FloatingText(std::string iconName, sf::Font& font, bool drawIcon = true, double duration = 3, int len = -1, double offsetX = 0, double offsetY = 0);
			FloatingText(const FloatingText& ft);
			FloatingText();
			virtual ~FloatingText() = default;
			/*
			Functions
			//*/
			void move(double x, double y);
			void setPosition(double x, double y);
			void setIcon(std::string name);
			void draw();
			void draw(sf::RenderWindow& myrender);
			void drawCrop(sf::IntRect area);
			void setOffset(double x, double y);

			int iconFormat(std::pair<sf::Text, bool>& pair, std::vector<std::string>& iit, int iterpos) override;

			FloatingText& operator=(std::string info);

		protected:

		private:
			template<class Archive>
			friend void save(Archive& ar, const GUI::Text::FloatingText& ft);
			template<class Archive>
			friend void load(Archive& ar, GUI::Text::FloatingText& ft);
		};

		class MissingIconException : public std::exception
		{
			sf::Sprite tmp;
		public:
			MissingIconException(sf::Sprite& sprite);
			//	~MissingIconException(void);
			const sf::Texture* what();
		};
	}
}
#endif