//#ifdef _DEBUG
//
//#include "EngineItemCreatorTypeField.hpp"
//#include "../../Resource.h"
//void EngineItemCreatorTypeField::start(HWND parent, HINSTANCE hInstance, Vector2 pos, Vector2 size, size_t ID, std::vector<std::string> _items)
//{
//	items = _items;
//	panel = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", " ItemType", WS_CHILD | WS_VISIBLE | SS_SUNKEN, pos.x, pos.y, size.x, size.y, parent, (HMENU)ID, hInstance, NULL);
//	defID = ID;
//	for (size_t i = 0; i < items.size(); i++)
//		radiobuttons.push_back(CreateWindowEx(0, "BUTTON", items[i].c_str(), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 5, i * 20 + 18, 100, 20, panel, (HMENU)(ID + 1 + i), hInstance, NULL));
//	if (items.size() != 0)
//		SendMessage(radiobuttons.at(radiobuttons.size()-1), BM_SETCHECK, BST_CHECKED, NULL);
//}
//void EngineItemCreatorTypeField::setText(std::string text)
//{
//	SendMessage(panel, WM_SETTEXT, NULL, (LPARAM)text.c_str());
//}
//std::string EngineItemCreatorTypeField::getCheckedType()
//{
//	for (size_t i = 0; i < items.size(); i++)
//	{
//		if (IsDlgButtonChecked(panel, int(defID + i + 1)) == BST_CHECKED)
//			return items[i];
//	}
//	return "Undefined";
//}
//size_t EngineItemCreatorTypeField::getRadiobuttonCount()
//{
//	return items.size();
//}
//void EngineItemCreatorTypeField::enable(bool value)
//{
//	EnableWindow(panel, value);
//}
//
//void EngineItemCreatorTypeField::setItems(std::vector<std::string> item)
//{
//	for (std::vector<HWND>::iterator it = radiobuttons.begin(); it != radiobuttons.end(); it++)
//	{
//		DestroyWindow(*it);
//	}
//	radiobuttons.clear();
//	items = item;
//	for (size_t i = 0; i < items.size(); i++)
//		radiobuttons.push_back(CreateWindowEx(0, "BUTTON", items[i].c_str(), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 5, i * 20 + 18, 100, 20, panel, (HMENU)(defID + 1 + i), (HINSTANCE)GetWindowLong(panel, GWL_HINSTANCE), NULL));
//	if (items.size() != 0)
//		SendMessage(radiobuttons.at(radiobuttons.size() - 1), BM_SETCHECK, BST_CHECKED, NULL);
//}
//#endif