// Lab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <module/ModuleManager.hpp>
#include <module/logger/OneLogger.hpp>
#include <utils/config/parser.hpp>
#include <module/window/GraphicsProxy.hpp>

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/map.hpp>

#include <file/archive/Requestable.hpp>

#include <map>
#include <File/FileId.hpp>
#include <common/uuid.hpp>
#include <common/string.hpp>

#include <file/archive/Requestor.hpp>

class Element : public of::file::archive::Requestable
{
public:
	struct Hash
	{
		size_t operator() (const Element& key) const noexcept
		{
			return std::hash<of::common::uuid>()(key.ID);
		}
	};
	Element() : of::file::archive::Requestable(of::file::ObjectType::Element) {};
	Element(const Element& copy) : of::file::archive::Requestable(copy) {};

	double damageToUnknownType = 0.0;
	std::map<of::file::FileId, double> elementAttributes;

	//sf::Color elementUiColor;

	double getElementModifier() const
	{
		return 1.0;
	}
	double getElementModifier(const of::file::FileId& ) const
	{
		return 0.0;
	}

	of::common::String getElementAttributeName(const of::file::FileId& ) const
	{
		return "";
	}

	bool operator==(const Element& other) const
	{
		return other.ID == ID;
	}

	template<class Archive>
	void load(Archive& ar)
	{
		ar(cereal::base_class<of::file::archive::Requestable>(this));
		//ar(cereal::base_class<IObject>(this));
		ar(elementAttributes);
		ar(damageToUnknownType);
		unsigned color;
		ar(color);
		//elementUiColor = sf::Color(color);
	}
	template<class Archive>
	void save(Archive& ar) const
	{
		ar(cereal::base_class<of::file::archive::Requestable>(this));
		//ar(cereal::base_class<IObject>(this));
		ar(elementAttributes);
		ar(damageToUnknownType);
		//ar(elementUiColor.toInteger());

	}

	// Inherited via IRequestable
	virtual of::file::archive::TypeInfo getTrait() const override
	{
		return { of::file::archive::Trait<Element>::typeId };
	}
	of::common::String getName() const override
	{
		return "name";
	}

};

of::common::uuid of::file::archive::Trait<Element>::typeId = of::common::uuid("1423d23c-e7d0-493a-9e03-0c68a1714703");

int main()
{
	of::file::archive::Requestor r;
	r.add(new Element);
    auto& x = of::engine::GetModule<of::module::window::Proxy>();
    system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
