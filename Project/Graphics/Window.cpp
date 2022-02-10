#include "Window.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <Object/GameObject.hpp>
#include <Object/BaseComponent.hpp>
#include "Render.hpp"
#include <Physics/Colliders/EntityCollider.hpp>
#include <Physics/Colliders/VisionCollider.hpp>
#include <Graphics/PlayerInteractionPrompt.hpp>
#include <File/GameConfig.hpp>

Enums::EngineResourceType Interfaces::IEngineResource<Graphics::RenderWindow>::type = Enums::EngineResourceType::Graphics;
namespace Graphics
{
#ifndef _UNITTESTS_
	void RenderWindow::Cull(std::vector<GameObject*>& i_renderables)
	{
		renderables[counter] = transform(i_renderables);
		auto tmp = counter;
		counter = renderCounter;
		renderCounter = tmp;
	}

	std::map<float, std::vector<std::shared_ptr<Renderable>>> RenderWindow::transform(std::vector<GameObject*>& objects)
	{
		std::map<float, std::vector<std::shared_ptr<Renderable>>> toRender;
		for (auto x : objects)
		{
			std::shared_ptr<Render> component = std::dynamic_pointer_cast<Render>(renderMapping[x]);
			if (component)
			{
				Component::Transform* transform = x->getComponent<Component::Transform>();
				toRender[transform->buffered.z].push_back(component);
				toRender[transform->buffered.z].push_back(x->getSharedComponent<Collider>());
				std::shared_ptr<Renderable> r = x->getSharedComponent<VisionCollider>();
				if (r)
					toRender[transform->buffered.z].push_back(r);
				r = x->getSharedComponent<PlayerInteractionPrompt>();
				if (r)
					toRender[99999.f].push_back(r);
			}
		}
		return toRender;
	}

	void RenderWindow::AddRenderable(GameObject* theObject)
	{
		auto r = theObject->getSharedComponent<Render>();
		if (r.get())
			renderMapping[theObject] = r;
	}
	void RenderWindow::RemoveRenderable(GameObject* theObject)
	{
		renderMapping.erase(theObject);
	}
	TransparencyMasker& RenderWindow::getMasker()
	{
		return masker;
	}

	void RenderWindow::ProcessCulling()
	{
		for (auto& it : tileMap)
		{
			for (auto& iit : it.second)
			{
				iit.second.Cull(renderBox, currentDayColor);
				allTiles += iit.second.allTiles;
				renderedTiles += iit.second.renderedTiles;
			}
		}
	}

	RenderWindow::RenderWindow() : window(
		new sf::RenderWindow(Engine::GetModule<EngineModule::GameConfig>().videoMode, "One Flower",
		Engine::GetModule<EngineModule::GameConfig>().getWindowStyle()
		,sf::ContextSettings(0, 0, Engine::GetModule<EngineModule::GameConfig>().getAntiAliasing(),
			3, 2, 0, false))
		),
		drawHitbox(Engine::GetModule<Globals>().boolGlobals[Globals::GLOBAL_DRAW_HITBOX]),
		ui(Engine::GetModule<Graphics::UI::UIHandler>()), light({ 555,125 }, 0, 256, sf::Color(255, 240, 246), sf::Color(255, 219, 120))
	{
		auto videoMode = Engine::GetModule<EngineModule::GameConfig>().videoMode;
		sf::ContextSettings c = window->getSettings();
		c.antialiasingLevel = 8;
		renderTex.create(videoMode.width, videoMode.height, c);
		shadowTex.create(videoMode.width, videoMode.height, c);
		primaryShader.create(videoMode.width, videoMode.height, c);
		secondaryShader.create(videoMode.width, videoMode.height, c);

		auto view = renderTex.getView();
		auto size = view.getSize();
		auto pos = view.getCenter();
		auto box = Core::Rect<float>{ pos.x - size.x / 2, pos.y - size.y / 2, size.x + 128, size.y + 128 };
		box.x -= 64;
		box.y -= 64;
		renderBox = box;

		renderSprite.setTexture(renderTex.getTexture());
		dayNightShader.loadFromFile("test2.frag", sf::Shader::Type::Fragment);

		luminescence.loadFromFile("luminescence.frag", sf::Shader::Type::Fragment);
		boxBlur.loadFromFile("boxblur.frag", sf::Shader::Type::Fragment);

		multiply.loadFromFile("multiply.frag", sf::Shader::Type::Fragment);
		assemble.loadFromFile("assemble.frag", sf::Shader::Type::Fragment);

		luminescence.setUniform("texture", sf::Shader::CurrentTexture);
		luminescence.setUniform("threshold", .66f);

		boxBlur.setUniform("tex", sf::Shader::CurrentTexture);
		boxBlur.setUniform("texture_inverse", 1.0f / videoMode.width);

		multiply.setUniform("texture", sf::Shader::CurrentTexture);
		assemble.setUniform("texture", sf::Shader::CurrentTexture);

		entityShading.loadFromFile("shadowEntity.frag", sf::Shader::Type::Fragment);
		entityShading.setUniform("texture", sf::Shader::CurrentTexture);

		lightUmpfher.loadFromFile("light.frag", sf::Shader::Type::Fragment);
		lightUmpfher.setUniform("texture", sf::Shader::CurrentTexture);
		lightUmpfher.setUniform("intensity", 0.8f);
	}

	RenderWindow::~RenderWindow()
	{
		if(window)
			window->close();
			delete window;
	}

	RenderWindow::RenderWindow(const RenderWindow& copy) : window(copy.window),
		drawHitbox(Engine::GetModule<Globals>().boolGlobals[Globals::GLOBAL_DRAW_HITBOX]),
		light({ 55,55 }, 0, 33, sf::Color(255, 240, 246), sf::Color(199, 183, 139)),
		ui(Engine::GetModule<Graphics::UI::UIHandler>())
	{
		copy.window = nullptr;
		renderTex.create(1920, 1080);
		renderSprite.setTexture(renderTex.getTexture());
		dayNightShader.loadFromFile("test2.frag", sf::Shader::Type::Fragment);
	}

	RenderWindow& RenderWindow::operator=(const RenderWindow& other)
	{
		window = std::move(other.window);
		renderTex.create(1920, 1080);
		renderSprite.setTexture(renderTex.getTexture());
		return *this;
	}

	void RenderWindow::draw()
	{
		renderedTiles = 0;
		allTiles = 0;
		renderTex.clear();
		shadowTex.clear(currentDayColor);
		entityShading.setUniform("color", sf::Glsl::Vec4(currentDayColor));

		//dayNightShader.setUniform("texture", renderTex.getTexture());
		//dayNightShader.setUniform("sigma", .5f);
		//dayNightShader.setUniform("glowMultiplier", 1.5f);
		//dayNightShader.setUniform("width", 1920);
		//dayNightShader.setUniform("height", 1080);
		//dayNightShader.setUniform("isVertical", true);
		
		//dayNightShader.setUniform("lightmap", lightBlob.getTexture());
		//dayNightShader.setUniform("ambient", sf::Glsl::Vec4(255, 255, 255, 0));
		//dayNightShader.setUniform("resolution", sf::Vector2f(1920, 1080));
		//dayNightShader.setUniform("theta", theta);

		//dayNightShader.setUniform("frag_LightOrigin", sf::Glsl::Vec3(50 , 1080 - 50 , 150));
		//dayNightShader.setUniform("frag_LightColor", sf::Glsl::Vec4(255, 255, 255, 255));
		//dayNightShader.setUniform("frag_LightAttenuation", theta);
		ProcessCulling();
		std::map<float, std::vector<std::shared_ptr<Renderable>>> toRender = renderables[renderCounter];
		std::vector<std::shared_ptr<Renderable>> v;

		int max_layer = -999999;
		masker.update();
		if (mtx.try_lock())
		{
			for (auto& it : tileMap)
			{
				max_layer = it.first;
				float a = (float)it.first;
				float b = a + 1.f;
				for (auto fit = toRender.lower_bound(a); fit != toRender.upper_bound(b); fit++)
				{
					v.reserve(v.size() + fit->second.size());
					v.insert(v.end(), fit->second.begin(), fit->second.end());
				}
				for (auto& iit : it.second)
				{
					masker.triggersTransparency(&iit.second, it.first);
					iit.second.projectShadow(shadowAngle, shadowLengthX, shadowLengthY);
					iit.second.drawShadows(shadowTex, v, entityShading);
					renderTex.draw(iit.second);
				}
				if (it.second.size() == 0)
				{
					empty.drawShadows(shadowTex, v, entityShading);
				}
				std::sort(v.begin(), v.end(), [](const std::shared_ptr<Renderable>& r1, const std::shared_ptr<Renderable>& r2) {return r1->drawBox.y < r2->drawBox.y; });
				for (auto& iiit : v)
				{
					renderTex.draw(*(iiit.get()));
				}
				v.clear();
			}
			mtx.unlock();
		}

		shadowTex.draw(light);
		lightUmpfher.setUniform("color", sf::Glsl::Vec4(light.lightShaderColor));
		renderTex.draw(light, &lightUmpfher);

		for (auto it = toRender.lower_bound(float(max_layer)); it != toRender.end(); it++)
		{
			//if (it.first >= max_layer)
			{
				std::sort(it->second.begin(), it->second.end(), [](const std::shared_ptr<Renderable>& r1, const std::shared_ptr<Renderable>& r2) {return r1->drawBox.y < r2->drawBox.y; });
				//empty.drawShadows(shadowTex, it->second, entityShading);
				for (auto& iit : it->second)
				{
					renderTex.draw(*(iit.get()));
				}
			}
		}
		
		if (drawHitbox)
		{
			sf::RectangleShape s;
			s.setFillColor(sf::Color::Transparent);
			s.setOutlineColor(sf::Color::Yellow);
			s.setOutlineThickness(1.f);
			s.setPosition(masker.triggerTransparency.x, masker.triggerTransparency.y);
			s.setSize({ masker.triggerTransparency.w, masker.triggerTransparency.h });
			renderTex.draw(s);
			s.setOutlineColor(sf::Color::Blue);
			s.setPosition(masker.releaseTransparency.x, masker.releaseTransparency.y);
			s.setSize({ masker.releaseTransparency.w, masker.releaseTransparency.h });
			renderTex.draw(s);
		}

		shadowTex.display();
		renderTex.display();

		sf::RenderTexture* r1 = &primaryShader;
		sf::RenderTexture* r2 = &secondaryShader;
		
		r1->clear();
		r2->clear();
		
		states.shader = &luminescence;
		r2->draw(renderSprite, states);
		r2->display();
		std::swap(r1, r2);
		
		states.shader = &boxBlur;
		boxBlur.setUniform("blur_radius", 20);
		r2->clear();
		r2->draw(sf::Sprite(r1->getTexture()));
		r2->display();
		// TODO: Do a better blur handling as of now it's super slow...
		for (unsigned i = 0; i < 8; i++)
		{
			boxBlur.setUniform("blur_direction", sf::Glsl::Vec2(2.4f, 0.0f));
			r2->draw(sf::Sprite(r2->getTexture()), states);
			r2->display();
		
			boxBlur.setUniform("blur_direction", sf::Glsl::Vec2(0.0f, 2.4f));
			r2->draw(sf::Sprite(r2->getTexture()), states);
			r2->display();
			std::swap(r1, r2);
			r2->clear();
		}

		//std::swap(r1, r2);
		
		states.shader = &multiply;
		multiply.setUniform("multiply", 1.f);
		//r2->clear();
		r2->draw(sf::Sprite(r1->getTexture()), states);
		r2->display();
		states.shader = &assemble;
		assemble.setUniform("add_weight", 1.f);
		assemble.setUniform("add_texture", r2->getTexture());
		
		r2->draw(renderSprite, states);
		r2->display();

		//window->draw(renderSprite);
		window->draw(sf::Sprite(r2->getTexture()));
		sf::RenderStates s;
		s.blendMode = sf::BlendMultiply;
		sf::Sprite spr(shadowTex.getTexture());
		window->draw(spr, s);
		//window->draw(renderTex.t);
		//renderTex.t.setString(renderTex.t.getString() + " Rendered tiles: " + std::to_string(renderedTiles) + "/" + std::to_string(allTiles));
		//window->draw(renderTex.t);
		//window->draw(renderSprite);
		//window->display();
	}

	void RenderWindow::drawUI()
	{
		ui.updateMouse(*window);
		ui.toggleToolTips();
		window->draw((sf::Drawable&)ui);
	}

	void RenderWindow::poll(sf::Event& event) const
	{
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				
			}
		}
	}

	void RenderWindow::setFramerate(const unsigned& limit) const
	{
		window->setFramerateLimit(limit);
	}

	void RenderWindow::setActive(const bool& active) const
	{
		window->setActive(active);
	}

	bool RenderWindow::isOpen() const
	{
		return window->isOpen();
	}

	void RenderWindow::moveCamera(const Core::Vector2f& vec)
	{
		vec;
		//auto view = (sf::View&)window->getView();
		//view.move(vec.x, vec.y);
		//window->setView(view);
	}
	void RenderWindow::moveCamera(const Core::Vector2f& vec, const Core::Rect<float>& bounds)
	{
		vec; bounds;
		//sf::Vector2f newTransform {0, 0};
		//auto view = (sf::View&)window->getView();
		//auto size = view.getSize();
		//auto pos = view.getCenter();
		//auto renderBox = Core::Rect<float>{ pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y };
		//
		//if (renderBox.pos.x> bounds.pos.x &&  renderBox.pos.x + renderBox.size.x < bounds.pos.x + bounds.size.x)
		//	newTransform.x = vec.x;
		//if (renderBox.pos.y > bounds.pos.y && renderBox.pos.y + renderBox.size.y < bounds.pos.y + bounds.size.y)
		//	newTransform.y = vec.y;
		//
		//view.move(newTransform);
		//window->setView(view);
	}
	void RenderWindow::centerCameraOnObjectPos(const Core::Vector3f& position)
	{
		auto view = renderTex.getView();
		
		//auto view = (sf::View&)window->getView();
		view.setCenter(std::floor(position.x), std::floor(position.y + (position.z * Globals::Z_OFFSET)));
		//window->setView(view);
		renderTex.setView(view);
		shadowTex.setView(view);
		auto size = view.getSize();
		auto pos = view.getCenter();
		auto box = Core::Rect<float>{ pos.x - size.x / 2, pos.y - size.y / 2, size.x + 128, size.y + 128 };
		box.x -= 64;
		box.y -= 64;
		box.y -= position.z * Globals::Z_OFFSET;
		renderBox = box;
	}

	void RenderWindow::addRenderable(const int& index, const Core::String& group, const Core::Vector2& pos, const float& z,
		const File::Mod::ModFileUUIDHelper& textureAtlas, const Core::String& textureCoords, const Enums::TileTypes& _type, bool addShadow)
	{
		tileMap[index][group].AddTile(pos, z, textureAtlas, textureCoords, _type, addShadow);
	}

	void RenderWindow::setTileMapColor(const int& index, const Core::String& group, const sf::Color& color)
	{
		tileMap[index][group].SetColor(color);
	}

	void RenderWindow::setTileMapTransparencyHitbox(int index, Core::String group, Core::Rect<float> rect, float z)
	{
		tileMap[index][group].setDrawBox(rect, z);
	}

	void RenderWindow::clearDrawList()
	{
		tileMap.clear();
	}
#else
void RenderWindow::Cull(std::vector<GameObject*>& )
{
}

void RenderWindow::AddRenderable(GameObject* )
{
}
void RenderWindow::RemoveRenderable(GameObject* )
{
}
TransparencyMasker& RenderWindow::getMasker()
{
	return masker;
}

RenderWindow::RenderWindow()
{
}

RenderWindow::~RenderWindow()
{
}

RenderWindow::RenderWindow(const RenderWindow& )
{
}

RenderWindow& RenderWindow::operator=(const RenderWindow& )
{
	return *this;
}

void RenderWindow::draw()
{
}

void RenderWindow::drawUI()
{
}

void RenderWindow::poll(sf::Event& ) const
{
}

void RenderWindow::setFramerate(const unsigned& ) const
{
}

void RenderWindow::setActive(const bool& ) const
{
}

bool RenderWindow::isOpen() const
{
	return false;
}

void RenderWindow::moveCamera(const Core::Vector2f& vec)
{
	vec;
}
void RenderWindow::moveCamera(const Core::Vector2f& vec, const Core::Rect<float>& bounds)
{
	vec; bounds;
}
void RenderWindow::centerCameraOnObjectPos(const Core::Vector3f& position)
{
	position;
}

void RenderWindow::addRenderable(const int& index, const Core::String& group, const Core::Vector2& pos, const float& z,
	const File::Mod::ModFileUUIDHelper& textureAtlas, const Core::String& textureCoords, const Enums::TileTypes& _type, bool addShadow)
{
	index, group, pos, z, textureAtlas, textureCoords, _type, addShadow;
}

void RenderWindow::setTileMapColor(const int& index, const Core::String& group, const sf::Color& color)
{
	index, group, color;
}

void RenderWindow::setTileMapTransparencyHitbox(int index, Core::String group, Core::Rect<float> rect, float z)
{
	index, group, rect, z;
}

void RenderWindow::clearDrawList()
{
}
#endif
}

