#ifndef NewFileModal_HPP
#define NewFileModal_HPP

#include <vector>
#include "ModalBase.hpp"

namespace Graphics
{
	namespace Editor
	{
		namespace Modals
		{
			class NewFile : public ModalBase
			{
				bool m_isOpen = false;
				Core::String m_fileName;
				bool isMaster = false;
				std::vector<std::pair<Core::String, bool>> modFiles;
				std::vector<std::pair<Core::String, Core::String>> dependencies;

				void loadDependencyDetails(const Core::String& file);
				void loadDependencyDetails(const Core::String& file, std::vector<std::pair<Core::String, Core::String>>& dependencies, const int index );

			public:

				NewFile(const Core::String& modalName);

				void ImGuiRenderModal() override;
				void OnOpen() override;


			};

		}
	}
}



#endif