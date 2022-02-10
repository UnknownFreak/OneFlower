#pragma once

#include <Graphics/Renderable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Graphics
{
	class Light : public Renderable
	{
		std::shared_ptr<sf::Texture> theTexture;
		float z;
		Core::Vector2f pos;
		sf::VertexArray light;
		sf::Color lightColor;
	public:
		sf::Color lightShaderColor;

		Light(const Core::Vector2f& thePos, const float& z, const float& lightRadii,
			const sf::Color& lightColor, const sf::Color& lightShaderColor);

		// Inherited via Renderable
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}
