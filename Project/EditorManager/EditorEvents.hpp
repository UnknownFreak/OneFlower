#ifndef EditorEvents_HPP
#define EditorEvents_HPP

namespace Editor
{
	ref class Events
	{
	public:

		void registerEvents();

		void OnEditorCreateMod(Object^ sender, EditorResources::Functionality::NewModCreateEventArgs^ args);
		void OnEditorLoadMod(Object^ sender, EditorResources::Functionality::ModLoadEventArgs^ args);
		void OnEditorModLoaded(Object^ sender, EditorResources::Functionality::ModFinishedLoadedEventArgs^ args);
	};
}

#endif