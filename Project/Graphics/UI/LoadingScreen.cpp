#include "LoadingScreen.hpp"

#include <File/Resource/TextureLoader.hpp>

Graphics::UI::LoadingScreen::LoadingScreen() : UIContext(swizzle::input::Keys::KeyNone, "LoadingScreen", true)
{
	loadingScreenName = "Flower.png";
	//texture = Engine::GetModule<File::Resource::Texture::Loader>().requestTexture(loadingScreenName);
}

Graphics::UI::LoadingScreen::~LoadingScreen()
{
}

void Graphics::UI::LoadingScreen::readInput()
{
	return;
}

void Graphics::UI::LoadingScreen::render()
{
}

void Graphics::UI::LoadingScreen::onMouseHover(const Core::Vector2f&)
{
}
