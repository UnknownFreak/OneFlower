//#ifdef _DEBUG
//#ifndef ENGINEITEMCREATORWINDOW_HPP
//#define ENGINEITEMCREATORWINDOW_HPP
//#include <Windows.h>
//#include "../../../Vector.h"
//#include "EngineItemCreatorTypeField.hpp"
//#include "EngineItemCreatorImageField.hpp"
//#include "AttachmentPointDialog.hpp"
//#include "EffectEnchantDialog.hpp"
//class Item;
//class EngineItemCreator
//{
//public:
//	
//	HINSTANCE hInstance;
//
//	HWND hWnd;
//
//	Item* addItem();
//
//	void editItem(Item* itemToEdit);
//
//	~EngineItemCreator();
//	//EngineItemCreator() = default;
//	void start();
//
//	void show();
//	
//	void getSecondaryTypeChange();
//	void getCheckedStateChange();
//	void setTexturePath();
//	void setNextValidID();
//	void setInventoryIcon();
//	void setSprite();
//	std::string getInventoryIcon();
//
//	void UpdateImageField(HWND hWnd);
//
//	bool createItem();
//	void updateFields();
//	void updateSecondaryFields();
//	void setAttachmentPoints();
//	void setEffect();
//	void repaint();
//private:
//
//	DWORD_PTR panelDwRefData;
//
//	size_t ID = 0;
//
//	HWND setTexturePathHWnd;		//Button
//	HWND setTexturePathEditHWnd;	//Textfield
//	HWND setTexturePathLabelHWnd;	//Label
//
//	HWND itemNameHWnd;				//Textfield
//	HWND itemNameLabelHWnd;			//Label
//
//	HWND itemIDHWnd;				//Textfiel
//	HWND itemIDLabelHWnd;			//Label
//	HWND itemIDPrefixHWnd;			//Textfield
//	HWND itemIDButtonHWnd;			//Button
//
//	HWND itemToolTipHWnd;			//Textfield
//	HWND itemTooltipLabelHWnd;		//Label
//
//	HWND itemWeightHWnd;			//Textfield
//	HWND itemWeightLabelHWnd;		//Label
//
//	HWND itemPriceHWnd;				//Textfield
//	HWND itemPriceLabelHWnd;		//Label
//
//	HWND itemStackableHWnd;			//Checkbox
//
//	HWND itemTypeControl;			//Static
//	HWND itemCreateHWnd;			//Button
//
//	HWND infoTip;					//Label
//
//	HWND isTwoHanded;				//Checkbox
//
//	HWND defenseLabelHWnd;			//Label
//	HWND defenseHWnd;				//Textfield
//
//	HWND damageLabelHWnd;			//Label
//	HWND damageHWnd;				//Textfield
//
//	HWND bagslotLabelHWnd;			//Label
//	HWND bagslotHWnd;				//Textfield
//
//	HWND attachmentPointLabelHWnd;	//Label
//	HWND attachmentPointHWnd;		//Button
//
//	HWND effectEnchantLabelHWnd;	//Label
//	HWND effectEnchantHWnd;		//Button
//
//	std::string selected = "-1";
//	std::string secondaryTypeSelected = "-1";
//	EngineItemCreatorAttachmentPointDialog attachpoint;
//	EngineItemCreatorEnchantEffectDialog effects;
//	EngineItemCreatorTypeField itemtypes;
//	EngineItemCreatorTypeField secondaryType;
//	EngineItemCreatorImageField inventoryIconField;
//	EngineItemCreatorImageField itemSpriteField;
//	Vector2 size;
//	WNDCLASSEX wc;
//	LPCTSTR windowDefinedName;
//	char texturePath [256];
//};
//
//
//#endif
//#endif