#ifndef STATS_HPP
#define STATS_HPP

#include "UIContext.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Helpers/String.hpp>

namespace Graphics::UI
{

	class Stats : public Graphics::UI::UIContext
	{
		sf::Font f;
		sf::Text t;

		float minFrame;
		float maxFrame;
		float mean[50];

		unsigned counterMax = 1;
		unsigned counter = 0;

		float mFrame;
		float mFps;
		const Core::String text;
		sf::Clock mClock;
		sf::Clock fpsPrintOut;
		sf::Time previous;
		sf::Time current;
	public:
		Stats(const Core::String text = "FPS", float x = 0.f, float y = 0.f) : UIContext(sf::Keyboard::F3, text, false), mFrame(0.f), mFps(0.f), text(text), minFrame(1000000.f), maxFrame(0.f) {
			f.loadFromFile("C:/Windows/Fonts/arial.ttf");
			t.setFont(f);
			t.setCharacterSize(12);
			t.setPosition(x, y);
			previous = current = mClock.getElapsedTime();
		}

		Stats(const Stats& copy) : Stats(copy.text, copy.t.getPosition().x, copy.t.getPosition().y)
		{
		}

		void reset()
		{
			mClock.restart();
		}
		void update()
		{

			{
				current = mClock.getElapsedTime();
				mFps = 1.f / (current.asSeconds() - previous.asSeconds());
				previous = current;
				if (mFps > maxFrame)
					maxFrame = mFps;
				if (mFps < minFrame && mFps > 0)
					minFrame = mFps;
				mean[counter++] = mFps;
				counterMax++;
				if (counterMax > 50)
					counterMax = 50;
				if (counterMax < 0)
					counterMax = 0;
				if (counter > 50)
					counter = 0;
			}

		}
		void print()
		{
			{
				float avg = 0.f;
				for (unsigned c = 0; c < counterMax; c++)
					avg += mean[c];

				avg /= counterMax;
				t.setString(text + ": " + std::to_string(mFps) + "\nmin: " + std::to_string(minFrame) + "\nmax: " + std::to_string(maxFrame) + "\navg: " + std::to_string(avg) + "\nms: " + std::to_string(1 / avg * 1000));
				fpsPrintOut.restart();
			}
		}

		// Inherited via Drawable
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			if (!visible)
				return;
			target.draw(t, states);
		}

		// Inherited via UIContext
		virtual void readInput() override {};

		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f&) override {};
	};
}

#endif 
