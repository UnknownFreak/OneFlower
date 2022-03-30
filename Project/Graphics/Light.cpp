#include "Light.hpp"

#include <Module/Globals.hpp>
#include <File/Resource/TextureLoader.hpp>

namespace Graphics
{
	Light::Light(const Core::Vector2f& thePos, const float& z, const float& lightRadii,
		const sf::Color& lightColor, const sf::Color& lightShaderColor) :
		Renderable({ thePos, lightRadii, lightRadii }), light(sf::PrimitiveType::Quads, 4), pos(thePos), lightColor(lightColor),
		lightShaderColor(lightShaderColor)
	{
		theTexture = Engine::GetModule<File::Resource::Texture::Loader>().requestTexture(Globals::LIGHT);
		light[0] = sf::Vertex({ pos.x, (pos.y + z * Globals::Z_OFFSET) }, lightColor, { 0, 0 });
		light[1] = sf::Vertex({ pos.x + lightRadii, (pos.y + z * Globals::Z_OFFSET) }, lightColor,
			{ 512, 0 });
		light[2] = sf::Vertex({ pos.x + lightRadii, (pos.y + z * Globals::Z_OFFSET) + lightRadii }, lightColor,
			{ 512, 512 });
		light[3] = sf::Vertex({ pos.x, (pos.y + z * Globals::Z_OFFSET) + lightRadii }, lightColor,
			{ 0, 512 });
	}

	void Light::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		auto origTex = states.texture;
		states.texture = theTexture.get();
		target.draw(light, states);
		states.texture = origTex;
	}
}