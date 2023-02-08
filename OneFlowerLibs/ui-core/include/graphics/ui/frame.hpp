#pragma once
#include <graphics/ui/uiRenderable.hpp>

#include <utils/common/uuid.hpp>

namespace of::graphics::ui
{

	class Frame : public UIRenderable
	{

		of::common::uuid m_frameId;
		of::common::String m_frameIdString;

	public:
		Frame(const ImVec4& frameSize, const Relation& relation);
		// Inherited via UIRenderable
		virtual void beginRender() override;
		virtual void render() override;
		virtual void endRender() override;
	};
}