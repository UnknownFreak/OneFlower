#pragma once
#ifndef WorldManager_HPP
#define WorldManager_HPP

#include <vector>
#include <memory>

#include <Helpers/uuid.hpp>
#include <File/ModFileUUIDHelper.hpp>

#include <Interfaces/IUpdateable.hpp>
#include <Graphics/Window.hpp>
#include <Object/ObjectInstanceHandler.hpp>
#include <File/SaveFile.hpp>

#include "LoadingStateMachine.hpp"

class WorldManager : public Interfaces::IUpdateable, Interfaces::ISimulatable
{

	LoadingStateMachine loadHandler;

	EngineModule::ObjectInstanceHandler& objectHandler;
	File::SaveFile& saveFile;

	void doDayCycle(const float& fElapsedTime);

public:
	Graphics::RenderWindow& gfx;
	bool isLoading = false;
	WorldManager(Graphics::RenderWindow& gfx);
	WorldManager(const WorldManager& copy);

//#ifdef _DEBUG
	void createSimpleWorld();
	void setCurrentTime(const float& currentTime);

//#endif

	void newGame();
	void save(const Core::String& fileName);
	void load(const Core::String& fileName);

	void loadWorldInstance(const File::Mod::ModFileUUIDHelper& world, const File::Mod::ModFileUUIDHelper& loadingScreen, const Core::Vector3f& playerPosition = {0.f, 0.f, 0.f});
	

	// Inherited via IUpdateable
	virtual void Update() override;


	// Inherited via ISimulatable
	virtual void Simulate(const float& fElapsedTime) override;

};

#endif 