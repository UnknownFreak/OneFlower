#ifndef PARENT_WINDOW_WRAPPER_HPP
#define PARENT_WINDOW_WRAPPER_HPP

#ifdef _EDITOR_

#include "InteropHelper.hpp"

public ref class ParentWndWrapper : IWin32Window
{
	IntPtr^ m_Handle;
public:
	ParentWndWrapper(long pParent)
	{
		m_Handle = (IntPtr)pParent;
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