#ifdef _EDITOR_
#include "CppInterop.hpp"
namespace ManagedGame
{
	std::string toString(String^ string)
	{
		msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
		return _mc->marshal_as<std::string>(string);
	}
	template<class T>
	std::string toString(T^ value)
	{
		msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
		return _mc->marshal_as<std::string>(System::Convert::ToString(value));
	}
	bool toBoolean(Boolean^ b)
	{
		if (b->ToString() == "True")
		return true;
		return false;
	}
	template<class T>
	int toInt(T value)
	{
		msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
		return std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(value)));
	}
#pragma region Main
	ManagedGame::~ManagedGame()
	{
		delete mc;
	}
	bool ManagedGame::isModLoaded()
	{
		return Engine::World.openedMod != "<Not Set>";
	}
	void ManagedGame::TestAdd()
	{
		mc->lock();
		mc->TestAdd();
		mc->unlock();
	}
	void ManagedGame::ManagedWindowLoop()
	{
		mc->windowMessage();
	}
	void ManagedGame::ManagedQuit()
	{
		mc->quit();
	}
	void ManagedGame::setUpWindows(IntPtr^ handle)
	{
		mc = new NativeContainer((HWND)handle->ToPointer());
	}
	bool ManagedGame::getRightClickedObject()
	{
		//mc->lock();
		GameObject* mine = Engine::Input.mouse.mySelected;
		if (mine != nullptr)
		{
			TransformComponent* transform = mine->GetComponent<TransformComponent>();
			RenderComponent* rc = mine->GetComponent<RenderComponent>();
			int localStartX = transform->position.x;
			int localStartY = transform->position.y;
			int localEndX = transform->position.x + rc->sprite.getTextureRect().width;
			int localEndY = transform->position.y + rc->sprite.getTextureRect().height;

			if (Engine::Input.mouse.pos.x >= localStartX && Engine::Input.mouse.pos.x <= localEndX)
				if (Engine::Input.mouse.pos.y >= localStartY && Engine::Input.mouse.pos.y <= localEndY)
				{
					return true;
				}
		}
		//mc->unlock();
		return false;
	}
	void ManagedGame::showHideHitboxes()
	{
		mc->lock();
		mc->showHideHitboxes();
		mc->unlock();
	}
#pragma endregion
#pragma region Prefabs
	List<String^>^ ManagedGame::getEntityNames(String^ string)
	{
		List<String^>^ list = gcnew List<String^>();
		std::string str = toString(string);
		for each (std::string var in Engine::ModelContainer.getEntities(Engine::ModelContainer.getModel(str)))
		{
			list->Add(gcnew String(var.c_str()));
		}
		return list;
	}
	List<String^>^ ManagedGame::getSceneFiles()
	{
		List<String^>^ list = gcnew List<String^>();
		for each (std::pair<std::string ,SpriterTextureMapper*> var in Engine::ModelContainer.modelTextureMapper)
		{
			list->Add(gcnew String(var.first.c_str()));
		}
		return list;
	}
	List<String^>^ ManagedGame::getTextureMaps(String^ str)
	{
		List<String^>^ list = gcnew List<String^>();
		for each (auto var in Engine::ModelContainer.getTextureMaps(toString(str)))
		{
			std::string str = var.first.first + ", " + var.first.second;
			list->Add(gcnew String(str.c_str()));
		}
		return list;
	}
	void ManagedGame::removeSpriterModel(String^ sceneFile)
	{
		mc->lock();
		Engine::ModelContainer.removeModel(toString(sceneFile));
		mc->unlock();
	}
	Dictionary<String^, TextureMapPointStruct^>^ ManagedGame::getTextureMapPoints(String^ model, String^ modName, String^ textureMap)
	{
		Dictionary<String^, TextureMapPointStruct^>^ points = gcnew Dictionary<String^, TextureMapPointStruct^>();
		mc->lock();
		auto textureMapPoints = Engine::ModelContainer.getTextureMapPoints(toString(model), toString(modName), toString(textureMap));
		mc->unlock();
		for each (auto var in textureMapPoints)
		{
			TextureMapPointStruct^ tmp = gcnew TextureMapPointStruct();
			tmp->pos = gcnew Tuple<int, int>(var.second.pos.x, var.second.pos.y);
			tmp->size = gcnew Tuple<int, int>(var.second.size.x, var.second.size.y);
			if (var.second.rotated)
				tmp->rotated = true;
			tmp->r = var.second.color.r;
			tmp->g = var.second.color.g;
			tmp->b = var.second.color.b;
			points->Add(gcnew String(var.first.c_str()), tmp);
		}
		return points;
	}
	void ManagedGame::addTextureMap(String^ model, String^ textureMap)
	{
		Engine::ModelContainer.addTextureMap(toString(model),Engine::World.openedMod, toString(textureMap));
	}
	void ManagedGame::removeTextureMap(String^ model, String^ modName, String^ textureMap)
	{
		Engine::ModelContainer.removeTextureMap(toString(model), toString(modName), toString(textureMap));
	}
	void ManagedGame::setPointPosition(String^ model, String^ modName, String^ TextureMap, String^ pointName, TextureMapPointStruct^ point)
	{
		TextureMapPoint p;
		p.pos.x = point->pos->Item1;
		p.pos.y = point->pos->Item2;
		p.size.x = point->size->Item1;
		p.size.y = point->size->Item2;
		Console::WriteLine("ispointrotated - before " + point->rotated->ToString() );
		if (point->rotated->ToString() == "True")
			p.rotated = true;
		else
			p.rotated = false;
		Console::WriteLine("ispointrotated - after " + p.rotated);
		p.color.r = point->r;
		p.color.g = point->g;
		p.color.b = point->b;
		Engine::ModelContainer.setTextureMapPoint(toString(model), toString(modName), toString(TextureMap), toString(pointName), p);
	}
	void ManagedGame::setPrefabPreview(IntPtr^ handle)
	{
		mc->setGameObjectPreviewHandle((HWND)handle->ToPointer());
	}
	void ManagedGame::previewPrefab(PrefabStruct^ prefab)
	{
#pragma region Render
		if (toBoolean(prefab->rc->isUsed))
		{
			RenderComponent* render = new RenderComponent();
			int a = toInt(prefab->rc->animationType);
			if (a == 0)
				render->animation = RenderComponent::AnimationType::Static;
			else if (a == 1)
				render->animation = RenderComponent::AnimationType::SpriteSheet;
			else
				render->animation = RenderComponent::AnimationType::Armature;
			render->textureName = toString(prefab->rc->textureName);
			if (render->textureName == "")
				render->textureName = "test.png";
			if (render->animation == RenderComponent::AnimationType::SpriteSheet)
			{
				for each (auto var in prefab->rc->animations)
				{
					SpriteSheetAnimation anim;
					anim.AnimationTime = std::stoi(toString(var->time));
					anim.looping = toBoolean(var->loop);
					for each (auto rects in var->textureRect)
					{
						anim.AnimationFrames.push_back(sf::IntRect(toInt(rects->Item1), toInt(rects->Item2), toInt(rects->Item3), toInt(rects->Item4)));
					}
					render->animations.insert(std::pair<std::string, SpriteSheetAnimation>(toString(var->name), anim));
				}
			}
			else if (render->animation == RenderComponent::AnimationType::Armature)
			{
				render->instance.entityName = toString(prefab->rc->spriterEntity);
				render->instance.sceneFile = toString(prefab->rc->spriterScene);
				render->instance.myTextureMap.first = toString(prefab->rc->textureMapMod);
				render->instance.myTextureMap.second = toString(prefab->rc->textureMapName);
			}
			mc->setGameObjectRenderPreview(render);
		}
		else
			mc->setGameObjectRenderPreview(NULL);
#pragma endregion
#pragma region Hitboxes
		if (toBoolean(prefab->hitbox->isUsed))
		{
			HitboxComponent* hitbox = new HitboxComponent();
			int x = toInt(prefab->hitbox->posX);
			int y = toInt(prefab->hitbox->posY);
			int sx = toInt(prefab->hitbox->sizeX);
			int sy = toInt(prefab->hitbox->sizeY);

			hitbox->bounding.position = Vector2(x, y);
			hitbox->bounding.size = Vector2(sx, sy);

			mc->setGameObjectHitboxPreview(hitbox);
		}
		else
			mc->setGameObjectHitboxPreview(NULL);
#pragma endregion
	}
	void ManagedGame::addPrefab(PrefabStruct^ prefab)
	{
		Prefab p;
		p.fromMod = toString(prefab->fromMod);
		p.name = toString(prefab->name);
		p.ID = toInt(prefab->ID);
		p.tag = toString(prefab->tag);
		if (toBoolean(prefab->rc->isUsed))
		{
		#pragma region Render
			RenderComponent* render = new RenderComponent();
			int a = toInt(prefab->rc->animationType);
			if (a == 0)
				render->animation = RenderComponent::AnimationType::Static;
			else if (a == 1)
				render->animation = RenderComponent::AnimationType::SpriteSheet;
			else
				render->animation = RenderComponent::AnimationType::Armature;
			render->textureName = toString(prefab->rc->textureName);
			render->size.x = toInt(prefab->rc->sizeX);
			render->size.y = toInt(prefab->rc->sizeY);
			if (render->textureName == "")
				render->textureName = "test.png";
			if (render->animation == RenderComponent::AnimationType::SpriteSheet)
			{
				for each (auto var in prefab->rc->animations)
				{
					SpriteSheetAnimation anim;
					anim.AnimationTime = std::stoi(toString(var->time));
					anim.looping = toBoolean(var->loop);
					for each (auto rects in var->textureRect)
					{
						anim.AnimationFrames.push_back(sf::IntRect(toInt(rects->Item1), toInt(rects->Item2), toInt(rects->Item3), toInt(rects->Item4)));
					}
					render->animations.insert(std::pair<std::string, SpriteSheetAnimation>(toString(var->name), anim));
				}
			}
			else if (render->animation == RenderComponent::AnimationType::Armature)
			{
				render->instance.entityName = toString(prefab->rc->spriterEntity);
				render->instance.sceneFile = toString(prefab->rc->spriterScene);
				render->instance.myTextureMap.first = toString(prefab->rc->textureMapMod);
				render->instance.myTextureMap.second = toString(prefab->rc->textureMapName);
			}
			p.base.push_back(render);
		#pragma endregion
		}
		if (toBoolean(prefab->hitbox->isUsed))
		{
		#pragma region hitbox/Rigid
			if (toBoolean(prefab->hitbox->isHitbox))
			{
				HitboxComponent* hitbox = new HitboxComponent();
				hitbox->bounding.position = Vector2(toInt(prefab->hitbox->posX), toInt(prefab->hitbox->posY));
				hitbox->bounding.size = Vector2(toInt(prefab->hitbox->sizeX), toInt(prefab->hitbox->sizeY));
				p.base.push_back(hitbox);
			}
			else
			{
				RigidComponent* rig = new RigidComponent();
				rig->bounding.position = Vector2(toInt(prefab->hitbox->posX), toInt(prefab->hitbox->posY));
				rig->bounding.size = Vector2(toInt(prefab->hitbox->sizeX), toInt(prefab->hitbox->sizeY));
				rig->mass = toInt(prefab->hitbox->mass);
				p.base.push_back(rig);
				//rig->material = material;
			}
		#pragma endregion
		}
		if (toBoolean(prefab->player->isUsed))
		{
			PlayerComponent* player = new PlayerComponent();
			player->setMovementSpeed(toInt(prefab->player->movementSpeed));
			p.base.push_back(player);
		}
		Engine::World.editorPrefabContainer.addPrefab(p);
	}
	List<String^>^ ManagedGame::getAnimations(String^model, String^entity)
	{
		List <String^>^ lst = gcnew List < String ^ >();
		std::vector<std::string> animations = Engine::ModelContainer.getAnimationNames(toString(model), toString(entity));
		for each (std::string var in animations)
		{
			lst->Add(gcnew String(var.c_str()));
		}
		return lst;
	}
	void ManagedGame::setPrefabAnimation(String^ animation)
	{
		mc->setAnimation(toString(animation));
	}
#pragma endregion
#pragma region Quests
	void ManagedGame::addQuest(String ^ Name, String^ Description, UInt32^ID, UInt32^ Coins, List<Objective^> ^Objectives, List<Reward^> ^Rewards)
	{
		if (!isModLoaded())
		{
			addErrorMessage("Cannot add object to non loaded mod");
		}
		else
		{
			Quests::Quest q;
			msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
			q.title = _mc->marshal_as<std::string>(Name);
			q.description = _mc->marshal_as<std::string>(Description);
			q.goldReward = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(Coins)));
			q.ID = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(ID)));
			std::vector<Quests::QuestObjective> obj;
			std::vector<std::pair<std::pair<std::string, unsigned int>, int>> rwd;
			for each (Objective^ var in Objectives)
			{
				Quests::QuestObjective tmp;
				tmp.count = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(var->Count)));
				tmp.description = _mc->marshal_as<std::string>(System::Convert::ToString(var->Description));
				tmp.objectiveName = _mc->marshal_as<std::string>(System::Convert::ToString(var->Name));

				if (!var->IsBonusObjective)
					tmp.isBonusObjective = false;
				else
					tmp.isBonusObjective = true;
				if (var->Target != nullptr)
				{
					tmp.target.first = _mc->marshal_as<std::string>(var->Target->Item1);
					tmp.target.second = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(var->Target->Item2)));
				}
				if (var->DestinationZone != nullptr)
				{
					tmp.destination.first = _mc->marshal_as<std::string>(var->DestinationZone->Item1);
					tmp.destination.second = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(var->DestinationZone->Item2)));

				}
				if (var->TargetDestination != nullptr)
				{
					tmp.targetDestination.first = _mc->marshal_as<std::string>(var->TargetDestination->Item1);
					tmp.targetDestination.second = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(var->TargetDestination->Item2)));
				}
				if (var->Type == "Escort")
					tmp.type = Quests::QuestObjective::Type::Escort;
				else if (var->Type == "Explore")
					tmp.type = Quests::QuestObjective::Type::Explore;
				else if (var->Type == "Kill")
					tmp.type = Quests::QuestObjective::Type::Kill;
				else if (var->Type == "Fetch")
					tmp.type = Quests::QuestObjective::Type::Fetch;

				Console::WriteLine("Add");
				obj.push_back(tmp);
			}
			for each (Reward^var in Rewards)
			{
				std::pair<std::pair<std::string, unsigned int>, int> p;
				int count = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(var->Count)));
				std::string rewardName = _mc->marshal_as<std::string>(var->Item->Item1);
				size_t rewardID = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(var->Item->Item2)));
				p.first.first = rewardName;
				p.first.second = rewardID;
				p.second = count;
				rwd.push_back(p);
			}
			q.objectives = obj;
			q.ItemRewards = rwd;
			Engine::World.AddQuest(q);
		}
	}
	ListViewItem^ ManagedGame::addQuest(String^Name, UInt32^ ID)
	{
		msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
		unsigned int id = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(ID)));
		auto var = Engine::World.EditorAllQuests.find(std::pair<std::string, unsigned int>(Engine::World.openedMod, id));
		if (var != Engine::World.EditorAllQuests.end())
		{
			List<String^>^ list = gcnew List<String^>();
			list->Add(gcnew String(var->second.title.c_str()));
			list->Add(gcnew String(std::to_string(var->second.ID).c_str()));
			list->Add(gcnew String("TYPE"));
			list->Add(gcnew String(var->second.fromMod.c_str()));
			list->Add(gcnew String("Quest"));
			list->Add(gcnew String("A"));
			ListViewItem^ myNewItem = gcnew ListViewItem(list->ToArray(), -1);
			return myNewItem;
		}
		return nullptr;
	}
	int ManagedGame::removeQuest(String^ModName, UInt32^ ID)
	{
		msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
		unsigned int id = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(ID)));
		auto it = Engine::World.EditorAllQuests.find(std::pair<std::string, unsigned int>(_mc->marshal_as<std::string>(ModName), id));
		if (it != Engine::World.EditorAllQuests.end())
		{
			if (it->second.mode == EditorObjectSaveMode::REMOVE)
			{
				it->second.mode = EditorObjectSaveMode::EDIT;
				return 2;
			}
			it->second.mode = EditorObjectSaveMode::REMOVE;
			return 1;
		}
		addErrorMessage("Failed to remove Quest <MODNAME,ID>,<" + ModName + "," + ID + ">");
		return -1;
	}
#pragma endregion
#pragma region Items
	void ManagedGame::addItem(ItemStruct^ item)
	{
		Items::Item* i = new Items::Item();
		delete i;
		if (!isModLoaded())
			addErrorMessage("Cannot add object to non loaded mod");
		else
		{
			msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
			std::string name = _mc->marshal_as<std::string>(item->name);
			std::string description = _mc->marshal_as<std::string>(item->Description);
			std::string icon = _mc->marshal_as<std::string>(item->IconName);
			std::string texture = _mc->marshal_as<std::string>(item->TextureName);
			std::string secondType = _mc->marshal_as<std::string>(item->secondType);
			size_t price = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->price)));
			size_t ID = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->ID)));
			int damage = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->damage)));
			int defense = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->defense)));
			int bagSlots = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->slots)));
			int rarity = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->rarity)));
			bool twoHanded;
			if (item->twoHanded)
				twoHanded = true;
			else
				twoHanded = false;
			double weight = std::stod(_mc->marshal_as<std::string>(System::Convert::ToString(item->weight)));
			std::map<std::string, Vector2> attachPoints;
			for each (auto var in item->attachPoints)
			{
				std::string _n = _mc->marshal_as<std::string>(var.Key);
				int _x = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(var.Value.X)));
				int _y = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(var.Value.X)));
				attachPoints.insert(std::pair<std::string, Vector2>(_n, Vector2(_x, _y)));
			}
			if (item->type == "Ammo")
				if (secondType == "Arrow")
					i = new Items::Ammo(ID, name, icon, weight, price, description, texture, damage, Items::Ammo::Arrow);
				else
					i = new Items::Ammo(ID, name, icon, weight, price, description, texture, damage, Items::Ammo::Bolt);
			else if (item->type == "Armor")
				if (secondType == "Helm")
					i = new Items::Armor(ID, defense, name, icon, weight, price, description, "Helm", texture, attachPoints);
				else if (secondType == "Gloves")
					i = new Items::Armor(ID, defense, name, icon, weight, price, description, "Gloves", texture, attachPoints);
				else if (secondType == "Chest")
					i = new Items::Armor(ID, defense, name, icon, weight, price, description, "Chest", texture, attachPoints);
				else if (secondType == "Leggings")
					i = new Items::Armor(ID, defense, name, icon, weight, price, description, "Leggings", texture, attachPoints);
				else
					i = new Items::Armor(ID, defense, name, icon, weight, price, description, "Boots", texture, attachPoints);
			else if (item->type == "Bag")
				i = new Items::Bag(ID, name, icon, weight, price, description, bagSlots);
			else if (item->type == "Consumable")
				i = new Items::Consumable(ID, name, icon, weight, price, description);
			else if (item->type == "Crafting Material")
				i = new Items::Item(ID, true, name, icon, Items::Item::craftingMaterial, weight, price, description);
			else if (item->type == "Junk")
				i = new Items::Item(ID, true, name, icon, Items::Item::junk, weight, price, description);
			else if (item->type == "Trophy")
				i = new Items::Item(ID, true, name, icon, Items::Item::trophy, weight, price, description);
			else if (item->type == "Undefined")
				i = new Items::Item(ID, true, name, icon, Items::Item::undefined, weight, price, description);
			else
				;// i = new Weapon(ID, true, name, icon, Item::undefined, weight, price, description);
			Engine::World.AddItem(i);
		}
	}
	ListViewItem^ ManagedGame::addItem(String^Name, UInt32^ ID)
	{
		msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
		unsigned int id = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(ID)));
		auto var = Engine::World.EditorAllItems.find(std::pair<std::string, unsigned int>(Engine::World.openedMod, id));
		if (var != Engine::World.EditorAllItems.end())
		{
			List<String^>^ list = gcnew List<String^>();
			list->Add(gcnew String(var->second->getName().c_str()));
			list->Add(gcnew String(std::to_string(var->second->getID()).c_str()));
			list->Add(gcnew String(var->second->getTagAsString().c_str()));
			list->Add(gcnew String(var->second->fromMod.c_str()));
			list->Add(gcnew String("Item"));
			list->Add(gcnew String("A"));
			ListViewItem^ myNewItem = gcnew ListViewItem(list->ToArray(), -1);
			return myNewItem;
		}
		return nullptr;
	}
	int ManagedGame::removeItem(String^ModName, UInt32^ ID)
	{
		msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
		unsigned int id = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(ID)));
		auto it = Engine::World.EditorAllItems.find(std::pair<std::string, unsigned int>(_mc->marshal_as<std::string>(ModName), id));
		if (it != Engine::World.EditorAllItems.end())
		{
			if (it->second->mode == EditorObjectSaveMode::REMOVE)
			{
				it->second->mode = EditorObjectSaveMode::EDIT;
				return 2;
			}
			it->second->mode = EditorObjectSaveMode::REMOVE;
			return 1;
		}
		addErrorMessage("Failed to remove Item <MODNAME,ID>,<" + ModName + "," + ID + ">");
		return -1;
	}
#pragma endregion
#pragma region Messages
	void ManagedGame::addErrorMessage(String^ message)
	{
		ListViewItem::ListViewSubItem^ sub = gcnew ListViewItem::ListViewSubItem();
		sub->Text = message;

		ListViewItem^ li = gcnew ListViewItem();
		li->BackColor = Color::LightCoral;
		li->Text = "Error";
		li->SubItems->Add(sub);
		li->ImageIndex = 0;
		infoMessages->Items->Add(li);
	}
	void ManagedGame::addInfoMessage(String^ message)
	{
		ListViewItem::ListViewSubItem^ sub = gcnew ListViewItem::ListViewSubItem();
		sub->Text = message;
		ListViewItem^ li = gcnew ListViewItem();
		li->BackColor = Color::LightGreen;
		li->Text = "Info";
		li->SubItems->Add(sub);
		li->ImageIndex = 1;
		infoMessages->Items->Add(li);
	}
	void ManagedGame::setMessageWindow(ListView^lv)
	{
		infoMessages = lv;
	}
#pragma endregion
#pragma region Zones
	AddZoneStruct^ ManagedGame::getZone()
	{
		AddZoneStruct^ get = gcnew AddZoneStruct();
		auto var = Engine::World.EditorAllZones.find(Engine::World.lastLoadedZone);
		get->name = gcnew String(var->second.name.c_str());
		get->background = gcnew String(var->second.background.name.c_str());
		get->loadingScreen = gcnew String(var->second.loadingScreen.name.c_str());
		get->loadingScreenMessage = gcnew String(var->second.loadingScreenMessage.c_str());
		get->ID = gcnew UInt32(var->second.ID);
		get->X = gcnew Double(var->second.background.size.x);
		get->Y = gcnew Double(var->second.background.size.y);
		return get;
	}
	void ManagedGame::editZone(AddZoneStruct^ myNewZone, ListView^ lv)
	{
		msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
		std::string name = _mc->marshal_as<std::string>(myNewZone->name);
		std::string desc = _mc->marshal_as<std::string>(myNewZone->loadingScreenMessage);
		std::string bg = _mc->marshal_as<std::string>(myNewZone->background);
		std::string ls = _mc->marshal_as<std::string>(myNewZone->loadingScreen);
		size_t id = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(myNewZone->ID)));
		double x = std::stod(_mc->marshal_as<std::string>(System::Convert::ToString(myNewZone->X)));
		double y = std::stod(_mc->marshal_as<std::string>(System::Convert::ToString(myNewZone->Y)));

		Engine::World.EditorEditZone(name, bg, ls, desc, id, x, y);

		auto var = Engine::World.EditorAllZones.find(std::pair<std::string, size_t>(Engine::World.openedMod, id));
		List<String^>^ list = gcnew List<String^>();
		list->Add(gcnew String(var->first.first.c_str()));
		list->Add(gcnew String(std::to_string(var->first.second).c_str()));
		list->Add(gcnew String(var->second.name.c_str()));
		lv->Items[lv->SelectedIndices[0]] = gcnew ListViewItem(list->ToArray(), -1);
	}
	void ManagedGame::addZone(AddZoneStruct^ myNewZone, ListView^ lv)
	{
		msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
		std::string name = _mc->marshal_as<std::string>(myNewZone->name);
		std::string desc = _mc->marshal_as<std::string>(myNewZone->loadingScreenMessage);
		std::string bg = _mc->marshal_as<std::string>(myNewZone->background);
		std::string ls = _mc->marshal_as<std::string>(myNewZone->loadingScreen);
		size_t id = std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(myNewZone->ID)));
		double x = std::stod(_mc->marshal_as<std::string>(System::Convert::ToString(myNewZone->X)));
		double y = std::stod(_mc->marshal_as<std::string>(System::Convert::ToString(myNewZone->Y)));

		Engine::World.EditorAddNewZone(name, bg, ls, desc, id, x, y);
		Console::WriteLine("All zones Size: {0}", Engine::World.EditorAllZones.size());

		String^str = gcnew String(Engine::World.openedMod.c_str());
		auto var = Engine::World.EditorAllZones.find(std::pair<std::string, size_t>(Engine::World.openedMod, id));
		List<String^>^ list = gcnew List<String^>();
		list->Add(gcnew String(var->first.first.c_str()));
		list->Add(gcnew String(std::to_string(var->first.second).c_str()));
		list->Add(gcnew String(var->second.name.c_str()));
		ListViewItem^ myNewItem = gcnew ListViewItem(list->ToArray(), -1);
		lv->Items->Add(myNewItem);

	}
	void ManagedGame::setUpZonesList(ListView^ lv)
	{
		lv->Items->Clear();
		for each (auto var in Engine::World.EditorAllZones)
		{
			List<String^>^ list = gcnew List<String^>();
			list->Add(gcnew String(var.first.first.c_str()));
			list->Add(gcnew String(std::to_string(var.first.second).c_str()));
			list->Add(gcnew String(var.second.name.c_str()));
			ListViewItem^ myNewItem = gcnew ListViewItem(list->ToArray(), -1);
			lv->Items->Add(myNewItem);
		}
	}
	void ManagedGame::loadZone(String^ name, UInt32^ID, ListView^ lv)
	{
		lv->Items->Clear();
		msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
		Engine::World.loadZone(_mc->marshal_as<std::string>(name), size_t(std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(ID)))));
		Console::WriteLine("size of the zone: ({0},{1})", name, ID);
		for each (auto var in Engine::World.EditorAllZones[std::pair<std::string, size_t>(_mc->marshal_as<std::string>(name), size_t(std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(ID)))))].prefabList)
		{
			List<String^>^ list = gcnew List<String^>();
			list->Add(gcnew String(var.first.first.c_str()));
			list->Add(gcnew String(std::to_string(var.first.second).c_str()));
			list->Add(gcnew String(std::to_string(var.second.ID).c_str()));
			list->Add(gcnew String(var.second.prefabName.c_str()));
			list->Add(gcnew String(var.second.fromMod.c_str()));
			ListViewItem^ myNewItem = gcnew ListViewItem(list->ToArray(), -1);
			lv->Items->Add(myNewItem);
		}
	}
#pragma endregion
#pragma region Mods
	String^ ManagedGame::newMod(String^ modName, List<String^>^ dependencies,Boolean^ isMain)
	{
		msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
		std::vector<std::string> dep;
		std::string name;
		name = _mc->marshal_as<std::string>(modName);
		for each (String^ var in dependencies)
		{
			dep.push_back(_mc->marshal_as<std::string>(var));
		}
		if (toBoolean(isMain))
			Engine::World.newMod(name + ".main", dep);
		else
			Engine::World.newMod(name + ".mod", dep);
		addInfoMessage("Successfully created new mod");
		return gcnew String(Engine::World.openedMod.c_str());
	}
	String^ ManagedGame::loadMod(String^ modToLoad)
	{
		msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
		std::vector<std::string> loadErrors = Engine::World.loadMod(_mc->marshal_as<std::string>(modToLoad));
		if (loadErrors.size() != 0)
			for each (std::string var in loadErrors)
			{
				addErrorMessage(gcnew String(var.c_str()));
			}
		else
			addInfoMessage(gcnew String(Engine::World.openedMod.c_str()) + " loaded with no errors");
		return gcnew String(Engine::World.openedMod.c_str());
	}
	String^ ManagedGame::getLoadedMod()
	{
		return gcnew String(Engine::World.openedMod.c_str());
	}
	void ManagedGame::save()
	{
		std::string myReturn = Engine::World.EditorSave();
		if (myReturn == "<Not Set>")
		{
			addErrorMessage("Cannot save a non loaded Mod");
		}
	}
	void ManagedGame::getDependencies(String^ myMod, ListBox^ dependencies)
	{
		dependencies->Items->Clear();
		msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
		for each(std::string v in Engine::World.getModDependencies(_mc->marshal_as<std::string>(myMod)))
		{
			dependencies->Items->Add(gcnew String(v.c_str()));
		}
		if (dependencies->Items->Count == 0)
			dependencies->Items->Add("<None>");
	}
#pragma endregion
#pragma region Tooltip
	void ManagedGame::setTooltipText(ItemStruct^ item)
	{
		if (item->type == "Ammo")
		{
			if (item->secondType == "Arrow")
			{
				Items::Ammo* _item;
				msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();

				_item = new Items::Ammo(0,
					_mc->marshal_as<std::string>(item->name),
					"test.png", std::stod(_mc->marshal_as<std::string>(System::Convert::ToString(item->weight))),
					std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->price))),
					_mc->marshal_as<std::string>(item->Description),
					"test.png", std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->damage))),
					Items::Ammo::Arrow);
				mc->setTooltipPreview(_item->getName(), _item->toToolTipString());
				delete _item;
			}
			else
			{
				Items::Ammo* _item;
				msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();

				_item = new Items::Ammo(0,
					_mc->marshal_as<std::string>(item->name),
					"test.png", std::stod(_mc->marshal_as<std::string>(System::Convert::ToString(item->weight))),
					std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->price))),
					_mc->marshal_as<std::string>(item->Description),
					"test.png", std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->damage))),
					Items::Ammo::Bolt);
				mc->setTooltipPreview(_item->getName(), _item->toToolTipString());
				delete _item;
			}

		}
		else if (item->type == "Consumable")
		{
			Items::Consumable* _item;
			msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();

			_item = new Items::Consumable(0,
				_mc->marshal_as<std::string>(item->name),
				"test.png", std::stod(_mc->marshal_as<std::string>(System::Convert::ToString(item->weight))),
				std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->price))),
				_mc->marshal_as<std::string>(item->Description));
			mc->setTooltipPreview(_item->getName(), _item->toToolTipString());
			delete _item;
		}
		else if (item->type == "Crafting Material" || item->type == "Trophy" || item->type == "Junk" || item->type == "Undefined")
		{
			Items::Item* _item;
			msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
			Items::Item::ItemType myTag;;
			if (item->type == "Crafting Material")
				myTag = Items::Item::craftingMaterial;
			else if (item->type == "Trophy")
				myTag = Items::Item::trophy;
			else if (item->type == "Junk")
				myTag = Items::Item::junk;
			else
				myTag = Items::Item::undefined;
			_item = new Items::Item(0, false,
				_mc->marshal_as<std::string>(item->name),
				"test.png", myTag, std::stod(_mc->marshal_as<std::string>(System::Convert::ToString(item->weight))),
				std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->price))),
				_mc->marshal_as<std::string>(item->Description));
			mc->setTooltipPreview(_item->getName(), _item->toToolTipString());
			delete _item;
		}
		else if (item->type == "Bag")
		{
			Items::Bag* _item;
			msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
			_item = new Items::Bag(0,
				_mc->marshal_as<std::string>(item->name),
				"test.png", std::stod(_mc->marshal_as<std::string>(System::Convert::ToString(item->weight))),
				std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->price))),
				_mc->marshal_as<std::string>(item->Description),
				std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->slots))));
			mc->setTooltipPreview(_item->getName(), _item->toToolTipString());
			delete _item;
		}
		else if (item->type == "Armor")
		{
			Items::Armor* _item;
			msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
			_item = new Items::Armor(0,
				std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->defense))),
				_mc->marshal_as<std::string>(item->name),
				"test.png", std::stod(_mc->marshal_as<std::string>(System::Convert::ToString(item->weight))),
				std::stoi(_mc->marshal_as<std::string>(System::Convert::ToString(item->price))),
				_mc->marshal_as<std::string>(item->Description), _mc->marshal_as<std::string>(item->secondType), "test.png", {});
			mc->setTooltipPreview(_item->getName(), _item->toToolTipString());
			delete _item;
		}
		else if (item->type == "Weapon")
		{
			mc->setTooltipPreview("<TODO>", "This itemtype have not yet been added to the game");
		}
		else
		{
			mc->setTooltipPreview("<ERR>", "This is awkward...");
		}

	}
	void ManagedGame::setTooltipPreview(IntPtr^ handle)
	{
		mc->setTooltipPreviewHandle((HWND)handle->ToPointer());
	}
#pragma endregion
#pragma region DragDrop
	void ManagedGame::addObjectToGame(ListViewItem^itm, ListView^lv)
	{
		if (Engine::World.lastLoadedZone.second == 0)
		{
			addErrorMessage("Cannot add object to non loaded zone");
		}
		else
		{
			if (itm->SubItems[4]->Text == "Prefab")
			{
				msclr::interop::marshal_context^ _mc = gcnew msclr::interop::marshal_context();
				std::string name = _mc->marshal_as<std::string>(itm->SubItems[3]->Text);
				std::string i = _mc->marshal_as<std::string>(itm->SubItems[1]->Text);
				size_t ii = std::stoi(i);
				auto var = mc->addGameObjectToZone(name, ii);

				List<String^>^ list = gcnew List<String^>();
				list->Add(gcnew String(var.first.first.c_str()));
				list->Add(gcnew String(std::to_string(var.first.second).c_str()));
				list->Add(gcnew String(std::to_string(var.second.ID).c_str()));
				list->Add(gcnew String(var.second.prefabName.c_str()));
				list->Add(gcnew String(var.second.fromMod.c_str()));
				ListViewItem^ myNewItem = gcnew ListViewItem(list->ToArray(), -1);
				lv->Items->Add(myNewItem);
			}
			else
				addInfoMessage("Add Item<TODO>");
		}
	}
#pragma endregion
#pragma region ListView
	void ManagedGame::setUpList(TreeView^ tv)
	{
		for each (auto var in Engine::World.editorPrefabContainer)
		{
			String ^tag = gcnew String(var.second.tag.c_str());
			if (!tv->Nodes["Prefabs"]->Nodes->ContainsKey(tag))
			{
				tv->Nodes["Prefabs"]->Nodes->Add(tag, tag);
			}
		}
		for each (auto var in Engine::World.EditorAllItems)
		{
			String ^tag = gcnew String(var.second->getTagAsString().c_str());
			if (!tv->Nodes["Items"]->Nodes->ContainsKey(tag))
			{
				tv->Nodes["Items"]->Nodes->Add(tag, tag);
				if (tag->Equals("Armor"))
				{
					String ^tag2 = gcnew String(((Items::Armor*)var.second)->armorType.c_str());
					tv->Nodes["Items"]->Nodes[tag]->Nodes->Add(tag2, tag2);
				}
				else if (tag->Equals("Ammo"))
				{
					String ^tag2 = gcnew String(((Items::Ammo*)var.second)->ammoType.c_str());
					tv->Nodes["Items"]->Nodes[tag]->Nodes->Add(tag2, tag2);
				}
				else if (tag->Equals("Weapon"))
				{
					String ^tag2 = gcnew String(((Items::Ammo*)var.second)->ammoType.c_str());
					tv->Nodes["Items"]->Nodes[tag]->Nodes->Add(tag2, tag2);
				}
			}
			else if (tag->Equals("Armor"))
			{
				String ^tag2 = gcnew String(((Items::Armor*)var.second)->armorType.c_str());
				tv->Nodes["Items"]->Nodes[tag]->Nodes->Add(tag2, tag2);
			}
			else if (tag->Equals("Ammo"))
			{
				String ^tag2 = gcnew String(((Items::Ammo*)var.second)->ammoType.c_str());
				tv->Nodes["Items"]->Nodes[tag]->Nodes->Add(tag2, tag2);
			}
		}
	}
	void ManagedGame::setUpDetailedListZone(ListView^ myList)
	{
		myList->Items->Clear();
		for each (auto var in Engine::World.EditorAllZones)
		{
			List<String^>^ list = gcnew List<String^>();
			list->Add(gcnew String(var.second.name.c_str()));
			list->Add(gcnew String(std::to_string(var.first.second).c_str()));
			list->Add("Zone");
			list->Add(gcnew String(var.second.fromMod.c_str()));
			list->Add("Zone");
			ListViewItem^ myNewItem = gcnew ListViewItem(list->ToArray(), -1);
			myList->Items->Add(myNewItem);
		}
	}
	void ManagedGame::setUpDetailedList(String^ tag, String^ path, ListView^ myList)
	{
		myList->Items->Clear();
		if (path->Contains("Prefabs"))
		{
			for each (auto var in Engine::World.editorPrefabContainer)
			{
				if (tag->Equals(gcnew String(var.second.tag.c_str())) || tag->Equals("Prefabs"))
				{
					List<String^>^ list = gcnew List<String^>();
					list->Add(gcnew String(var.second.name.c_str()));
					list->Add(gcnew String(std::to_string(var.second.ID).c_str()));
					list->Add(gcnew String(var.second.tag.c_str()));
					list->Add(gcnew String(var.second.fromMod.c_str()));
					list->Add(gcnew String("Prefab"));
					if (var.second.mode == EditorObjectSaveMode::ADD)
						list->Add(gcnew String("A"));
					else if (var.second.mode == EditorObjectSaveMode::DEFAULT)
						list->Add(gcnew String(""));
					else if (var.second.mode == EditorObjectSaveMode::EDIT)
						list->Add(gcnew String("E"));
					else
						list->Add(gcnew String("D"));
					ListViewItem^ myNewItem = gcnew ListViewItem(list->ToArray(), -1);
					myList->Items->Add(myNewItem);
				}
			}
		}
		else if (path->Contains("Items"))
		{
			for each (auto var in Engine::World.EditorAllItems)
			{
				if (tag->Equals(gcnew String(var.second->getTagAsString().c_str())) || tag->Equals("Items"))
				{
					List<String^>^ list = gcnew List<String^>();
					list->Add(gcnew String(var.second->getName().c_str()));
					list->Add(gcnew String(std::to_string(var.second->getID()).c_str()));
					list->Add(gcnew String(var.second->getTagAsString().c_str()));
					list->Add(gcnew String(var.second->fromMod.c_str()));
					list->Add("Item");
					if (var.second->mode == EditorObjectSaveMode::ADD)
						list->Add(gcnew String("A"));
					else if (var.second->mode == EditorObjectSaveMode::DEFAULT)
						list->Add(gcnew String(""));
					else if (var.second->mode == EditorObjectSaveMode::EDIT)
						list->Add(gcnew String("E"));
					else
						list->Add(gcnew String("D"));
					ListViewItem^ myNewItem = gcnew ListViewItem(list->ToArray(), -1);
					myList->Items->Add(myNewItem);
				}
			}
		}
		else if (path->Contains("Quests"))
		{
			for each (auto var in Engine::World.EditorAllQuests)
			{
				if (tag->Equals("Quests"))
				{
					List<String^>^ list = gcnew List<String^>();
					list->Add(gcnew String(var.second.title.c_str()));
					list->Add(gcnew String(std::to_string(var.second.ID).c_str()));
					list->Add(gcnew String("TYPE"));
					list->Add(gcnew String(var.second.fromMod.c_str()));
					list->Add(gcnew String("Quest"));
					if (var.second.mode == EditorObjectSaveMode::ADD)
						list->Add(gcnew String("A"));
					else if (var.second.mode == EditorObjectSaveMode::DEFAULT)
						list->Add(gcnew String(""));
					else if (var.second.mode == EditorObjectSaveMode::EDIT)
						list->Add(gcnew String("E"));
					else
						list->Add(gcnew String("D"));
					ListViewItem^ myNewItem = gcnew ListViewItem(list->ToArray(), -1);
					myList->Items->Add(myNewItem);
				}
			}
		}
	}
#pragma endregion
}
#endif