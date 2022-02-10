#include "LoadingScreenInfo.hpp"

#include <Module/Globals.hpp>
#include <File/GameConfig.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

Graphics::UI::LoadingScreenInfo::LoadingScreenInfo(const Enums::LoadingState& theState) : UIContext(sf::Keyboard::Key::Unknown, "LoadingScreenInfo", true), theState(theState)
{
	visible = Engine::GetModule<Globals>().boolGlobals[Globals::B_GLOBAL_LOADINGSCREENINFO];
	f.loadFromFile("C:/Windows/Fonts/arial.ttf");
	t.setFont(f);
	t.setCharacterSize(12);
	auto height = Engine::GetModule<EngineModule::GameConfig>().videoMode.height;
	t.setPosition(5, float(height)-320.f);
}

void Graphics::UI::LoadingScreenInfo::readInput()
{
}

void Graphics::UI::LoadingScreenInfo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!visible)
		return;
	target.draw(t, states);
}

void Graphics::UI::LoadingScreenInfo::update()
{
	t.setString(
		"\nElapsed time: " + std::to_string(totalLoadTime.asSeconds()) + 
		"\nLoading State: " + Enums::to_string(theState) +
		"\nProgress (Total): " + std::to_string(currentLoadCount) +"/" + std::to_string(totalLoadCount) +
		"\nTime (Prepare load): " + std::to_string(instanceLoadTime.asSeconds()) +
		"\nProgress (Tile Atlas): " + std::to_string(currentAtlasCount) +"/" + std::to_string(totalAtlasCount) +
		"\n    Elapsed: " + std::to_string(atlasLoadTimer.asSeconds()) +
		"\nProgress (Prefabs): " + std::to_string(currentPrefabCount) +"/" + std::to_string(totalPrefabCount) +
		"\n    Elapsed: " + std::to_string(prefabLoadTimer.asSeconds()) +
		"\nProgress (Tiles): " + std::to_string(currentTileCount) +"/" + std::to_string(totalTileCount) +
		"\n    Elapsed: " + std::to_string(tileLoadTimer.asSeconds()) +
		"\nProgress (Tile Building): " + std::to_string(currentTileBuildingCount) +"/" + std::to_string(totalTileBuildingCount) +
		"\n    Elapsed: " + std::to_string(tileBuildLoadTimer.asSeconds()) +
		"\nProgress (Collider): " + std::to_string(currentColliderCount) +"/" + std::to_string(totalColliderCount) +
		"\n    Elapsed: " + std::to_string(colliderLoadTimer.asSeconds()) +
		"\nProgress (Building Colliders): " + std::to_string(currentColliderBuildingCount) +"/" + std::to_string(totalColliderBuildingCount) +
		"\n    Elapsed: " + std::to_string(colliderBuildingLoadTimer.asSeconds()) +
		"\nProgress (Pre building objects): " + std::to_string(currentObjectPartCount) + "/" + std::to_string(totalObjectPartCount) +
		"\n    Elapsed: " + std::to_string(objectPartLoadTimer.asSeconds()) + 
		"\nProgress (Building objects): " + std::to_string(currentObjectCount) + "/" + std::to_string(totalObjectCount) +
		"\n    Elapsed: " + std::to_string(objectLoadTimer.asSeconds()) +
		""
	);
}

void Graphics::UI::LoadingScreenInfo::onMouseHover(const Core::Vector2f&)
{
}
