#ifndef IObject_HPP
#define IObject_HPP

#include "ISaveable.hpp"

#include <Helpers/uuid.hpp>

namespace Interfaces
{

	class IObject : public ISaveable {

	public:

		inline IObject() : IObject("") {} 
		inline IObject(const Core::String& name) : identifier(Core::uuid()), tag(), name(name) {}
		inline IObject(const IObject& copy) : identifier(copy.identifier), tag(copy.tag), name(copy.name) {}
		inline IObject& operator= (const IObject& left) {
			if (left.identifier == identifier)
				return *this;
			identifier = left.identifier;
			tag = left.tag;
			name = left.name;
			return *this;
		}

		Core::uuid identifier;
		Core::String tag;
		Core::String name;

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