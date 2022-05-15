#ifndef LoadingScreen_HPP
#define LoadingScreen_HPP

#include <Graphics/UI/UIContext.hpp>

#include <Helpers/String.hpp>

namespace Graphics::UI
{
	class LoadingScreen : public UIContext
	{
		//std::shared_ptr<sf::Texture> texture;
		Core::String loadingScreenName;
		//sf::Sprite loadingScreen;
	public:
		LoadingScreen();
		~LoadingScreen();

		// Inherited via UIContext
		virtual void readInput() override;

		virtual void render() override;

		// Inherited via UIContext
		virtual void onMouseHover(const glm::vec2& mouse) override;
	};
}


#endif
