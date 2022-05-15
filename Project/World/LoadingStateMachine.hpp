#ifndef LoadingStateMachine_HPP
#define LoadingStateMachine_HPP

#include <glm/vec3.hpp>

#include <Graphics/Window.hpp>
#include <Helpers/Enum/LoadingState.hpp>
#include <Graphics/UI/LoadingScreenInfo.hpp>

class LoadingStateMachine
{

	Graphics::UI::LoadingScreenInfo* loadingScreenInfoPtr;
	bool& isLoading;
	Graphics::RenderWindow& gfx;
	Enums::LoadingState loadstate;

	File::Mod::ModFileUUIDHelper worldToLoad;
	File::Mod::ModFileUUIDHelper loadingScreenToLoad;

	File::Asset::Resource::Template::WorldInstance instanceToLoad;

public:

	const File::Mod::ModFileUUIDHelper& getCurrentWorld() const;
	const File::Mod::ModFileUUIDHelper& getCurrentLoadingScreen() const;

	std::vector<File::Asset::Resource::Template::ObjectInfo> buffer;
	
	glm::vec3 playerPos;

	LoadingStateMachine(Graphics::RenderWindow& gfx, bool& isLoading);

	void beginLoad(const File::Mod::ModFileUUIDHelper& world, const File::Mod::ModFileUUIDHelper& loadingScreen, const glm::vec3& position);
	void load();
	
};

#endif