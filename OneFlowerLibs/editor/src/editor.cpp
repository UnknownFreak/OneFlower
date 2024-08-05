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
	std::vector<of::common::uuid> s_uuids;

	static of::common::uuid add(std::shared_ptr<of::graphics::window::Application> gfx, std::shared_ptr<of::graphics::Renderable> render)
	{
		of::common::uuid id;
		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, id, render);
		return id;
	}

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

		s_uuids.push_back(add(gfx, editorMenu));
		s_uuids.push_back(add(gfx, physxSettings));
		s_uuids.push_back(add(gfx, newFileModal));
		s_uuids.push_back(add(gfx, loadFileModal));
	}

	void initialize(std::shared_ptr<of::graphics::window::Application> gfx)
	{
		s_gfx = gfx;
		s_uuids.clear();
		gfx->setCameraController(std::make_shared<EditorCamera>());
		s_uuids.push_back(add(gfx, std::make_shared<Gizmo>(gfx)));
		createMenu(gfx);
	}

	void exit()
	{
		for (auto& id : s_uuids)
		{
			s_gfx->removeRenderable(id);
		}
		s_gfx = nullptr;
	}
}