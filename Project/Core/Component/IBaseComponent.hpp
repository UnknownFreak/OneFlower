#ifndef IBaseComponent_HPP
#define IBaseComponent_HPP
#include "BaseComponent.hpp"
#include <string>
#ifdef _DEBUG
//#include "../../Engine/Editor/BaseField.hpp"
//#include "../../Engine/Editor/EditorField.hpp"
#endif
namespace Component
{
	template<typename>
	class IBaseComponent : public Base
	{
	public:

		const size_t getType()
		{
			return typeID;
		}
		Core::String getTypeName()
		{
			return componentName;
		}

		Base* copy() const {
			return nullptr;
		}

		static Core::String componentName;
		static const size_t typeID;

	protected:

	private:
	#ifdef _DEBUG
		//std::map<std::string,BaseField*> getFields()
		//{
		//	return editorFields;
		//}
		/*
		~IBaseComponent()
		{
			for(std::map<std::string,BaseField*>::iterator it = editorFields.begin(); it != editorFields.end(); ++it)
			{
				delete it->second;
				it->second = 0;
			}
		}
		//*/
		//HIGH: Friendclass stuffz so you can put this into private
		//std::map<std::string,BaseField*> editorFields;
	#endif
	};
}

#endif