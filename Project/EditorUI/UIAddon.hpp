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
			void addField(BaseField* variable,EditorGroup* hWnd,int xExtra,int yExtra);
			void addGroup(EditorGroup*);
		}
		
		RECT GetLocalCoordinates(HWND hWnd);
		RECT GetClientCoordinates(HWND hWnd);
		void RedirectIOToConsole();
		void CompileComponents();
		extern std::map<std::string,std::map<std::string,std::string>> compiledClass;
	}
	#pragma endregion


#endif