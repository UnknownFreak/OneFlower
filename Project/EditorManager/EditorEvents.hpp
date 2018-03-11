#ifndef EditorEvents_HPP
#define EditorEvents_HPP
#ifdef _EDITOR_
#ifndef _UNITTESTS_

#include <AssetManager\Database\DatabaseIndex.hpp>
#include <AssetManager\ObjectSaveMode.hpp>

#include <Core/String.hpp>

#define EditorEvents_old EditorResources::Functionality::EditorEvents_old
#define EngineEvents EditorResources::Functionality::EngineEvents
#define EditorEvents EditorResources::Functionality::EditorEvents

namespace Editor
{
	ref class Events
	{

		EditorResources::Utils::ModDependencyList^ loadDependenciesInternal(Core::String mod);
	public:

		void registerEvents();

		void OnEditorCreateMod(Object^ sender, EditorResources::Functionality::NewModCreateEventArgs^ args);
		void OnEditorLoadMod(Object^ sender, EditorResources::Functionality::ModLoadEventArgs^ args);
		void OnEditorModFileSelected(Object^ sender, EditorResources::Functionality::ModFileSelectedEventArgs^ args);

		void OnEditorZoneSelected(Object^ sender, EditorResources::Functionality::EditorZoneSelectedEventArgs^ args);

		void OnEditorSave(Object ^ sender, EditorResources::Functionality::ModSaveEventArgs^ args);

		void OnGlobalVaraibleCreated(Object ^ sender, EditorResources::Functionality::OnVariableCreatedEventArgs^ args);

		void OnVariableMappingRecieved(Object^ sender, EditorEvents::GameVariableMappingEventArgs^ args);
	};

	Core::String toString(System::String^ str);
	Core::String toString(array<wchar_t>^ arr);
	System::String^ toString(const Core::String& str);

	void onObjectLoaded(const Core::String Origin, const size_t ID, const Core::String Name, const ObjectSaveMode mode, const DatabaseIndex::ObjectTypeEnum type, const Core::String value);
}
#endif
#endif
#endif