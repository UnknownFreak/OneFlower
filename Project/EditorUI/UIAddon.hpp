#ifndef UIAddon_HPP
#define UIAddon_HPP
#include <Windows.h>
#include <string>
#include <map>
class GameObject;
class EditorGroup;
class BaseField;
	#pragma region Prototypes
	namespace EditorUI
	{
		namespace Field
		{
			void addField(BaseField* variable,EditorGroup* hwnd);
			void addGroup(EditorGroup*);
		}
		HWND addButton(HWND phWnd,std::string buttonDisplayName,int x,int y,int width,int height,int buttonID);
		HWND addTextbox(HWND phWnd,std::string textBoxName,int x,int y,int width,int height,int textboxID);
		HWND addLabel(HWND phWnd,std::string labelDisplay,int x,int y,int width,int height,int labelID);
		HWND addTextboxInt(HWND phWnd,std::string number,int x,int y,int width,int height,int textboxID);
		HWND addComponentGroup(HWND phWnd,std::string name,int x,int y,int width,int height,int groupID);
		HWND addEditor(HWND phWnd,std::string name,int x,int y,int width,int height,int groupID);
		
		
		RECT GetLocalCoordinates(HWND hWnd);
		void RecycleID(int i);
		int RequestID();
		void RedirectIOToConsole();
		void CompileComponents();
		extern std::map<std::string,std::map<std::string,std::string>> compiledClass;
	}
	#pragma endregion


#endif