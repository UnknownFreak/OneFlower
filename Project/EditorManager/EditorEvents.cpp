#include "EditorEvents.hpp"
#include <EditorManager\EditorCore.hpp>
#include <EditorManager\WorldEditorExtensions\WorldManagerAddons.hpp>
#include <Core/String.hpp>
#include <iostream>

void Editor::Events::registerEvents()
{
	EditorResources::Functionality::EditorEvents::onModCreate += gcnew EventHandler<EditorResources::Functionality::NewModCreateEventArgs^>(this, &Editor::Events::OnEditorCreateMod);
	EditorResources::Functionality::EditorEvents::onModLoad += gcnew EventHandler<EditorResources::Functionality::ModLoadEventArgs^>(this, &Editor::Events::OnEditorLoadMod);
}

void Editor::Events::OnEditorCreateMod(Object ^ sender, EditorResources::Functionality::NewModCreateEventArgs ^ args)
{
	//Core::String s(args->modName->ToCharArray());
	//Editor::addons.newMod(s, {});
}
void Editor::Events::OnEditorLoadMod(Object ^ sender, EditorResources::Functionality::ModLoadEventArgs ^ args)
{
	array<wchar_t>^ wstr = args->modName->ToCharArray();
	std::wstring w;
	for each(wchar_t wc in wstr)
	{
		w.push_back(wc);
	}
	Core::String s = Core::Converter.toUtf8(w);
	//Editor::addons.loadMod(s);

	EditorResources::Functionality::EditorEvents::onModFinishedLoading(nullptr, gcnew EditorResources::Functionality::ModFinishedLoadedEventArgs());
}

void Editor::Events::OnEditorModLoaded(Object ^ sender, EditorResources::Functionality::ModFinishedLoadedEventArgs ^ args)
{
	throw gcnew System::NotImplementedException();
}
