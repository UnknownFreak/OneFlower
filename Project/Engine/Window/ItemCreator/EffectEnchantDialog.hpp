#ifdef _DEBUG
#ifndef	EFFECT_ENCHANT_DIALOG_HPP
#define EFFECT_ENCHANT_DIALOG_HPP

#include <windows.h>
class EngineItemCreatorEnchantEffectDialog
{
public:
	~EngineItemCreatorEnchantEffectDialog();
	EngineItemCreatorEnchantEffectDialog();
	static LRESULT CALLBACK WndProcAttachment(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void show(HWND hWndParent, HINSTANCE hInst);
	void clearEffect();
private:

	HWND hWnd;
	WNDCLASSEX wc;
	HINSTANCE hInstance;
	LPCTSTR windowDefinedName;
	static unsigned int registered;

};

#endif
#endif