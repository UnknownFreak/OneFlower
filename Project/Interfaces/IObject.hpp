#ifndef IObject_HPP
#define IObject_HPP

#include <utils/common/uuid.hpp>

namespace Interfaces
{

	class IObject {

	public:

		inline IObject() : IObject("") {} 
		inline IObject(const of::common::String& name) : identifier(of::common::uuid()), tag(), name(name) {}
		inline IObject(const IObject& copy) : identifier(copy.identifier), tag(copy.tag), name(copy.name) {}
		inline IObject& operator= (const IObject& left) {
			if (left.identifier == identifier)
				return *this;
			identifier = left.identifier;
			tag = left.tag;
			name = left.name;
			return *this;
		}

		of::common::uuid identifier;
		of::common::String tag;
		of::common::String name;

		template<class Archive>
		void save(Archive& saver) const
		{
			saver(identifier);
			saver(tag);
			saver(name);
		}
		template <class Archive>
		void load(Archive& loader)
		{
			loader(identifier);
			loader(tag);
			loader(name);
		}
	};
}

#endif