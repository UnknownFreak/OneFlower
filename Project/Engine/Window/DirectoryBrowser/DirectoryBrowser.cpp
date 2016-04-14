//#ifdef _DEBUG
//#include "DirectoryBrowser.hpp"
//#include <ShlObj.h>
//
//char DirectoryBrowser::windowDefaultDirectory[256];
//LRESULT CALLBACK DirectoryBrowser::DirectoryBrowserCallback(HWND hWnd, UINT msg, LPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//		case BFFM_INITIALIZED:
//		{
//			if (lParam)
//			{
//				SendMessage(hWnd, BFFM_SETSELECTION, TRUE, lParam);
//			}
//		}
//	}
//
//	return 0; // The function should always return 0.
//}
//void DirectoryBrowser::init()
//{
//	GetCurrentDirectory(128, windowDefaultDirectory);
//}
//void DirectoryBrowser::setDirectory(HWND parent, LPSTR path)
//{
//	BOOL retval;
//	CoInitialize(NULL);
//	BROWSEINFO fileToOpen = { 0 };
//	LPITEMIDLIST filepath = 0;
//	fileToOpen.hwndOwner = parent;
//	fileToOpen.ulFlags = BIF_VALIDATE | 64;
//	fileToOpen.lpszTitle = "Select Texture Folder";
//	fileToOpen.lParam = (LPARAM)windowDefaultDirectory;
//	fileToOpen.lpfn = (BFFCALLBACK)DirectoryBrowserCallback;
//	fileToOpen.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
//	filepath = SHBrowseForFolder(&fileToOpen);
//	if (filepath != NULL)
//	{
//		retval = SHGetPathFromIDList(filepath, path);
//		CoTaskMemFree(filepath);
//	}
//	else
//	{
//		retval = FALSE;
//	}
//	CoUninitialize();
//}
//#endif