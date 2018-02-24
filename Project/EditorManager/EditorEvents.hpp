#ifndef EditorEvents_HPP
#define EditorEvents_HPP
#ifdef _EDITOR_
#ifndef _UNITTESTS_
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
		void OnEditorModFileSelected(Object^ sender, EditorResources::Functionality::ModFileSelectedEventArgs^ args);

		void OnEditorZoneSelected(Object^ sender, EditorResources::Functionality::EditorZoneSelectedEventArgs^ args);

		void OnEditorSave(Object ^ sender, EditorResources::Functionality::ModSaveEventArgs^ args);

		void OnGlobalVaraibleCreated(Object ^ sender, EditorResources::Functionality::OnVariableCreatedEventArgs^ args);

	};
}
#endif
#endif
#endif