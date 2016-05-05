//#ifdef _DEBUG
//#include "EngineItemCreatorImageField.hpp"
//#include <SFML\Graphics\Texture.hpp>
//#include "../../../Game/Gfx.h"
//#include "../../../Engine.hpp"
//#include "../../../Game/Item/Item.hpp"
//unsigned int EngineItemCreatorImageField::isRegistered = 0;
//
//LRESULT CALLBACK WndProcImageField(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
//EngineItemCreatorImageField::~EngineItemCreatorImageField()
//{
//	DestroyWindow(panel);
//	isRegistered--;
//	if (!isRegistered)
//	{
//		UnregisterClass("ImageView", hInstance);
//	}
//}
//
//EngineItemCreatorImageField::EngineItemCreatorImageField() : sprite(), imagePreview(), attachPointSprite()
//{
//}
//void EngineItemCreatorImageField::start(HWND hWnd, HINSTANCE hInst, Vector2 pos, Vector2 size, HMENU ID, std::string labelName)
//{
//	hInstance = hInst;
//	
//	windowDefinedName = "ImageView";
//
//	wc.lpszClassName = windowDefinedName;
//	wc.lpfnWndProc = WndProcImageField;						// This function is called by windows
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.hIcon = NULL;
//	wc.hIconSm = NULL;
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.lpszMenuName = NULL;													// No menu
//	wc.cbClsExtra = 0;														// No extra bytes after the window class
//	wc.cbWndExtra = 0;														// structure or the window instance
//	wc.hbrBackground = HBRUSH(COLOR_BTNFACE + 1);
//
//	if (isRegistered == 0)
//		if (RegisterClassEx(&wc))
//			isRegistered = 1;
//		else;
//	else
//		isRegistered++;
//	panel = CreateWindowEx(WS_EX_TRANSPARENT, "ImageView", " ", WS_CHILD | WS_VISIBLE | WS_BORDER, pos.x, pos.y, size.x > 170 ? size.x : 170 , size.y + 40, hWnd,NULL, hInstance,NULL);
//	itemIconLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", labelName.c_str(), WS_CHILD | WS_VISIBLE, 2, 0, 100, 20, panel, NULL, hInstance, NULL);
//	itemIconHWnd = CreateWindowEx(0, "EDIT", "Texturename", WS_CHILD | WS_VISIBLE | WS_BORDER, 2, 20, 140, 20, panel, ID+1, hInstance, NULL);
//	itemIconFileSelectHWnd = CreateWindowEx(0, "BUTTON", "ok", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 147, 20, 22, 20, panel, ID, hInstance, NULL);
//	itemIconPreviewHWnd = CreateWindowEx(0, "STATIC", "", WS_CHILD | WS_VISIBLE, 0, 40, size.x, size.y, panel, NULL, hInstance, NULL);
//
//	imagePreview.create(itemIconPreviewHWnd);
//	attachPointText.setCharacterSize(12);
//}
//std::string EngineItemCreatorImageField::getTextureName()
//{
//	char ch[128];
//	SendMessage(itemIconHWnd, WM_GETTEXT, 128, (LPARAM)ch);
//	return std::string(ch);
//}
//void EngineItemCreatorImageField::drawImage(std::string str)
//{
//	sprite.setTexture(*Engine::Graphic.requestTexture(str),true);
//	SendMessage(itemIconHWnd, WM_SETTEXT, NULL, (LPARAM)str.c_str());
//	imagePreview.clear(sf::Color(64,64,192));
//	imagePreview.draw(sprite);
//
//	for (std::map<std::string, Vector2>::iterator it = attachmentPoints.begin(); it != attachmentPoints.end(); it++)
//	{
//		attachPointSprite.setPosition(it->second.x-8, it->second.y-8);
//		imagePreview.draw(attachPointSprite);
//		attachPointText.setString(it->first);
//		attachPointText.setPosition(it->second.x + 8, it->second.y);
//		imagePreview.draw(attachPointText);
//	}
//	imagePreview.display();
//}
//bool EngineItemCreatorImageField::hasTexture()
//{
//	return sprite.getTexture() != NULL;
//}
//void EngineItemCreatorImageField::setAttachmentPoints(std::map<std::string, Vector2> attachpoint)
//{
//	attachmentPoints = attachpoint;
//	if (attachPointSprite.getTexture() == NULL)
//		attachPointSprite.setTexture(*Engine::Graphic.requestTexture("attachmentpoint.png"));
//	if (attachPointText.getFont() == NULL)
//		attachPointText.setFont(*Engine::Graphic.font.requestFont("arial.ttf"));
//}
//void EngineItemCreatorImageField::redraw()
//{
//	if (sprite.getTexture() != NULL)
//	{
//		imagePreview.clear(sf::Color(64, 64, 192));
//		imagePreview.draw(sprite);
//		for (std::map<std::string, Vector2>::iterator it = attachmentPoints.begin(); it != attachmentPoints.end(); it++)
//		{
//			attachPointSprite.setPosition(it->second.x-8, it->second.y-8);
//			imagePreview.draw(attachPointSprite);
//			attachPointText.setString(it->first);
//			attachPointText.setPosition(it->second.x + 8, it->second.y);
//			imagePreview.draw(attachPointText);
//		}
//		imagePreview.display();
//	}
//}
//void EngineItemCreatorImageField::enable(bool value)
//{
//	if (value)
//	{
//		EnableWindow(panel, TRUE);
//		EnableWindow(itemIconHWnd, TRUE);
//		EnableWindow(itemIconFileSelectHWnd, TRUE);
//		EnableWindow(itemIconPreviewHWnd, TRUE);
//	}
//	else
//	{
//		EnableWindow(panel, FALSE);
//		EnableWindow(itemIconHWnd, FALSE);
//		EnableWindow(itemIconFileSelectHWnd, FALSE);
//		EnableWindow(itemIconPreviewHWnd, FALSE);
//	}
//}
//LRESULT CALLBACK WndProcImageField(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	if (msg == WM_COMMAND || msg == WM_NOTIFY)
//		SendMessage(GetParent(hwnd), msg, wParam, lParam);
//	return DefWindowProc(hwnd, msg, wParam, lParam);
//}
//
//#endif