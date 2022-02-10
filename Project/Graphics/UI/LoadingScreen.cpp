#include "LoadingScreen.hpp"

#include <File/Resource/TextureLoader.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

Graphics::UI::LoadingScreen::LoadingScreen() : UIContext(sf::Keyboard::Key::Unknown, "LoadingScreen", true)
{
	loadingScreenName = "Flower.png";
	texture = Engine::GetModule<TextureLoader>().requestTexture(loadingScreenName);
	loadingScreen.setTexture(*texture.get());
}

Graphics::UI::LoadingScreen::~LoadingScreen()
{
}

void Graphics::UI::LoadingScreen::readInput()
{
	return;
}

void Graphics::UI::LoadingScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(loadingScreen, states);
}

void Graphics::UI::LoadingScreen::onMouseHover(const Core::Vector2f&)
{
}
