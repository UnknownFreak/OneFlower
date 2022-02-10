#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class RenderTextureDrawCallCount : public sf::RenderTexture
{
	sf::Font f;
	unsigned drawCount;

public:
	sf::Text t;

	RenderTextureDrawCallCount() : sf::RenderTexture(), drawCount(0)
	{
		f.loadFromFile("C:/Windows/Fonts/arial.ttf");
		t.setFont(f);
		t.setCharacterSize(12);
		t.setPosition(20, 2);
		t.setOutlineColor(sf::Color::White);
	}

	void draw(const sf::Drawable& d, const sf::RenderStates& states = sf::RenderStates::Default)
	{
		drawCount++;
		sf::RenderTexture::draw(d, states);
	}

    void draw(const sf::Vertex* vertices, std::size_t vertexCount,
        sf::PrimitiveType type, const sf::RenderStates& states = sf::RenderStates::Default)
    {
        drawCount++;
        sf::RenderTexture::draw(vertices, vertexCount, type, states);
    }
    void draw(const sf::VertexBuffer& vertexBuffer, const sf::RenderStates& states = sf::RenderStates::Default)
    {
        drawCount++;
        sf::RenderTexture::draw(vertexBuffer, states);
    }

	void draw(const sf::VertexBuffer& vertexBuffer, std::size_t firstVertex, std::size_t vertexCount,
		const sf::RenderStates& states = sf::RenderStates::Default)
	{
		drawCount++;
		sf::RenderTexture::draw(vertexBuffer, firstVertex, vertexCount, states);
	}

	void display()
	{
		t.setString("Visible draws: " + std::to_string(drawCount));
		sf::RenderTexture::display();
	}

	void clear(const sf::Color& color=sf::Color(0,0,0,255))
	{
		sf::RenderTexture::clear(color);
		drawCount = 0;
	}

};