#ifndef PARENT_WINDOW_WRAPPER_HPP
#define PARENT_WINDOW_WRAPPER_HPP

#ifdef _EDITOR_
#ifndef _UNITTESTS_
#include "InteropHelper.hpp"

public ref class ParentWndWrapper : System::Windows::Forms::IWin32Window
{
	System::IntPtr^ m_Handle;
public:
	ParentWndWrapper(long pParent)
	{
		m_Handle = (System::IntPtr)pParent;
	}

	// Inherited via IWin32Window
	virtual property System::IntPtr Handle
	{
		System::IntPtr get()
		{
			return *m_Handle;
		}
	}
};
#endif
#endif
#endif