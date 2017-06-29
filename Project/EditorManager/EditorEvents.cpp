#ifdef _EDITOR_
#include "EditorEvents.hpp"
#include <EditorManager\EditorCore.hpp>
#include <EditorManager\WorldEditorExtensions\WorldManagerAddons.hpp>
#include <iostream>

Core::String Editor::Events::toString(array<wchar_t>^ arr)
{
	array<wchar_t>^ wstr = arr;
	std::wstring w;
	
	for each(wchar_t wc in wstr)
		w.push_back(wc);
	
	return Core::Converter.toUtf8(w);
}

EditorResources::ModWindow::ModDependencyList ^ Editor::Events::loadDependenciesInternal(Core::String mod)
{
	EditorResources::ModWindow::ModDependencyList^ depList = gcnew EditorResources::ModWindow::ModDependencyList();
	depList->Mod = gcnew System::String(mod.c_str());
	std::vector<Core::String> dep;
	dep = Editor::addons.getModDependencies(mod);
	
	for each (Core::String str in dep)
		depList->dependencies->Add(loadDependenciesInternal(str));
	
	return depList;
}

void Editor::Events::registerEvents()
{
	EditorResources::Functionality::EditorEvents::onModCreate += gcnew EventHandler<EditorResources::Functionality::NewModCreateEventArgs^>(this, &Editor::Events::OnEditorCreateMod);
	EditorResources::Functionality::EditorEvents::onModLoad += gcnew EventHandler<EditorResources::Functionality::ModLoadEventArgs^>(this, &Editor::Events::OnEditorLoadMod);
	EditorResources::Functionality::EditorEvents::onModSelected += gcnew EventHandler<EditorResources::Functionality::ModFileSelectedEventArgs^>(this, &Editor::Events::OnEditorModFileSelected);
	EditorResources::Functionality::EditorEvents::onZoneSelectedEvent += gcnew EventHandler<EditorResources::Functionality::EditorZoneSelectedEventArgs^>(this, &Editor::Events::OnEditorZoneSelected);
	EditorResources::Functionality::EditorEvents::onModSave += gcnew EventHandler<EditorResources::Functionality::ModSaveEventArgs^>(this, &Editor::Events::OnEditorSave);
}

void Editor::Events::OnEditorCreateMod(Object ^ sender, EditorResources::Functionality::NewModCreateEventArgs ^ args)
{
	Core::String s = toString(args->modName->ToCharArray());
	std::vector<Core::String> dependencies;
	
	for each (System::String^ str in args->dependencies)
		dependencies.push_back(toString(str->ToCharArray()));

	Editor::addons.newMod(s, dependencies, (bool)args->createMaster);
}
void Editor::Events::OnEditorLoadMod(Object ^ sender, EditorResources::Functionality::ModLoadEventArgs ^ args)
{
	Core::String s = toString(args->modName->ToCharArray());
	Editor::addons.loadMod(s);

	auto modfinishedloaded = gcnew EditorResources::Functionality::ModFinishedLoadedEventArgs();

	for each (auto v in Editor::addons.myActualManager.EditorAllZones)
	{
		v.second.fromMod;
		auto zinfo = gcnew System::Tuple<System::String^, size_t, System::String^>(gcnew String(v.second.fromMod.c_str()), v.second.ID, gcnew String(v.second.name.c_str()));
		modfinishedloaded->zoneFiles->Add(zinfo);
	}

	EditorResources::Functionality::EditorEvents::onModFinishedLoading(nullptr, modfinishedloaded);
}

void Editor::Events::OnEditorModLoaded(Object ^ sender, EditorResources::Functionality::ModFinishedLoadedEventArgs ^ args)
{
	throw gcnew System::NotImplementedException();
}

void Editor::Events::OnEditorModFileSelected(Object^ sender, EditorResources::Functionality::ModFileSelectedEventArgs^ args)
{
	Core::String mod = toString(args->fileName->ToCharArray());
	EditorResources::ModWindow::ModDependencyList^ depList = loadDependenciesInternal(mod);
	EditorResources::Functionality::EngineOnModSelectedLoadedEventArgs ^evt = gcnew EditorResources::Functionality::EngineOnModSelectedLoadedEventArgs();
	evt->Dependencies = depList;
	EditorResources::Functionality::EditorEvents::EngineOnModSelectedLoaded(evt);
}

void Editor::Events::OnEditorZoneSelected(Object^ sender, EditorResources::Functionality::EditorZoneSelectedEventArgs^ args)
{
	Editor::addons.EditorLoadZone(toString(args->ModOrigin->ToCharArray()), args->ZoneID);
	while (Editor::addons.myActualManager.getIsLoading())
	{
		// change this to some kind of indicator in the editor that we are loading, even though the editor game view shows it.
		_sleep(20);
		//;Wait
	}

}

void Editor::Events::OnEditorSave(Object^ sender, EditorResources::Functionality::ModSaveEventArgs^ args)
{

	Editor::addons.EditorSave();

}
#endif