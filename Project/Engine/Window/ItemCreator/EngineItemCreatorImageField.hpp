//#ifdef _DEBUG
//#ifndef ENGINEITEMCREATORIMAGEFIELD_HPP
//#define ENGINEITEMCREATORIMAGEFIELD_HPP
//#include <Windows.h>
//#include "../../../Vector.h"
//#include "../../Resource.h"
//#include <SFML\Graphics\Sprite.hpp>
//#include <SFML\Graphics\RenderWindow.hpp>
//#include <SFML\Graphics\Text.hpp>
//class EngineItemCreatorImageField
//{
//
//public:
//	EngineItemCreatorImageField();
//	~EngineItemCreatorImageField();
//	void start(HWND parent, HINSTANCE hInstance, Vector2 pos, Vector2 size, HMENU ButtonID, std::string labelName);
//
//	sf::RenderWindow imagePreview;
//	void drawImage(std::string image);
//	std::string getTextureName();
//	static unsigned int isRegistered;
//	HWND panel;
//	void enable(bool value);
//	void redraw();
//	void setAttachmentPoints(std::map<std::string, Vector2> attachmentPoints);
//	bool hasTexture();
//private:
//
//
//	std::map<std::string,Vector2> attachmentPoints;
//
//	WNDCLASSEX wc;
//	HINSTANCE hInstance;
//
//	sf::Sprite sprite;
//	sf::Sprite attachPointSprite;
//	sf::Text attachPointText;
//
//	HWND itemIconLabelHWnd;			//Label
//	HWND itemIconFileSelectHWnd;	//Button
//	HWND itemIconHWnd;				//Textfield
//	HWND itemIconPreviewHWnd;		//PictureControl
//
//	LPCTSTR windowDefinedName;
//
//};
//
//#endif
//#endif