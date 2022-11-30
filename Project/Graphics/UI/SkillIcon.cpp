#include "SkillIcon.hpp"
#include <File/Resource/TextureLoader.hpp>

Graphics::UI::SkillIcon::SkillIcon(Combat::Skill* skill) : UIContext(swizzle::input::Keys::KeyNone, "SkillIcon", false), skill(skill),
skillIcon(of::engine::GetModule<File::Resource::Texture::Loader>().requestTexture(skill->iconTextureName, Globals::uiTexturePath))
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
