#ifdef _EDITOR_
#ifndef _UNITTESTS_
#include <vector>

#include <Core\EngineModule\EngineModuleManager.hpp>
#include <Editor\WorldEditorExtensions\WorldManagerAddons.hpp>
#include <Asset\AssetManagerCore.hpp>

#include <Core\GameVariableMapping.hpp>
#include <Core\Globals.hpp>

#include "EditorEvents.hpp"
#include "InteropHelper.hpp"

Core::String Editor::toString(System::String ^ str)
{
	return toString(str->ToCharArray());
}

Core::String Editor::toString(array<wchar_t>^ arr)
{
	std::wstring w;
	
	for each(wchar_t wc in arr)
		w.push_back(wc);
	
	return Engine::GetModule<Core::StringConverter>().toUtf8(w);
}

System::String^ Editor::toString(const Core::String & str)
{
	return gcnew System::String(Engine::GetModule<Core::StringConverter>().toUtf16(str).c_str());
}

EditorResources::Utils::ModDependencyList ^ Editor::Events::loadDependenciesInternal(Core::String mod)
{
	EditorResources::Utils::ModDependencyList^ depList = gcnew EditorResources::Utils::ModDependencyList();
	depList->Mod = gcnew System::String(mod.c_str());
	std::vector<Core::String> dep = Engine::GetModule<WorldManagerAddon>().getModDependencies(mod);
	
	for each (Core::String str in dep)
		depList->dependencies->Add(loadDependenciesInternal(str));
	
	return depList;
}

void Editor::Events::registerEvents()
{
	EditorEvents::onModEvent += gcnew System::EventHandler<EditorEvents::ModEventArgs^>(this, &Editor::Events::OnEditorEvent);
	EditorEvents::onObjectEvent += gcnew System::EventHandler<EditorEvents::ObjectEventArgs^>(this, &Editor::Events::OnGlobalVaraibleCreated);
	EditorEvents::onObjectEvent += gcnew System::EventHandler<EditorEvents::ObjectEventArgs^>(this, &Editor::Events::OnElementEvent);
	EditorEvents::onObjectSelectedEvent += gcnew System::EventHandler < EditorEvents::OnObjectSelectedEventArgs^ >(this, &Editor::Events::OnEditorZoneSelected);
	EditorEvents::onRequestGameVariableMapping += gcnew System::EventHandler<EditorEvents::GameVariableMappingEventArgs^>(this, &Editor::Events::OnVariableMappingRecieved);
}

void Editor::Events::OnEditorEvent(Object^, EditorEvents::ModEventArgs^ args)
{
	if (args->Type == EditorEvents::ModEventArgs::EventType::Saved)
		Engine::GetModule<WorldManagerAddon>().EditorSave();
	else if (args->Type == EditorEvents::ModEventArgs::EventType::Created)
	{
		Core::String s = toString(args->ModName);
		std::vector<Core::String> dependencies;

		for each (System::String^ str in args->Dependencies)
			dependencies.push_back(toString(str));

		Engine::GetModule<WorldManagerAddon>().newMod(s, dependencies, args->CreateMaster);
	}
	else if (args->Type == EditorEvents::ModEventArgs::EventType::Loaded)
	{
		Core::String s = toString(args->ModName);
		WorldManagerAddon& addon = Engine::GetModule<WorldManagerAddon>();
		addon.loadMod(s);
	}
	else if (args->Type == EditorEvents::ModEventArgs::EventType::Selected)
	{
		Core::String mod = toString(args->ModName);
		EditorResources::Utils::ModDependencyList^ depList = loadDependenciesInternal(mod);
		EngineEvents::DependencyListEventArgs ^ evt = gcnew EngineEvents::DependencyListEventArgs();
		
		evt->Dependencies = depList;
		EngineEvents::OnDependencyListEvent(evt);
	}
}

void Editor::Events::OnEditorZoneSelected(Object^ , EditorEvents::OnObjectSelectedEventArgs ^ args)
{
	if (args->SelectedType == EditorResources::Utils::EnumCollection::ObjectType::Zone)
	{
		WorldManagerAddon& addon = Engine::GetModule<WorldManagerAddon>();

		addon.EditorLoadZone(toString(args->ModOrigin), args->ID);

		while (addon.myWorldManager.isLoading())
		{
			// change this to some kind of indicator in the editor that we are loading, even though the editor game view shows it.
			Sleep(10);
			addon.myWorldManager.loadSome();
			//;Wait
		}
		EngineEvents::OnModFinishedLoadingEvent();
	}
}

void Editor::Events::OnGlobalVaraibleCreated(Object ^ , EditorEvents::ObjectEventArgs^ args)
{
	if (args->Flag == EditorResources::Utils::EnumCollection::ObjectFlag::Added)
	{
		Asset::AssetManager& am = Engine::GetModule<Asset::AssetManager>();

		if (args->Type == EditorResources::Utils::EnumCollection::ObjectType::IntVariable)
		{
			PrimitiveSaveable<int> var(System::Convert::ToInt32(((EditorResources::Dto::VariableDto^)args->Value)->Value), toString(args->Value->Name));
			var.fromMod = toString(args->Value->Origin);
			var.ID = args->Value->ID;
			am.getIntRequestor().add(var);
			Engine::GetModule<Globals>().longGlobals.insert({ toString(args->Value->Name), var.value });
		}
		else if (args->Type == EditorResources::Utils::EnumCollection::ObjectType::DoubleVariable)
		{
			PrimitiveSaveable<double> var(System::Convert::ToDouble(((EditorResources::Dto::VariableDto^)args->Value)->Value), toString(args->Value->Name));
			var.fromMod = toString(args->Value->Origin);
			var.ID = args->Value->ID;
			am.getDoubleRequestor().add(var);
			Engine::GetModule<Globals>().doubleGlobals.insert({ toString(args->Value->Name), var.value});
		}
		else if (args->Type == EditorResources::Utils::EnumCollection::ObjectType::StringVariable)
		{
			PrimitiveSaveable<Core::String> var(toString(((EditorResources::Dto::VariableDto^)args->Value)->Value), toString(args->Value->Name));
			var.fromMod = toString(args->Value->Origin);
			var.ID = args->Value->ID;
			am.getStringRequestor().add(var);
			Engine::GetModule<Globals>().stringGlobals.insert({ toString(args->Value->Name), var.value });
		}
	}
}

void Editor::Events::OnVariableMappingRecieved(Object ^ , EditorEvents::GameVariableMappingEventArgs ^ args)
{
	if (args->VariableToRequest == EditorEvents::GameVariableMappingEventArgs::Variable::Animation)
	{
		EngineEvents::AnimationVariableMappingEventArgs^ arg = gcnew EngineEvents::AnimationVariableMappingEventArgs();
		arg->AnimationVariable = toString(Engine::GetModule<GameVariableMapping>().getAnimationVariableName());
		EngineEvents::EngineOnSendVariableMapping(arg);
	}
}

void Editor::Events::OnElementEvent(Object ^ , EditorEvents::ObjectEventArgs ^ args)
{
	if (args->Type == EditorResources::Utils::EnumCollection::ObjectType::Element)
	{
		Asset::AssetManager& am = Engine::GetModule<Asset::AssetManager>();
		if (args->Flag == EditorResources::Utils::EnumCollection::ObjectFlag::Added)
		{
			Element var(toString(args->Value->Name));
			var.fromMod = toString(args->Value->Origin);
			var.ID = args->Value->ID;

			var.damageToUnknownType = ((EditorResources::Dto::ElementTypeDto^)args->Value)->DamageToUnknownType;
			for each (EditorResources::Dto::ElementTypeDto::ElementAttributeDto^ it in ((EditorResources::Dto::ElementTypeDto^)args->Value)->ElementAttribute)
			{
				var.elementAttributes.insert({ { toString(it->Origin), it->ID }, it->Modifier});
			}
			am.getElementRequestor().add(var);
		}
		else if (args->Flag == EditorResources::Utils::EnumCollection::ObjectFlag::Edited)
		{
			Element& elem = am.getElementRequestor().request(toString(args->Value->Origin), args->Value->ID);

			elem.name = toString(args->Value->Name);
			elem.damageToUnknownType = ((EditorResources::Dto::ElementTypeDto^)args->Value)->DamageToUnknownType;

			elem.elementAttributes.clear();
			for each (EditorResources::Dto::ElementTypeDto::ElementAttributeDto^ it in ((EditorResources::Dto::ElementTypeDto^)args->Value)->ElementAttribute)
			{
				elem.elementAttributes.insert({ { toString(it->Origin), it->ID }, it->Modifier });
			}
			elem.mode = ObjectSaveMode::EDIT;

		}
		else if (args->Flag == EditorResources::Utils::EnumCollection::ObjectFlag::Deleted)
		{
			Element& elem = am.getElementRequestor().request(toString(args->Value->Origin), args->Value->ID);
			if (elem.mode == ObjectSaveMode::REMOVE)
				elem.mode = ObjectSaveMode::EDIT;
			else
				elem.mode = ObjectSaveMode::REMOVE;
		}
	}
}

#endif
#endif
