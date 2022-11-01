#pragma once
#ifndef Element_HPP
#define Element_HPP

#include <cereal/cereal.hpp>

#include <Interfaces/IRequestable.hpp>
#include <Interfaces/IObject.hpp>

#include <map>
#include <File/Mod/ModFileUUIDHelper.hpp>

namespace Combat
{
	class Element : public Interfaces::IRequestable, public Interfaces::IObject
	{
		public:
			struct Hash
			{
				size_t operator() (const Combat::Element& key) const noexcept
				{
					return std::hash<Core::uuid>()(key.ID);
				}
			};
		Element();
		Element(const Element& copy);

		double damageToUnknownType = 0.0;
		std::map<File::Mod::ModFileUUIDHelper, double> elementAttributes;

		//sf::Color elementUiColor;

		double getElementModifier() const;
		double getElementModifier(const File::Mod::ModFileUUIDHelper& element) const;

		Core::String getElementAttributeName(const File::Mod::ModFileUUIDHelper& element) const;

		bool operator==(const Element& other) const;

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IRequestable>(this));
			ar(cereal::base_class<IObject>(this));
			ar(elementAttributes);
			ar(damageToUnknownType);
			unsigned color;
			ar(color);
			//elementUiColor = sf::Color(color);
		}
		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IRequestable>(this));
			ar(cereal::base_class<IObject>(this));
			ar(elementAttributes);
			ar(damageToUnknownType);
			//ar(elementUiColor.toInteger());

		}

		// Inherited via IRequestable
		virtual Interfaces::TypeInfo getTrait() const override;

		virtual void render() override;

		Core::String getName() const override;

	};
}

#endif