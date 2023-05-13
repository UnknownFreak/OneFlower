#pragma once

#include "modalBase.hpp"

#include <vector>

namespace of::imgui
{
	class FileSelector : public ModalBase
	{
		of::common::String m_selectedFile;
		bool fileSelected = false;
		const of::common::String m_path;
		const of::common::String m_fileExtension;
		std::vector<std::pair<of::common::String, bool>> m_fileNames;
		void load();
	public:

		FileSelector(const of::common::String& modalName, const of::common::String& path, const of::common::String& fileExt);

		void ImGuiRenderModal() override;
		void OnOpen() override;

		bool hasFileBeenSelected();
		of::common::String getSelectedFile();

	};
}