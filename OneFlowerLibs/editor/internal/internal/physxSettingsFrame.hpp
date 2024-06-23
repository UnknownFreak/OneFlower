#pragma once

#include <graphics/parentedRenderable.hpp>

#include <imgui/imgui.h>

#include "physics/physics.hpp"

namespace of::editor
{


	class PhysxSettingsFrame : public of::graphics::ParentedRenderable
	{
		std::vector<of::common::String> m_groupNames;
		bool m_visible;
	public:

		PhysxSettingsFrame() : m_visible(false)
		{
			m_groupNames.push_back("Terrain");
			m_groupNames.push_back("Doors");
			m_groupNames.push_back("Player");
			m_groupNames.push_back("Actors");
			m_groupNames.push_back("TrigPlayer");
			m_groupNames.push_back("TrigActor");
		}

		virtual void updateFrame(const float ) override {};

		void open()
		{
			m_visible = true;
		}

		virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>&, of::graphics::view::MVP&)
		{
			if (m_visible)
			{
				if (ImGui::Begin("Physx settings", &m_visible, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking))
				{
					ImGui::Text("Simulation Groups");
					ImGui::NewLine();
					const size_t count = m_groupNames.size();
					if (ImGui::BeginTable("Sim groups", (int)count + 1, ImGuiTableFlags_SizingFixedFit))
					{
						ImGui::TableSetupColumn("", ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoReorder);
						for (size_t cols = 0; cols < count; cols++)
						{
							ImGui::TableSetupColumn(m_groupNames[cols].c_str(), ImGuiTableColumnFlags_AngledHeader);
						}
						ImGui::TableAngledHeadersRow();
						for (size_t i = 0; i < count; i++)
						{
							ImGui::TableNextRow();
							ImGui::TableNextColumn();
							ImGui::Text(m_groupNames[i].c_str());
							for (size_t j = 0; j < count; j++)
							{
								ImGui::TableNextColumn();
									bool b = physx::PxGetGroupCollisionFlag((physx::PxU16)i, (physx::PxU16)j);
								char buf[32];
								sprintf_s(buf, "###%d-%d", (int)i, (int)j);
								if (ImGui::Checkbox(buf, &b))
									{
										physx::PxSetGroupCollisionFlag((physx::PxU16)i, (physx::PxU16)j, b);
									}
							}
						}
						ImGui::EndTable();
					}

					ImGui::Text("Query groups");
				}
				ImGui::End();
			}
		}
	};
}