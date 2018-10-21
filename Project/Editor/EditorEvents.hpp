#ifndef EditorEvents_HPP
#define EditorEvents_HPP
#ifdef _EDITOR_
#ifndef _UNITTESTS_

#include <Asset\DatabaseIndex.hpp>
#include <Asset\Database\DatabaseObjects.hpp>
#include <Asset\ObjectSaveMode.hpp>

#include <Asset\PrimitiveSaveable.hpp>

#include <Core/String.hpp>

#include <Core/EngineModule/EngineModuleManager.hpp>
#include <Core/Logger.hpp>

#include <Asset/Element.hpp>
#include <Asset/Language.hpp>

#define EditorEvents_old EditorResources::Functionality::EditorEvents_old
#define EngineEvents EditorResources::Functionality::EngineEvents
#define EditorEvents EditorResources::Utils::EditorEvents

namespace Editor
{
	ref class Events
	{

		EditorResources::Utils::ModDependencyList^ loadDependenciesInternal(Core::String mod);
	public:

		void registerEvents();

		void OnEditorEvent(Object^ sender, EditorEvents::ModEventArgs^ args);

		void OnEditorZoneSelected(Object^ sender, EditorEvents::OnObjectSelectedEventArgs^ args);

		void OnGlobalVaraibleCreated(Object ^ sender, EditorEvents::ObjectEventArgs^ args);

		void OnVariableMappingRecieved(Object^ sender, EditorEvents::GameVariableMappingEventArgs^ args);

		void OnElementEvent(Object^ sender, EditorEvents::ObjectEventArgs ^args);

	};

	Core::String toString(System::String^ str);
	Core::String toString(array<wchar_t>^ arr);
	System::String^ toString(const Core::String& str);

	inline void onObjectLoaded(const Core::String Origin, const size_t ID, const Core::String Name, const ObjectSaveMode mode, const DatabaseIndex::ObjectTypeEnum type, void* value)
	{
		EditorEvents::ObjectEventArgs^args = gcnew EditorEvents::ObjectEventArgs();

		switch (mode)
		{
		case ObjectSaveMode::ADD:
			args->Flag = EditorResources::Utils::EnumCollection::ObjectFlag::Added;
			break;
		case ObjectSaveMode::EDIT:
			args->Flag = EditorResources::Utils::EnumCollection::ObjectFlag::Edited;
			break;
		case ObjectSaveMode::REMOVE:
			args->Flag = EditorResources::Utils::EnumCollection::ObjectFlag::Deleted;
			break;
		default:
			args->Flag = EditorResources::Utils::EnumCollection::ObjectFlag::Default;
		}

		switch (type)
		{
		case DatabaseIndex::ObjectTypeEnum::Zone:
		case DatabaseIndex::ObjectTypeEnum::DBZone:
			args->Type = EditorResources::Utils::EnumCollection::ObjectType::Zone;
			args->Value = gcnew EditorResources::Dto::ZoneDto();
			((EditorResources::Dto::ZoneDto^)args->Value)->Background = toString(((Database::Zone*)value)->background);
			((EditorResources::Dto::ZoneDto^)args->Value)->LoadingScreen = toString(((Database::Zone*)value)->loadingScreen);
			((EditorResources::Dto::ZoneDto^)args->Value)->LoadingScreenMessage = toString(((Database::Zone*)value)->loadingScreenMessage);
			break;
		case DatabaseIndex::ObjectTypeEnum::Prefab:
			args->Type = EditorResources::Utils::EnumCollection::ObjectType::GameObject;
			args->Type = EditorResources::Utils::EnumCollection::ObjectType::GameObject;
			break;
		case DatabaseIndex::ObjectTypeEnum::Quest:
			args->Type = EditorResources::Utils::EnumCollection::ObjectType::Quest;
			break;
		case DatabaseIndex::ObjectTypeEnum::Item:
			args->Type = EditorResources::Utils::EnumCollection::ObjectType::Item;
			break;
		case DatabaseIndex::ObjectTypeEnum::Model:
			args->Type = EditorResources::Utils::EnumCollection::ObjectType::Model;
			break;
		case DatabaseIndex::ObjectTypeEnum::TextureMap:
			args->Type = EditorResources::Utils::EnumCollection::ObjectType::TextureMap;
			break;
		case DatabaseIndex::ObjectTypeEnum::PrimitiveInt:
			args->Type = EditorResources::Utils::EnumCollection::ObjectType::IntVariable;
			args->Value = gcnew EditorResources::Dto::VariableDto();
			((EditorResources::Dto::VariableDto^)args->Value)->Value = toString(((PrimitiveSaveable<int>*)value)->getValue());
			break;
		case DatabaseIndex::ObjectTypeEnum::PrimitiveDouble:
			args->Type = EditorResources::Utils::EnumCollection::ObjectType::DoubleVariable;
			args->Value = gcnew EditorResources::Dto::VariableDto();
			((EditorResources::Dto::VariableDto^)args->Value)->Value = toString(((PrimitiveSaveable<double>*)value)->getValue());
			break;
		case DatabaseIndex::ObjectTypeEnum::PrimitiveString:
			args->Type = EditorResources::Utils::EnumCollection::ObjectType::StringVariable;
			args->Value = gcnew EditorResources::Dto::VariableDto();
			((EditorResources::Dto::VariableDto^)args->Value)->Value = toString(((PrimitiveSaveable<Core::String>*)value)->getValue());
			break;
		case DatabaseIndex::ObjectTypeEnum::StringList:
			args->Type = EditorResources::Utils::EnumCollection::ObjectType::ListVariable;
			args->Value = gcnew EditorResources::Dto::VariableDto();
			((EditorResources::Dto::VariableDto^)args->Value)->Value = toString(((PrimitiveSaveable<std::vector<Core::String>>*)value)->getValue());
			break;
		case DatabaseIndex::ObjectTypeEnum::Element:
			args->Type = EditorResources::Utils::EnumCollection::ObjectType::Element;
			args->Value = gcnew EditorResources::Dto::ElementTypeDto();
			((EditorResources::Dto::ElementTypeDto^)args->Value)->Name = toString(((Element*)value)->name);
			((EditorResources::Dto::ElementTypeDto^)args->Value)->DamageToUnknownType = ((Element*)value)->damageToUnknownType;
			for (std::pair<const std::pair<Core::String, size_t>, double> it : ((Element*)value)->elementAttributes)
			{
				EditorResources::Dto::ElementTypeDto::ElementAttributeDto^ attr = gcnew EditorResources::Dto::ElementTypeDto::ElementAttributeDto();
				attr->ID = it.first.second;
				attr->Origin = toString(it.first.first);
				attr->Modifier = it.second;
				((EditorResources::Dto::ElementTypeDto^)args->Value)->ElementAttribute->Add(attr);
			}
			break;
		case DatabaseIndex::ObjectTypeEnum::Language:
			Engine::GetModule<OneLogger>().Info("Loaded language module.");
			Engine::GetModule<OneLogger>().Info(((Language*)value)->fromMod);
			return;
		case DatabaseIndex::ObjectTypeEnum::Undefined:
		default:
			args->Type = EditorResources::Utils::EnumCollection::ObjectType::Unknown;
			break;
		}
		args->Value->Origin = toString(Origin);
		args->Value->ID = ID;
		args->Value->Name = toString(Name);

		EditorEvents::OnObjectEvent(args);
	}
}
#endif
#endif
#endif