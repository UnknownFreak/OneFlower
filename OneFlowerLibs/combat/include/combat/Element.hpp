#pragma once
#ifndef Element_HPP
#define Element_HPP

#include <cereal/cereal.hpp>
#include <cereal/types/map.hpp>

#include <file/archive/Requestable.hpp>

#include <utils/common/string.hpp>

#include <map>
#include <File/FileId.hpp>

namespace Combat
{
	class Element : public of::file::archive::Requestable
	{
		public:
			struct Hash
			{
				size_t operator() (const Combat::Element& key) const noexcept
				{
					return std::hash<of::common::uuid>()(key.ID);
				}
			};
		Element();
		Element(const Element& copy);

		of::common::String name;
		double damageToUnknownType = 0.0;
		std::map<of::file::FileId, double> elementAttributes;

		//sf::Color elementUiColor;

		double getElementModifier() const;
		double getElementModifier(const of::file::FileId& element) const;

		of::common::String getElementAttributeName(const of::file::FileId& element) const;

		bool operator==(const Element& other) const;

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Requestable>(this));
			ar(name);
			ar(elementAttributes);
			ar(damageToUnknownType);
			//unsigned color;
			//ar(color);
			//elementUiColor = sf::Color(color);
		}
		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Requestable>(this));
			ar(name);
			ar(elementAttributes);
			ar(damageToUnknownType);
			//ar(elementUiColor.toInteger());

		}

		// Inherited via IRequestable
		virtual of::file::archive::TypeInfo getTrait() const override;

		virtual void render() override;

		of::common::String getName() const override;

	};
}

CEREAL_REGISTER_TYPE(Combat::Element);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, Combat::Element);

#endif