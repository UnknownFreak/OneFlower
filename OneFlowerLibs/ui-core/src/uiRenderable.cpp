#include <graphics/ui/uiRenderable.hpp>

namespace of::graphics::ui
{
	float UIRenderable::getCenter(const ImVec4& relSize, const bool& width) const
	{
		if (width)
		{
			return (relSize.z / 2) - offsetX;
		}
		return (relSize.w / 2) - offsetY;
	}

	void UIRenderable::adjustRelation(ImVec4 relSize)
	{
		// IMGUI is x, y, z, w (so z is width)
		switch (m_windowRelation)
		{
		case Relation::TOP:
			m_renderBox.y = offsetY;
			m_renderBox.x = getCenter(relSize, true) - getCenter({ 0, 0, m_renderBox.z, m_renderBox.w }, true);
			break;
		case Relation::TOP_LEFT:
			m_renderBox.x = offsetX;
			m_renderBox.y = offsetY;
			break;
		case Relation::TOP_RIGHT:
			m_renderBox.x = relSize.z - (m_renderBox.z + offsetX);
			m_renderBox.y = offsetY;
			break;
		case Relation::LEFT:
			m_renderBox.x = offsetX;
			m_renderBox.y = getCenter(relSize, false) - getCenter({ 0, 0, m_renderBox.z, m_renderBox.w }, false);
			break;
		case Relation::RIGHT:
			m_renderBox.x = relSize.z - (m_renderBox.z + offsetX);
			m_renderBox.y = getCenter(relSize, false) - getCenter({ 0.f, 0.f, m_renderBox.z, m_renderBox.w }, false);
			break;
		case Relation::CENTER:
			m_renderBox.x = getCenter(relSize, true) - getCenter({ 0.f, 0.f, m_renderBox.z, m_renderBox.w }, true);
			m_renderBox.y = getCenter(relSize, false) - getCenter({ 0.f, 0.f, m_renderBox.z, m_renderBox.w }, false);
			break;
		case Relation::BOTTOM_LEFT:
			m_renderBox.x = offsetX;
			m_renderBox.y = relSize.w - (m_renderBox.w + offsetY);
			break;
		case Relation::BOTTOM_RIGHT:
			m_renderBox.x = relSize.z - (m_renderBox.z + offsetX);
			m_renderBox.y = relSize.w - (m_renderBox.w + offsetY);
			break;
		case Relation::BOTTOM:
			m_renderBox.x = getCenter(relSize, true) - getCenter({ offsetX, offsetY, m_renderBox.z, m_renderBox.w }, true);
			m_renderBox.y = relSize.w - (m_renderBox.w + offsetY);
			break;
		default:
			m_renderBox.x = offsetX;
			m_renderBox.y = offsetY;
		}
	}

	ImVec2 UIRenderable::getStart(ImVec4 relation)
	{

		return { relation.x + m_renderBox.x, relation.y + m_renderBox.y};
	}

	ImVec2 UIRenderable::getEnd(const ImVec2& size)
	{
		return {size.x + m_renderBox.z, size.y + m_renderBox.w};
	}

	void UIRenderable::debugDraw(const ImColor& color) const
	{
		auto x = ImGui::GetWindowDrawList();
		x->AddRect(ImVec2{ m_renderBox.x, m_renderBox.y }, ImVec2{ m_renderBox.x + m_renderBox.z, m_renderBox.y + m_renderBox.w }, color, 0.f, 0);
	}

	UIRenderable::UIRenderable(const ImVec4& renderBox, const Relation& relation) : m_renderBox(renderBox), m_windowRelation(relation), m_uiParent(nullptr), offsetX(renderBox.x), offsetY(renderBox.y)
	{
	}

	void UIRenderable::updateFrame(const float& dt)
	{
		if (m_uiParent)
		{
			adjustRelation(m_uiParent->m_renderBox);
		}
		else
		{
			adjustRelation({ 0.f, 0.f, (float)m_parent->getWindowWidth(), (float)m_parent->getWindowHeight() });
		}
		for (auto& child : m_children)
		{
			child->updateFrame(dt);
		}
	}

	void UIRenderable::render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, view::MVP& mvp)
	{

		beginRender();
		auto x = ImGui::GetWindowDrawList();

		ImVec4 relation;
		if (m_uiParent)
		{
			relation = m_uiParent->m_renderBox;
		}
		else
		{
			relation = { 0.f, 0.f, (float)m_parent->getWindowWidth(), (float)m_parent->getWindowHeight() };
		}
		auto start = getStart(relation);
		auto end = getEnd(start);

		x->PushClipRect(start, end, false);

		//x->AddRect(start, end, ImColor(255, 255, 255));
		render();
		for (auto& child : m_children)
		{
			child->render(transaction, mvp);
		}
		x->PopClipRect();

		endRender();
	}

	void UIRenderable::add(std::shared_ptr<UIRenderable> child)
	{
		child->m_uiParent = this;
		m_children.push_back(child);
	}
}