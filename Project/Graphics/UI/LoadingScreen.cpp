#include "LoadingScreen.hpp"

#include <module/resource/TextureLoader.hpp>

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

void Graphics::UI::LoadingScreen::onMouseHover(const glm::vec2&)
{
}

void Graphics::UI::LoadingScreen::updateFrame(const float& )
{
}

void Graphics::UI::LoadingScreen::render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>&, of::graphics::view::MVP&)
{
	render();
}
