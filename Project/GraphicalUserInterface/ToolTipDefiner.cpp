#include "ToolTip.hpp"
#include "../Engine.hpp"
#include "../Component/EquipmentComponent.hpp"
#include "../Item/Armor.hpp"
ToolTip::ToolTip() : toolTipText("test.png",*Engine::Graphic.font.requestFont("arial.ttf"),false), toolTipBody("test.png",*Engine::Graphic.font.requestFont("arial.ttf"),false), toolTipIcon(*Engine::Graphic.requestTexture("ToolTipIcon.png"))
{
	toolTipText.setSize(21);
	toolTipBody.setSize(13);
}

ToolTip::ToolTip(std::string name) : toolTipText("test.png",*Engine::Graphic.font.requestFont("arial.ttf"),false), toolTipBody("test.png",*Engine::Graphic.font.requestFont("arial.ttf"),false), toolTipIcon(*Engine::Graphic.requestTexture("ToolTipIcon.png"))
{
	toolTipText = name;
	toolTipText.setSize(21);
	toolTipBody.setSize(13);
	toolTipIcon.setTextureRect(sf::IntRect(0, 0, (int)toolTipText.entireString.getLocalBounds().width + 24, (int)toolTipText.entireString.getLocalBounds().height + 24));
}
ToolTip::ToolTip(std::string name, std::string icon) : toolTipText("test.png", *Engine::Graphic.font.requestFont("arial.ttf"), false), toolTipBody("test.png", *Engine::Graphic.font.requestFont("arial.ttf"), false), toolTipIcon(*Engine::Graphic.requestTexture(icon))
{
	toolTipText = name;
	toolTipText.setSize(21);
	toolTipBody.setSize(13);
	toolTipIcon.setTextureRect(sf::IntRect(0, 0, (int)toolTipText.entireString.getLocalBounds().width + 24, (int)toolTipText.entireString.getLocalBounds().height + 24));
}
ToolTip::ToolTip(std::string name, std::string body, std::string icon) : toolTipText("test.png", *Engine::Graphic.font.requestFont("arial.ttf"), false), toolTipBody("test.png", *Engine::Graphic.font.requestFont("arial.ttf"), false), toolTipIcon(*Engine::Graphic.requestTexture(icon))
{
	toolTipText.setSize(21);
	toolTipBody.setSize(13);
	setToolTipText(name, body);
}
ToolTip::ToolTip(const ToolTip& copy) : toolTipText(copy.toolTipText), toolTipBody(copy.toolTipBody), toolTipIcon(copy.toolTipIcon)
{
}
void ToolTip::setPosition(double x, double y)
{
	float width = Engine::View.camera.getSize().x;
	float height = Engine::View.camera.getSize().y;

	x += 8;
	y -= 16;
	double dy = y - toolTipIcon.getTextureRect().height + 12;
	if (x + toolTipIcon.getTextureRect().width + 24 > Engine::View.camera.getCenter().x + width / 2)
		x -= toolTipIcon.getTextureRect().width + 24;
	if (!(dy > Engine::View.camera.getCenter().y - height / 2))
		dy = y + 24;
	if (toolTipText.entireString.getString() != "")
	{
		toolTipText.setPosition(x + 12, dy + 4);
		toolTipBody.setPosition(x + 12, dy + 28);
		toolTipIcon.setPosition(x, dy);
	}
	else
	{
		toolTipBody.setPosition(x + 12, dy + 4);
		toolTipIcon.setPosition(x, dy);
	}
}
void ToolTip::draw()
{
	setPosition(Engine::GUI.mouseAim.position.x, Engine::GUI.mouseAim.position.y);
	Engine::View.render.draw(toolTipIcon);
	toolTipText.draw();
	toolTipBody.draw();
}
void ToolTip::setToolTipText(std::string _text, std::string _body)
{
	toolTipText = _text;
	
	if (_body != toolTipBody.entireString.getString())
	{
		toolTipBody = _body;
		sf::Text sizeString("", toolTipBody.font, toolTipBody.size);
		std::string lines = "";
		for (std::vector<std::pair<sf::Text, bool>>::iterator it = toolTipBody.text.begin(); it != toolTipBody.text.end(); it++)
		{
			if (it->second)
				lines += it->first.getString();
			else
				lines += it->first.getString()+"\n";
		}
		lines.pop_back();
		sizeString.setString(lines);
		float tmp = 0;
		if (toolTipText.entireString.getLocalBounds().width < sizeString.getLocalBounds().width)
			tmp = sizeString.getLocalBounds().width;
		else
			tmp = toolTipText.entireString.getLocalBounds().width;
		toolTipIcon.setTextureRect(sf::IntRect(0, 0, tmp + 24, (int)toolTipText.entireString.getLocalBounds().height + (int)sizeString.getLocalBounds().height + 10 + 24));
	}
}
void ToolTip::draw(std::string text)
{
	setToolTipText(text);
	setPosition(Engine::GUI.mouseAim.position.x, Engine::GUI.mouseAim.position.y);
	Engine::View.render.draw(toolTipIcon);
	toolTipText.draw();
}
void ToolTip::draw(std::string title, std::string _body)
{
	setToolTipText(title, _body);
	setPosition(Engine::GUI.mouseAim.position.x, Engine::GUI.mouseAim.position.y);
	Engine::View.render.draw(toolTipIcon);
	toolTipText.draw();
	toolTipBody.draw();
}
const std::string ToolTip::getToolTipTitle()
{
	return toolTipText.entireString.getString();
}
const std::string ToolTip::getToolTipBody()
{
	return toolTipBody.entireString.getString();
}
ToolTip& ToolTip::operator=(const ToolTip& copy)
{
	this->toolTipBody = copy.toolTipBody;
	this->toolTipIcon = copy.toolTipIcon;
	this->toolTipText = copy.toolTipText;
	return *this;
}
