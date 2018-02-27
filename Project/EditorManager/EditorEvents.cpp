#ifdef _EDITOR_
#ifndef _UNITTESTS_
#include <vector>

#include <Core\IEngineResource\EngineResourceManager.hpp>
#include <EditorManager\WorldEditorExtensions\WorldManagerAddons.hpp>
#include <AssetManager\AssetManagerCore.hpp>

#include <Core\Globals.hpp>

#include "EditorEvents.hpp"
#include "InteropHelper.hpp"


Core::String Editor::Events::toString(array<wchar_t>^ arr)
{
	std::wstring w;
	
	for each(wchar_t wc in arr)
		w.push_back(wc);
	
	return Engine::Get<Core::StringConverter>().toUtf8(w);
}

EditorResources::ModWindow::ModDependencyList ^ Editor::Events::loadDependenciesInternal(Core::String mod)
{
	EditorResources::ModWindow::ModDependencyList^ depList = gcnew EditorResources::ModWindow::ModDependencyList();
	depList->Mod = gcnew System::String(mod.c_str());
	std::vector<Core::String> dep = Engine::Get<WorldManagerAddon>().getModDependencies(mod);
	
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
	EditorResources::Functionality::EditorEvents::onOVariableCreatedEvent += gcnew EventHandler<EditorResources::Functionality::OnVariableCreatedEventArgs^>(this, &Editor::Events::OnGlobalVaraibleCreated);
}

void Editor::Events::OnEditorCreateMod(Object ^ sender, EditorResources::Functionality::NewModCreateEventArgs ^ args)
{
	Core::String s = toString(args->modName->ToCharArray());
	std::vector<Core::String> dependencies;
	
	for each (System::String^ str in args->dependencies)
		dependencies.push_back(toString(str->ToCharArray()));

	Engine::Get<WorldManagerAddon>().newMod(s, dependencies, (bool)args->createMaster);
}

void Editor::Events::OnEditorLoadMod(Object ^ sender, EditorResources::Functionality::ModLoadEventArgs ^ args)
{
	Core::String s = toString(args->modName->ToCharArray());
	WorldManagerAddon& addon = Engine::Get<WorldManagerAddon>();
	addon.loadMod(s);

	auto modfinishedloaded = gcnew EditorResources::Functionality::ModFinishedLoadedEventArgs();

	modfinishedloaded->ModName = args->modName;

	for each (auto v in addon.getAllDbZones())
	{
		auto zinfo = gcnew System::Tuple<System::String^, size_t, System::String^>(gcnew String(v.fromMod.c_str()), v.ID, gcnew String(v.name.c_str()));
		modfinishedloaded->zoneFiles->Add(zinfo);
	}

	EditorResources::Functionality::EditorEvents::onModFinishedLoading(nullptr, modfinishedloaded);
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

	WorldManagerAddon& addon = Engine::Get<WorldManagerAddon>();

	addon.EditorLoadZone(toString(args->ModOrigin->ToCharArray()), args->ZoneID);
	EditorResources::Functionality::EditorGetZoneInfoEvent ^evt = gcnew EditorResources::Functionality::EditorGetZoneInfoEvent();
	evt->Origin = args->ModOrigin;
	evt->Id = args->ZoneID;
	evt->ZoneName = args->ZoneName;

	std::vector<Core::String> v = addon.getExtraZoneInfo(toString(args->ModOrigin->ToCharArray()), args->ZoneID);
	
	evt->BackgroundPath = gcnew System::String(v[0].c_str());
	evt->LoadingScreenPath = gcnew System::String(v[1].c_str());
	evt->LoadingScreenMessage = gcnew System::String(v[2].c_str());
	
	EditorResources::Functionality::EditorEvents::onGetZoneInfoEvent(nullptr, evt);
	while (addon.myWorldManager.getIsLoading())
	{
		// change this to some kind of indicator in the editor that we are loading, even though the editor game view shows it.
		_sleep(20);
		//;Wait
	}

}

void Editor::Events::OnEditorSave(Object^ sender, EditorResources::Functionality::ModSaveEventArgs^ args)
{
	Engine::Get<WorldManagerAddon>().EditorSave();
}

void Editor::Events::OnGlobalVaraibleCreated(Object ^ sender, EditorResources::Functionality::OnVariableCreatedEventArgs ^ args)
{
	AssetManager& am = Engine::Get<AssetManager>();

	if (args->VariableType == EditorResources::Resources::NameValidator::ValidationType::Int)
	{
		PrimitiveSaveable<int> var(System::Convert::ToInt32(args->Value), toString(args->Name->ToCharArray()));
		var.fromMod = toString(args->Origin->ToCharArray());
		var.ID = args->ID;
		am.getIntRequestor().add(var);
		Engine::Get<Globals>().longGlobals.insert({ toString(args->Name->ToCharArray()), System::Convert::ToInt32(args->Value) });
	}
	else if (args->VariableType == EditorResources::Resources::NameValidator::ValidationType::Double)
	{
		PrimitiveSaveable<double> var(System::Convert::ToDouble(args->Value), toString(args->Name->ToCharArray()));
		var.fromMod = toString(args->Origin->ToCharArray());
		var.ID = args->ID;
		am.getDoubleRequestor().add(var);
		Engine::Get<Globals>().doubleGlobals.insert({ toString(args->Name->ToCharArray()), System::Convert::ToDouble(args->Value) });
	}
	else if (args->VariableType == EditorResources::Resources::NameValidator::ValidationType::String)
	{
		PrimitiveSaveable<Core::String> var(toString(args->Value->ToCharArray()), toString(args->Name->ToCharArray()));
		var.fromMod = toString(args->Origin->ToCharArray());
		var.ID = args->ID;
		am.getStringRequestor().add(var);
		Engine::Get<Globals>().stringGlobals.insert({ toString(args->Name->ToCharArray()), toString(args->Value->ToCharArray()) });
	}
}
#endif
#endif