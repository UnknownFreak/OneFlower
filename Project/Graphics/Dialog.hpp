#ifndef DialogComponent_HPP
#define DialogComponent_HPP

#include <Helpers/Enum/InteractionOption.hpp>
#include <Helpers/Enum/DialogStatus.hpp>

#include <file/Handler.hpp>
#include <File/Asset/Resource/DialogTree.hpp>

#include <object/component/IBaseComponent.hpp>
#include <object/component/Transform.hpp>

#include <file/FileId.hpp>

class Dialog : public of::object::component::IBase<Dialog>
{
	virtual void onMessage(const of::object::messaging::Message& message) override;

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

	void reset();
	// maybe not needed
	void attachOn(of::object::GameObject* go);
	// Inherited via IBase
	virtual void onCollision(of::object::GameObject* the_collidee) override;


	// Inherited via IBase
	virtual void Update() override;

	virtual void Simulate(const float& fElapsedTime) override;
	virtual void onDeath() override;
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
};

CEREAL_REGISTER_ARCHIVE(Dialog);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::object::component::Base, Dialog);

#endif
