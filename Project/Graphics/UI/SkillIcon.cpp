#include "SkillIcon.hpp"
#include <File/Resource/TextureLoader.hpp>

Graphics::UI::SkillIcon::SkillIcon(Combat::Skill* skill) : UIContext(sf::Keyboard::Key::Unknown, "SkillIcon", false), buf(sf::PrimitiveType::Quads, sf::VertexBuffer::Usage::Dynamic), skill(skill),
skillIcon(Engine::GetModule<TextureLoader>().requestTexture(skill->iconTextureName, Globals::uiTexturePath))
{
	buf.create(8);
	setPosition({ 0,0 });
}

Graphics::UI::SkillIcon::SkillIcon(const SkillIcon& copy) : SkillIcon(copy.skill)
{
}

//Graphics::UI::SkillIcon& Graphics::UI::SkillIcon::operator=(const SkillIcon& other)
//{
//	skillIcon = other.skillIcon;
//	skill = other.skill;
//	*vertices = *other.vertices;
//	buf = other.buf;
//	buf.update(vertices);
//	return *this;
//}

void Graphics::UI::SkillIcon::setPosition(const Core::Vector2f& newPos)
{
	pos = newPos;
	vertices[0].position = { pos.x, pos.y };
	vertices[1].position = { pos.x, pos.y + 64.f };
	vertices[2].position = { pos.x + 64.f, pos.y + 64.f };
	vertices[3].position = { pos.x + 64.f, pos.y };

	vertices[0].texCoords = { 0, 0 };
	vertices[1].texCoords = { 0, 64.f };
	vertices[2].texCoords = { 64.f, 64.f };
	vertices[3].texCoords = { 64.f, 0};

	// logic to calculate cd icon shape
	//vertices[4].position = { pos.x, pos.y };
	//vertices[5].position = { pos.x, pos.y + 64.f };
	//vertices[6].position = { pos.x + 64.f, pos.y + 64.f };
	//vertices[7].position = { pos.x + 64.f, pos.y };

	buf.update(vertices);
	
}

void Graphics::UI::SkillIcon::update()
{
}

void Graphics::UI::SkillIcon::onMouseHover(const Core::Vector2f& mouse)
{
	if (mouseInside(pos, { 64.f, 64.f }, mouse))
	{

	}
}

void Graphics::UI::SkillIcon::readInput()
{
}

void Graphics::UI::SkillIcon::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(buf, skillIcon.get());
}
