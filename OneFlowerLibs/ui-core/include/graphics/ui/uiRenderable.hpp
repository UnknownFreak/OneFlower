#pragma once
#include <graphics/parentedRenderable.hpp>
#include <graphics/ui/relation.hpp>
#include <imgui/imgui.h>

namespace of::graphics::ui
{

	class UIRenderable : public ParentedRenderable
	{
		float getCenter(const ImVec4&, const bool& width) const;
		void adjustRelation(ImVec4 relSize);

		ImVec2 getStart(ImVec4 relSize);
		ImVec2 getEnd(const ImVec2& start);

	protected:

		UIRenderable* m_uiParent;
		std::vector<std::shared_ptr<UIRenderable>> m_children;
		ImVec4 m_renderBox;
		float offsetX;
		float offsetY;

		virtual void debugDraw(const ImColor& color) const;

	public:
		Relation m_windowRelation;

		UIRenderable(const ImVec4& renderBox, const Relation& relation = Relation::TOP_LEFT);
		virtual void updateFrame(const float dt) override;
		virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, view::MVP& mvp) override;

		virtual void beginRender() = 0;
		virtual void render() = 0;
		virtual void endRender() = 0;

		void add(std::shared_ptr<UIRenderable> child);

	};

}