#ifndef LoadingStateMachine_HPP
#define LoadingStateMachine_HPP

#include <glm/vec3.hpp>

#include <Graphics/Window.hpp>
#include <Helpers/Enum/LoadingState.hpp>
#include <Graphics/UI/LoadingScreenInfo.hpp>
#include <File/Asset/Resource/Template/WorldInstance.hpp>

class LoadingStateMachine
{

	Graphics::UI::LoadingScreenInfo* loadingScreenInfoPtr;
	bool& isLoading;
	Graphics::RenderWindow& gfx;
	Enums::LoadingState loadstate;

	of::file::FileId worldToLoad;
	of::file::FileId loadingScreenToLoad;

	File::Asset::Resource::Template::WorldInstance instanceToLoad;

public:

	const of::file::FileId& getCurrentWorld() const;
	const of::file::FileId& getCurrentLoadingScreen() const;

	std::vector<File::Asset::Resource::Template::ObjectInfo> buffer;
	
	glm::vec3 playerPos;

	LoadingStateMachine(Graphics::RenderWindow& gfx, bool& isLoading);

	void beginLoad(const of::file::FileId& world, const of::file::FileId& loadingScreen, const glm::vec3& position);
	void load();
	
};

#endif