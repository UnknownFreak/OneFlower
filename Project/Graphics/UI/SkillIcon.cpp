#include "SkillIcon.hpp"

#include <module/resource/TextureLoader.hpp>

Graphics::UI::SkillIcon::SkillIcon(of::combat::Skill* skill) : UIContext(swizzle::input::Keys::KeyNone, "SkillIcon", false), skill(skill),
skillIcon(of::module::texture::get().requestTexture(skill->iconTextureName, of::engine::path::ui))
{
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

void Graphics::UI::SkillIcon::setPosition(const glm::vec2& newPos)
{
	pos = newPos;
}

void Graphics::UI::SkillIcon::update()
{
}

void Graphics::UI::SkillIcon::onMouseHover(const glm::vec2& mouse)
{
	if (mouseInside(pos, { 64.f, 64.f }, mouse))
	{

	}
}

void Graphics::UI::SkillIcon::readInput()
{
}

void Graphics::UI::SkillIcon::render()
{
}
