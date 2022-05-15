#ifndef DialogComponent_HPP
#define DialogComponent_HPP

#include <Helpers/Enum/InteractionOption.hpp>
#include <Helpers/Enum/DialogStatus.hpp>

#include <File/Asset/Manager.hpp>
#include <File/Asset/Resource/DialogTree.hpp>

#include <Object/IBaseComponent.hpp>
#include <Object/Transform.hpp>

#include <File/Mod/ModFileUUIDHelper.hpp>

class Dialog : public Component::IBase<Dialog>
{
public:
	File::Mod::ModFileUUIDHelper dialogTreeuuid;

	Asset::Resource::DialogTree dialogTree;

public:
	//Dialog();
	//Dialog(const Dialog& copy);
	//~Dialog();

	virtual Enums::DialogStatus navigate(const Enums::InteractionOption& navigation);
	void visualSelect(const glm::vec2& mousePosition);
	virtual Core::String getCurrentText();

	virtual std::vector<Core::String> getDialogOptions();

	virtual Dialog* copy() const override
	{
		return new Dialog(*this);
	}

	void reset();
	// maybe not needed
	void attachOn(GameObject* go);
	// Inherited via IBase
	virtual void onCollision(Interfaces::ICollider* the_collidee) override;


	// Inherited via IBase
	virtual void Update() override;

	virtual void Simulate(const float& fElapsedTime) override;
	virtual void onDeath() override;
	//void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(dialogTreeuuid);
	}
	
	template<class Archive>
	void load(Archive& ar)
	{
		ar(dialogTreeuuid);
		dialogTree = Engine::GetModule<File::Asset::Manager>().getDialogTree().request(dialogTreeuuid);
	}
};
#endif
