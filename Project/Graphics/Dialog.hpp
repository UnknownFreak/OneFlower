#ifndef DialogComponent_HPP
#define DialogComponent_HPP

#include <Helpers/Enum/InteractionOption.hpp>
#include <Helpers/Enum/DialogStatus.hpp>

#include <file/Handler.hpp>
#include <File/Asset/Resource/DialogTree.hpp>

#include <component/transform.hpp>

#include <file/FileId.hpp>

class Dialog : public of::component::Base
{
	virtual void onMessage(const of::object::messaging::Message& message) override;
	virtual void attached() override;
	virtual void deconstruct() override;
	virtual void initialize() override;

public:
	of::file::FileId dialogTreeuuid;

	Asset::Resource::DialogTree dialogTree;

public:
	//Dialog();
	//Dialog(const Dialog& copy);
	//~Dialog();

	virtual Enums::DialogStatus navigate(const Enums::InteractionOption& navigation);
	void visualSelect(const glm::vec2& mousePosition);
	virtual of::common::String getCurrentText();

	virtual std::vector<of::common::String> getDialogOptions();

	virtual Dialog* copy() const override
	{
		return new Dialog(*this);
	}

	virtual std::unique_ptr<Base> ucopy() const override
	{
		return std::make_unique<Dialog>(*this);
	}

	void reset();

	//void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void persist(of::object::ObjectSaveState*) override {};
	void onReconstruct(of::object::ObjectSaveState*) override {};
	void resolveReferences() override {};

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(dialogTreeuuid);
	}
	
	template<class Archive>
	void load(Archive& ar)
	{
		ar(dialogTreeuuid);
		dialogTree = of::engine::GetModule<of::file::Handler>().archive.request<Asset::Resource::DialogTree>(dialogTreeuuid);
	}

	of::common::uuid getType() const override
	{
		return typeId;
	};

	of::common::String getTypeName() const override
	{
		return "Dialog";
	};

	static constexpr of::common::uuid typeId = "54f0116b-25fc-422a-82ed-bb2ff6c60820";
};

CEREAL_REGISTER_ARCHIVE(Dialog);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::component::Base, Dialog);

#endif
