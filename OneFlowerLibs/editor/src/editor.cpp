#include "editor.hpp"

#include <graphics/window/Window.hpp>

#include <file/Handler.hpp>

#include <internal/gizmo.hpp>
#include <internal/editorCamera.hpp>
#include <internal/editorMenu.hpp>
#include <internal/physxSettingsFrame.hpp>

#include <internal/menu/subMenu.hpp>

#include <internal/modal/newFileModal.hpp>
#include <internal/modal/loadFileModal.hpp>

namespace of::editor
{

	std::shared_ptr<of::graphics::window::Application> s_gfx = nullptr;

	static void createMenu(std::shared_ptr<of::graphics::window::Application> gfx)
	{
		auto editorMenu = std::make_shared<EditorMenu>();
		auto physxSettings = std::make_shared<PhysxSettingsFrame>();
		auto fileMenu = std::make_shared<menu::SubMenu>("File", "");

		auto newFileModal = std::make_shared<modal::NewFile>("New File");
		auto loadFileModal = std::make_shared<modal::LoadFile>("Load File");

		auto newFileMenu = std::make_shared<menu::SubMenuCallback>("New", "Ctrl + N", std::bind(&modal::NewFile::open, newFileModal.get()));
		auto saveFileMenu = std::make_shared<menu::SubMenuCallback>("Save", "Ctrl + S", [] {
			auto& manager = of::engine::GetModule<of::file::Handler>();
			manager.saveGameDatabase(manager.openedFile.name, manager.openedFile); 
			});
		auto loadFileMenu = std::make_shared<menu::SubMenuCallback>("Load", "", std::bind(&modal::LoadFile::open, loadFileModal.get()));

		auto physxMenu = std::make_shared<menu::SubMenuCallback>("Physx", "", std::bind(&PhysxSettingsFrame::open,physxSettings.get()));

		fileMenu->addMenu(newFileMenu);
		fileMenu->addMenu(saveFileMenu);
		fileMenu->addMenu(loadFileMenu);
		fileMenu->addMenu(std::make_shared<menu::Separator>());
		fileMenu->addMenu(std::make_shared<menu::SubMenuCallback>("Exit", "Alt + F4", [] {std::exit(0); }));

		editorMenu->addMenu(fileMenu);
		editorMenu->addMenu(physxMenu);


		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), editorMenu);
		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), physxSettings);
		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), newFileModal);
	}

	void initialize(std::shared_ptr<of::graphics::window::Application> gfx)
	{
		s_gfx = gfx;
		gfx->setCameraController(std::make_shared<EditorCamera>());
		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Gizmo>(gfx));
		createMenu(gfx);
	}

	void exit()
	{
		s_gfx = nullptr;
	}
}