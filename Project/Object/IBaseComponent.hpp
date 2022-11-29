#ifndef IBaseComponent_HPP
#define IBaseComponent_HPP
#include "BaseComponent.hpp"
#include <utils/common/string.hpp>
#include <Helpers/Enum/ComponentType.hpp>

#include <Module/EngineModuleManager.hpp>
#include <Module/Logger/OneLogger.hpp>

namespace Component
{
	template<typename>
	class IBase : public Base
	{
	public:

		virtual ~IBase() = default;

		Enums::ComponentType getType() const
		{
			return typeID;
		}
		of::common::String getTypeName() const
		{
			return componentName;
		}

		Base* copy() const {
			
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Component::IBase").Error("Component: " + getTypeName() + " is missing copy() override, it will always return nullptr");
			return nullptr;
		}

		std::unique_ptr<Base> ucopy() const
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Component::IBase").Error("Component: " + getTypeName() + " is missing ucopy() override, it will always return empty unique_ptr");
			return nullptr;
		}

		static of::common::String componentName;
		static Enums::ComponentType typeID;

	protected:

	private:
	};
}

#endif