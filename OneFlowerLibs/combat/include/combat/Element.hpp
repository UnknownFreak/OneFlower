#pragma once

#include <utils/expose/expose.hpp>

#include <cereal/cereal.hpp>
#include <cereal/types/map.hpp>

#include <asset/iAsset.hpp>

#include <utils/common/string.hpp>

#include <map>
#include <asset/assetId.hpp>


namespace of::combat
{
	class Element : public of::asset::IAsset
	{
		template <class T> friend class of::expose::ExposeToEditor;
		public:
			struct Hash
			{
				size_t operator() (const of::combat::Element& key) const noexcept
				{
					return std::hash<of::common::uuid>()(key.ID);
				}
			};
		Element();
		Element(const Element& copy);

		of::common::String name;
		double damageToUnknownType = 0.0;
		std::map<of::asset::AssetId, double> elementAttributes;

		//sf::Color elementUiColor;

		double getElementModifier() const;
		double getElementModifier(const of::asset::AssetId& element) const;

		of::common::String getElementAttributeName(const of::asset::AssetId& element) const;

		bool operator==(const Element& other) const;

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IAsset>(this));
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
			ar(cereal::base_class<IAsset>(this));
			ar(name);
			ar(elementAttributes);
			ar(damageToUnknownType);
			//ar(elementUiColor.toInteger());

		}

		// Inherited via IRequestable
		virtual of::asset::TypeInfo getTrait() const override;

		of::common::String getName() const override;

	};
}

CEREAL_REGISTER_TYPE(of::combat::Element);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::asset::IAsset, of::combat::Element);
