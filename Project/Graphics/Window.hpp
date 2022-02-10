#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <map>
#include <mutex>
#include <SFML/Graphics.hpp>
#include <Graphics/Renderable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <Interfaces/IEngineModule.hpp>
#include <Helpers/Rect.hpp>
#include <Graphics/TransparencyMasker.hpp>
#include <Graphics/TileMap.hpp>
#include "Light.hpp"
#include "UI/UIHandler.hpp"


namespace Component
{
	class Base;
}
class GameObject;
namespace Graphics
{
	class RenderWindow : public Interfaces::IEngineResource<RenderWindow>
	{
#ifndef _UNITTESTS_
		TileMap empty;
		std::unordered_map<GameObject*, std::shared_ptr<Component::Base>> renderMapping;
		std::map<int, std::map<Core::String,TileMap>> tileMap;
		std::map<float, std::vector<std::shared_ptr<Renderable>>> renderables[2];

		Graphics::Light light;

		TransparencyMasker masker;
		const bool& drawHitbox;
		sf::RenderTexture renderTex;
		//sf::RenderTexture renderTex;
		sf::RenderTexture shadowTex;
		sf::RenderTexture primaryShader;
		sf::RenderTexture secondaryShader;
		sf::Sprite renderSprite;
		sf::Shader dayNightShader;

		sf::Shader luminescence;
		sf::Shader boxBlur;
		sf::Shader multiply;
		sf::Shader assemble;

		sf::Shader entityShading;
		sf::Shader lightUmpfher;

		sf::RenderStates states;

		void ProcessCulling();
		size_t renderedTiles = 0;
		size_t allTiles = 0;
		size_t counter = 0;
		size_t renderCounter = 1;

		std::map<float, std::vector<std::shared_ptr<Renderable>>> transform(std::vector<GameObject*>& objects);
	public:
		std::mutex mtx;
		Graphics::UI::UIHandler& ui;

		//Component::Transform* player = nullptr;;
		mutable sf::RenderWindow*  window;
		float shadowAngle = 0.f;
		float timeOfDay = 0.f;
		float shadowLengthX = 0.f;
		float shadowLengthY = 0.f;
		float theta = 3;
		Core::Rect<float> renderBox;
		sf::Color currentDayColor;
#else
	public:
		std::mutex mtx;
		mutable sf::RenderWindow* window;
		TransparencyMasker masker;
		Core::Rect<float> renderBox;
		Graphics::UI::UIHandler ui;
		float shadowAngle = 0.f;
		float timeOfDay = 0.f;
		float shadowLengthX = 0.f;
		float shadowLengthY = 0.f;
		sf::Color currentDayColor;
#endif
	public:

		inline void reloadShader() {
#ifndef _UNITTESTS_
			//dayNightShader.loadFromFile("frag2.frag", sf::Shader::Type::Fragment);
			boxBlur.loadFromFile("boxblur.frag", ::sf::Shader::Type::Fragment);
			boxBlur.setUniform("tex", sf::Shader::CurrentTexture);
			boxBlur.setUniform("texture_inverse", 1.0f / 1920);
			entityShading.loadFromFile("shadowEntity.frag", sf::Shader::Type::Fragment);
			entityShading.setUniform("texture", sf::Shader::CurrentTexture);
#endif
		};
		RenderWindow();
		~RenderWindow();
		RenderWindow(const RenderWindow& copy);
		RenderWindow& operator=(const RenderWindow& other);

		void draw();
		void drawUI();
		void poll(sf::Event& event) const;

		void setFramerate(const unsigned& limit) const;
		void setActive(const bool& active) const;

		bool isOpen() const;

		void moveCamera(const Core::Vector2f& vec);
		void moveCamera(const Core::Vector2f& vec, const Core::Rect<float>& bounds);
		void centerCameraOnObjectPos(const Core::Vector3f& position);

		void setTileMapColor(const int& index, const Core::String& group, const sf::Color& color);
		void setTileMapTransparencyHitbox(int index, Core::String group, Core::Rect<float> rect, float z);
		void addRenderable(const int& index, const Core::String& group, const Core::Vector2& pos, const float& z,
			const File::Mod::ModFileUUIDHelper& textureAtlas, const Core::String& textureCoords, const Enums::TileTypes& type, bool addShadow=false);
		void clearDrawList();

		void Cull(std::vector<GameObject*>& colliders);

		void AddRenderable(GameObject* theObject);
		void RemoveRenderable(GameObject* theObject);

		void addHitbox(std::unique_ptr<TileCollider> ptr, int index, Core::String group)
		{
#ifndef _UNITTESTS_
			tileMap[index][group].AddHitbox(std::move(ptr));
#else
			ptr, index, group;
#endif
		}

		Enums::EngineResourceType & getType() const
		{
			return type;
		}

		TransparencyMasker& getMasker();
	};
}


#endif //WINDOW_HPP