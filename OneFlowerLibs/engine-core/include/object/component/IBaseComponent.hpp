#ifndef IBaseComponent_HPP
#define IBaseComponent_HPP
#include "BaseComponent.hpp"
#include <utils/common/string.hpp>

#include <utils/common/uuid.hpp>

//#include <Helpers/Enum/ComponentType.hpp>

#include <Module/ModuleManager.hpp>
#include <Module/Logger/OneLogger.hpp>

namespace of::object::component
{
	template<typename>
	class IBase : public Base
	{
	public:

		virtual ~IBase() = default;

		of::common::uuid getType() const
		{
			return typeID;
		}

		of::common::String getTypeName() const
		{
			return componentName;
		}

		Base* copy() const {
			
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("Component::IBase").Error("Component: " + getTypeName() + " is missing copy() override, it will always return nullptr");
			return nullptr;
		}

		std::unique_ptr<Base> ucopy() const
		{
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("Component::IBase").Error("Component: " + getTypeName() + " is missing ucopy() override, it will always return empty unique_ptr");
			return nullptr;
		}

		static of::common::String componentName;
		static of::common::uuid typeID;

	protected:

	private:
	};
}

#endif