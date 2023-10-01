#include "DialogScreen.hpp"
#include <module/resource/TextureLoader.hpp>
#include <Input/InputHandler.hpp>
#include <Graphics/Dialog.hpp>

Graphics::UI::DialogScreen::DialogScreen() : UIContext(swizzle::input::Keys::KeyNone, "DialogScreen", true)
{
	// first quad is top dialog bar
	// second is the right side
	// third is the left side
	// fourth is the middle (text content)
	// fifth is the top right corner
	// sixth is the top left corner
	// 	                       
	//             ________________________
	//            /                        \
	//            |                        |
	//            |                        |
	//            |                        |
	//            |                        |


	//texture = Engine::GetModule<File::Resource::Texture::Loader>().requestTexture("DialogFramedummy.png", Globals::uiTexturePath);
	//
	//float size = 256*4;
	//float height = 64;
	//float x = 1920/2 - size/2;
	//float y = 1080-height-300;
	//
	//dialogFrame[0].position = { x, y };
	//dialogFrame[0].texCoords = { 0.f, 0.f };
	//dialogFrame[1].position = { x, y + height };
	//dialogFrame[1].texCoords = { 0.f, 64.f };
	//dialogFrame[2].position = { x + size, y + height };
	//dialogFrame[2].texCoords = { 256.f, 64.f };
	//dialogFrame[3].position = { x + size, y };
	//dialogFrame[3].texCoords = { 256.f, 0.f };
	//
	//f.loadFromFile("C:/Windows/Fonts/arial.ttf");
	//t.setFont(f);
	//t.setCharacterSize(12);
	//t.setPosition(5, 600);

}
Graphics::UI::DialogScreen::DialogScreen(Dialog* dialog) : DialogScreen()
{
	show(dialog);
}
Graphics::UI::DialogScreen::~DialogScreen()
{
}
void Graphics::UI::DialogScreen::toggleVisible()
{
	UIContext::toggleVisible();
	of::engine::GetModule<of::input::InputHandler>().enablePlayerMovement();
}
void Graphics::UI::DialogScreen::readInput()
{
}
void Graphics::UI::DialogScreen::readInput(const Enums::InteractionOption& nav)
{
	if (dialog->navigate(nav) == Enums::DialogStatus::Close)
		toggleVisible();
	else
	{
		t = "";
		auto op = dialog->getDialogOptions();
		for (auto s : op)
		{
			t += s + "\n";
		}
	}
	t += "\n" + dialog->getCurrentText();
}

void Graphics::UI::DialogScreen::show(Dialog* diag)
{
	dialog = diag;
	dialog->reset();
	visible = true;
	of::engine::GetModule<of::input::InputHandler>().disablePlayerMovement();
	t = dialog->getCurrentText();

}

void Graphics::UI::DialogScreen::render()
{
	if (visible)
	{
		//const sf::Texture* before = states.texture;
		//states.texture = texture.get();
		//target.draw(dialogFrame, states);
		//states.texture = before;
		//target.draw(t, states);
	}
}

void Graphics::UI::DialogScreen::onMouseHover(const glm::vec2&)
{
}
