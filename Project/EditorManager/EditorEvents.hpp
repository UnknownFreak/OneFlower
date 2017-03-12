#ifndef EditorEvents_HPP
#define EditorEvents_HPP
#include <Core/String.hpp>

namespace Editor
{
	ref class Events
	{
		Core::String toString(array<wchar_t>^ arr);
		EditorResources::ModWindow::ModDependencyList^ loadDependenciesInternal(Core::String mod);
	public:

		void registerEvents();

		void OnEditorCreateMod(Object^ sender, EditorResources::Functionality::NewModCreateEventArgs^ args);
		void OnEditorLoadMod(Object^ sender, EditorResources::Functionality::ModLoadEventArgs^ args);
		void OnEditorModLoaded(Object^ sender, EditorResources::Functionality::ModFinishedLoadedEventArgs^ args);
		void OnEditorModFileSelected(Object^ sender, EditorResources::Functionality::ModFileSelectedEventArgs^ args);
	};
}

#endif