#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <File/AssetManagerCore.hpp>
#include <File/Resource/TextureLoader.hpp>

#include <Helpers/Enum/TileTypes.hpp>

#include <Physics/Colliders/TileCollider.hpp>
#include <Physics/QuadTree.hpp>

#include <immintrin.h>


inline float getValue(const __m256& m, const int& idx)
{
#if defined(__linux__)				
	return m[idx];
#endif
#if defined (_WIN32)
	return m.m256_f32[idx];
#endif
}

struct TileImpl : Renderable
{
	
	TileImpl() : Renderable({0,0,0,0}) {};
	sf::Vertex mVertex[4];
	Enums::TileTypes type = Enums::TileTypes::Void;
	File::Mod::ModFileUUIDHelper theAtlas;
	float z = 0.f;

	virtual void draw(sf::RenderTarget& , sf::RenderStates ) const override
	{

	}

	bool needUpdate() { return false; }
	void doParentUpdate() {};

	bool operator==(const TileImpl& other) const { return drawBox == other.drawBox; }

};

inline auto getTileBox = [](TileImpl node)
{
	return node.drawBox;
};
class TileMap : public Renderable
{

	sf::Color originalColor;
	sf::Color transparencyColor;

	quadtree::Quadtree<TileImpl, decltype(getTileBox)> tileTree;

	const bool& renderHitboxes;
	sf::Shader s;

	sf::VertexArray floorShadows;
	sf::VertexArray shadows;
	sf::VertexArray hitboxes;
	std::map<File::Mod::ModFileUUIDHelper, std::shared_ptr<sf::Texture>> textures;

	std::vector<std::unique_ptr<TileCollider>> colliders;

	std::map<File::Mod::ModFileUUIDHelper, sf::VertexArray> culledFloor;
	std::map<File::Mod::ModFileUUIDHelper, sf::VertexArray> culledWalls;
	sf::VertexArray culledFloorShadows;
	sf::VertexArray culledShadows;
	sf::VertexArray culledHitboxes;

	Core::Rect<float> previousRect;

	void setTransparency(std::map<File::Mod::ModFileUUIDHelper, sf::VertexArray>& buf, const sf::Color& color)
	{
		for (auto& x : buf)
		{
			for (size_t i = 0; i < x.second.getVertexCount(); i++)
			{
				x.second[i].color = color;
			}
		}
	}

	void SetColor(std::map<File::Mod::ModFileUUIDHelper, sf::VertexArray>& buf, const sf::Color& color)
	{
		for (auto& x : buf)
		{
			for (size_t i = 0; i < x.second.getVertexCount(); i++)
			{
				x.second[i].color = color;
			}
		}
	}

	void addTexture(const File::Mod::ModFileUUIDHelper& helper)
	{
		if (textures.find(helper) == textures.end())
		{
			TileAtlas* ta = Engine::GetModule<Asset::AssetManager>().requestor.request<TileAtlas>(helper);
			textures.insert({ helper, Engine::GetModule<TextureLoader>().requestTexture(ta->name, Globals::tileTexturePath) });
		}
	}

	void addLayer(const File::Mod::ModFileUUIDHelper& helper)
	{
		if (culledWalls.find(helper) == culledWalls.end())
		{
			culledWalls.insert({ helper, sf::VertexArray(sf::PrimitiveType::Quads) });
		}
		if (culledFloor.find(helper) == culledFloor.end())
		{
			culledFloor.insert({ helper, sf::VertexArray(sf::PrimitiveType::Quads) });
		}
	}

	void Cull(const Core::Rect<float>& rect, sf::VertexArray& cull, sf::VertexArray& noCulled, const size_t inc = 4)
	{
		for (size_t i = 0; i < noCulled.getVertexCount(); i += inc)
		{
			auto p = noCulled[i].position;
			auto p2 = noCulled[i + 2].position;
			//const size_t inc_ = inc * rect.contains_const(p.x, p.y) | inc * rect.contains_const(p2.x, p2.y);
			//for (size_t c = 0; c < inc_; c++)
			//	cull.append(noCulled[i + c]);
			if (rect.contains_const(p.x, p.y) || rect.contains_const(p2.x, p2.y))
			{
				for (size_t c = 0; c < inc; c++)
					cull.append(noCulled[i + c]);
			}
		}
	}

public:

	size_t allTiles;
	size_t renderedTiles;

	void reloadShader()
	{
		s.loadFromFile("shadow.frag", sf::Shader::Type::Fragment);
		//s.loadFromFile("shadow.vert", sf::Shader::Type::Vertex);
		s.setUniform("texture", sf::Shader::CurrentTexture);
	}

	TileMap(): hitboxes(sf::PrimitiveType::Lines), culledHitboxes(sf::PrimitiveType::Lines),
		renderHitboxes(Engine::GetModule<Globals>().boolGlobals[Globals::GLOBAL_DRAW_HITBOX]), previousRect{0,0,0,0},
		shadows(sf::PrimitiveType::Quads), culledShadows(sf::PrimitiveType::Quads),
		floorShadows(sf::PrimitiveType::Quads), culledFloorShadows(sf::PrimitiveType::Quads),
		Renderable({0,0,0,0}), tileTree({ -100000, -100000, 200000, 200000 }, getTileBox)
	{
		allTiles = 0;
		SetColor({ 255, 255, 255 });
		reloadShader();
	}

	void setDrawBox(const Core::Rect<float>& rect, float z)
	{
		drawBox = rect;
		drawBox.y += z * Globals::Z_OFFSET;
	}

	void AddTile(const Core::Vector2f& pos, const float& z, const File::Mod::ModFileUUIDHelper& textureAtlas, const Core::String& atlasPos,
		const Enums::TileTypes& type, bool addShadow = false)
	{
		allTiles++;
		addTexture(textureAtlas);
		TileAtlas* ta = Engine::GetModule<Asset::AssetManager>().requestor.request<TileAtlas>(textureAtlas);
		auto texCoord = ta->get(atlasPos);
		addLayer(textureAtlas);

		TileImpl t;
		t.mVertex[0] = sf::Vertex({ pos.x, (pos.y + z * Globals::Z_OFFSET) }, { texCoord.x, texCoord.y });
		t.mVertex[1] = sf::Vertex({ pos.x + Globals::MAX_SIZE_F,  (pos.y + z * Globals::Z_OFFSET) },
			{ texCoord.x + Globals::MAX_SIZE_F, texCoord.y });
		t.mVertex[2] = sf::Vertex({ pos.x + Globals::MAX_SIZE_F, (pos.y + z * Globals::Z_OFFSET) + Globals::MAX_SIZE_F },
			{ texCoord.x + Globals::MAX_SIZE_F,  texCoord.y + 64.f });
		t.mVertex[3] = sf::Vertex({ pos.x,  (pos.y + z * Globals::Z_OFFSET) + Globals::MAX_SIZE_F },
			{ texCoord.x, texCoord.y + Globals::MAX_SIZE_F });

		auto hasShadow = type == Enums::TileTypes::Wall || addShadow;
		t.type = type;
		t.theAtlas = textureAtlas;
		t.z = z;
		t.drawBox.pos = { t.mVertex[0].position.x, t.mVertex[0].position.y };
		t.drawBox.size = { 64.f, 64.f };
		if (hasShadow)
		{
			auto shadowTile = t;
			auto ShadowType = Enums::TileTypes::GroundShadow;
			if (type == Enums::TileTypes::Wall)
				ShadowType = Enums::TileTypes::WallShadow;
			float q = 0.f;
			if (addShadow && type == Enums::TileTypes::Wall)
			{
				q = 1.f;
				ShadowType = Enums::TileTypes::WallShadow;
			}
			shadowTile.type = ShadowType;
			shadowTile.mVertex[0] = sf::Vertex({ pos.x, (pos.y + z * Globals::Z_OFFSET) },
				sf::Color(56, 56, 56), { 0, q });
			shadowTile.mVertex[1] = sf::Vertex({ pos.x + Globals::MAX_SIZE_F,  (pos.y + z * Globals::Z_OFFSET) },
				sf::Color(56, 56, 56), { 0, q });
			shadowTile.mVertex[2] = sf::Vertex({ pos.x + Globals::MAX_SIZE_F, (pos.y + z * Globals::Z_OFFSET) + Globals::MAX_SIZE_F },
				sf::Color(56, 56, 56), { 0, q });
			shadowTile.mVertex[3] = sf::Vertex({ pos.x,  (pos.y + z * Globals::Z_OFFSET) + Globals::MAX_SIZE_F },
				sf::Color(56, 56, 56), { 0, q });
			tileTree.add(shadowTile);
		}
		tileTree.add(t);
	}

	void AddHitbox(std::unique_ptr<TileCollider> ptr)
	{
		ptr->Update();
		ptr->buildRenderableHitbox(hitboxes);
		colliders.emplace_back(std::move(ptr));
	}

	void SetColor(const sf::Color& color)
	{
		if (originalColor == color)
			return;
		originalColor = color;
		transparencyColor = originalColor - sf::Color(60,60,60);
		transparencyColor.a = 255 / 2;
		SetColor(culledFloor, color);
		SetColor(culledWalls, color);
	}

	void projectShadow(const float& angle, const float& shadow_length_x, const float& shadow_length_y)
	{
		//if (previousAngle == angle)
			//return;
		const float y_angle = std::abs(std::sin(angle));
		const float x_angle = std::cos(angle);

		__m256 _angles, _add64, _mul64, _shadow_len, _values, _cast_shadows;
		_angles = _mm256_setr_ps(y_angle, y_angle, x_angle, x_angle,
								 y_angle, y_angle, x_angle, x_angle);

		_add64 = _mm256_setr_ps(Globals::MAX_SIZE_F, 0, Globals::MAX_SIZE_F, Globals::MAX_SIZE_F, 
								Globals::MAX_SIZE_F, Globals::MAX_SIZE_F, 0,0);

		_mul64 = _mm256_setr_ps(Globals::MAX_SIZE_F, Globals::MAX_SIZE_F, Globals::MAX_SIZE_F, Globals::MAX_SIZE_F,
			                    Globals::MAX_SIZE_F, Globals::MAX_SIZE_F, Globals::MAX_SIZE_F, Globals::MAX_SIZE_F);

		_shadow_len = _mm256_setr_ps(shadow_length_y, shadow_length_y, shadow_length_x, shadow_length_x,
									 shadow_length_y, shadow_length_y, shadow_length_x, shadow_length_x);
		
		_cast_shadows = _mm256_mul_ps(_shadow_len, _mul64);
		_cast_shadows = _mm256_mul_ps(_cast_shadows, _angles);

		for (size_t i = 0; i < culledShadows.getVertexCount(); i += 4)
		{
			_values = _mm256_setr_ps(
				culledShadows[i].position.y, culledShadows[i].position.y,
				culledShadows[i].position.x, culledShadows[i].position.x,
				culledShadows[i].position.y, culledShadows[i].position.y,
				0, 0);
			_values = _mm256_add_ps(_values, _add64);
			_values = _mm256_add_ps(_values, _cast_shadows);
			if (culledShadows[i].texCoords.y > 0.8f)
			{
				if (angle < 1.84f)
				{
					_values.m256_f32[2] += Globals::MAX_SIZE_F;
					_values.m256_f32[3] += Globals::MAX_SIZE_F;
					culledShadows[i].position.x += Globals::MAX_SIZE_F;
					culledShadows[i+3].position.x = culledShadows[i+3].position.x + Globals::MAX_SIZE_F;
				}

				culledShadows[i + 2].position.y = getValue(_values, 0);
				culledShadows[i + 1].position.y = getValue(_values, 1);
				culledShadows[i + 2].position.x = getValue(_values, 2);
				culledShadows[i + 1].position.x = getValue(_values, 3);
			}
			else
			{
				culledShadows[i + 2].position.y = getValue(_values, 4);
				culledShadows[i + 3].position.y = getValue(_values, 5);

				//culledShadows[i + 2].position.x = culledShadows[i+1].position.x + shadow_length_x * 64.f * std::cos(angle);
				//culledShadows[i + 3].position.x = culledShadows[i].position.x + shadow_length_x * 64.f * std::cos(angle);
			}
		}
		for (size_t i = 0; i < culledFloorShadows.getVertexCount(); i += 4)
		{
			_values = _mm256_setr_ps(
				floorShadows[i].position.y, floorShadows[i + 1].position.y,
				floorShadows[i].position.x, floorShadows[i + 1].position.x,
				floorShadows[i + 2].position.y, floorShadows[i + 3].position.y,
				floorShadows[i + 2].position.x, floorShadows[i + 3].position.x);
			_values = _mm256_add_ps(_values, _cast_shadows);

			culledFloorShadows[i + 0].position.y = getValue(_values, 0);
			culledFloorShadows[i + 1].position.y = getValue(_values, 1);
			culledFloorShadows[i + 0].position.x = getValue(_values, 2);
			culledFloorShadows[i + 1].position.x = getValue(_values, 3);
			culledFloorShadows[i + 2].position.y = getValue(_values, 4);
			culledFloorShadows[i + 3].position.y = getValue(_values, 5);
			culledFloorShadows[i + 2].position.x = getValue(_values, 6);
			culledFloorShadows[i + 3].position.x = getValue(_values, 7);
		}
	}

	void setTransparency(const bool& transparent)
	{
		//auto const color = sf::Color(
		//	transparencyColor.r * transparent + originalColor.r * !transparent,
		//	transparencyColor.g * transparent + originalColor.g * !transparent,
		//	transparencyColor.b * transparent + originalColor.b * !transparent,
		//	transparencyColor.a * transparent + originalColor.a * !transparent);
		//setTransparency(culledFloor, color);
		//setTransparency(culledWalls, color);
		if (transparent) {
			setTransparency(culledFloor, transparencyColor);
			setTransparency(culledWalls, transparencyColor);
		}
		else
		{
			setTransparency(culledFloor, originalColor);
			setTransparency(culledWalls, originalColor);
		}
	}

	void drawShadows(sf::RenderTexture& rt, std::vector<std::shared_ptr<Renderable>>& entities, sf::Shader& entityShader)
	{
		sf::RenderStates rs;
		rs.blendMode = sf::BlendAlpha;
		rs.shader = &entityShader;
		rt.draw(culledFloorShadows);
		if(culledFloorShadows.getVertexCount()> 0)
			for (auto& f : culledFloor)
			{
				rt.draw(f.second);
			}
		for (auto& iit : entities)
		{
			rt.draw(*(iit.get()), rs);
		}
		for (auto& w : culledWalls)
		{
			rt.draw(w.second);
		}
		rt.draw(culledShadows);
	}


	void Cull(const Core::Rect<float>& rect, const sf::Color& currentDayColor)
	{
		bool doNotReAdd = false;
		if (previousRect == rect)
			doNotReAdd = true;
		else
			renderedTiles = 0;
		auto tiles = tileTree.query(rect);
		culledShadows.clear();
		culledFloorShadows.clear();
		floorShadows.clear();
		shadows.clear();
		if (doNotReAdd == false)
			for (auto& x : textures)
			{
				culledFloor[x.first].clear();
				culledWalls[x.first].clear();
			}

		for (auto& tile : tiles)
		{
			//if (tile.hasShadow)
			//{
				if (tile.type == Enums::TileTypes::GroundShadow)
				{
					floorShadows.append(tile.mVertex[0]);
					floorShadows.append(tile.mVertex[1]);
					floorShadows.append(tile.mVertex[2]);
					floorShadows.append(tile.mVertex[3]);
					culledFloorShadows.append(tile.mVertex[0]);
					culledFloorShadows.append(tile.mVertex[1]);
					culledFloorShadows.append(tile.mVertex[2]);
					culledFloorShadows.append(tile.mVertex[3]);
				}
				else if (tile.type == Enums::TileTypes::WallShadow)
				{
					shadows.append(tile.mVertex[0]);
					shadows.append(tile.mVertex[1]);
					shadows.append(tile.mVertex[2]);
					shadows.append(tile.mVertex[3]);
					culledShadows.append(tile.mVertex[0]);
					culledShadows.append(tile.mVertex[1]);
					culledShadows.append(tile.mVertex[2]);
					culledShadows.append(tile.mVertex[3]);
				}
			//}
			if (doNotReAdd == false)
			{
				renderedTiles++;
				if (tile.type == Enums::TileTypes::Wall)
				{
					culledWalls[tile.theAtlas].append(tile.mVertex[0]);
					culledWalls[tile.theAtlas].append(tile.mVertex[1]);
					culledWalls[tile.theAtlas].append(tile.mVertex[2]);
					culledWalls[tile.theAtlas].append(tile.mVertex[3]);
				}
				else if (tile.type == Enums::TileTypes::Ground)
				{
					culledFloor[tile.theAtlas].append(tile.mVertex[0]);
					culledFloor[tile.theAtlas].append(tile.mVertex[1]);
					culledFloor[tile.theAtlas].append(tile.mVertex[2]);
					culledFloor[tile.theAtlas].append(tile.mVertex[3]);
				}
			}
		}
		SetColor(currentDayColor);

		//culledShadows.clear();
		//culledFloorShadows.clear();
		//Cull(rect, culledShadows, shadows);
		//Cull(rect, culledFloorShadows, floorShadows);
		//if (previousRect == rect)
		//	return;
		//
		//culledHitboxes.clear();
		//
		//for (auto& x : textures)
		//{
		//	culledFloor[x.first].clear();
		//	culledWalls[x.first].clear();
		//	Cull(rect, culledFloor[x.first], floor[x.first]);
		//	Cull(rect, culledWalls[x.first], walls[x.first]);
		//}
		culledHitboxes.clear();
		Cull(rect, culledHitboxes, hitboxes, 8);
		previousRect = rect;
	}

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};