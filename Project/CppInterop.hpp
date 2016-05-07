// ManagedGame.h
#ifndef MANAGEDGAME_HPP
#define MANAGEDGAME_HPP
#endif
#ifdef _EDITOR_
#include "NativeContainer.hpp"
#include "Game\Item\Item.hpp"
#include "Game\Item\Ammo.hpp"
#include "Game\Item\Armor.hpp"
#include "Game\Item\Bag.hpp"
#include "Game\Item\Weapon.hpp"
#include "Game\Item\Consumable.hpp"
#include "Game\Quest\Quest.hpp"
#include "Game\Quest\QuestObjective.hpp"
#include <SFML\Graphics\RenderWindow.hpp>
#include "Game\GUI\ToolTip.hpp"
#include "Game\LoadAndSave\DatabaseIndex.hpp"
#include <msclr\marshal_cppstd.h>

#using <mscorlib.dll>
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace ManagedGame 
{
	public ref class TextureMapPointStruct
	{
	public:
		Tuple<int, int>^ pos = gcnew Tuple<int,int>(0,0);
		Tuple<int, int>^ size = gcnew Tuple<int, int>(0, 0);
		Boolean^ rotated = false;
		int r =255;
		int g = 255;
		int b = 255;

	};
	public ref class SpriteSheetAnimationStruct
	{
	public:
		String^ name = "";
		Double^ time = 0.0;
		Boolean^ loop = false;
		List<Tuple<int, int, int, int>^>^ textureRect = gcnew List<Tuple<int,int,int,int>^>();
	};
	public ref class RenderComponentStruct
	{
	public:
		Boolean^ isUsed = false;
		String^ textureName = "";
		int^ animationType = 0;
		//
		List<SpriteSheetAnimationStruct^>^ animations = gcnew List<SpriteSheetAnimationStruct^>();
		//
		String^ spriterScene = "";
		String^ spriterEntity = "";
		String^ textureMapMod = "";
		String^ textureMapName = "";
	};
	public ref class Hitbox_RigidComponentStruct
	{
	public:
		Boolean ^isUsed = false;
		//if this is false and isUsed is true, this is defining rigidcomponent; 
		Boolean isHitbox = false;

		//MaterialType
		int^ Material = 0;
		int^ mass = 0;
		int^ posX = 0, posY = 0, sizeX = 0, sizeY = 0;

	};
	public ref class PrefabStruct
	{
	public:
		RenderComponentStruct ^rc;
		Hitbox_RigidComponentStruct ^hitbox;
	};
	public ref class ItemStruct
	{
	public:
		System::String^ name;
		System::String^ Description;
		int^ price = 0;
		int^ ID = 0;
		double^ weight = 0.0;
		String^ type;
		int^ damage = 0;
		int^ defense = 0;
		int^ slots = 0;
		String^ secondType;
		String^ TextureName;
		String^ IconName;
		int^ rarity;
		Boolean^ twoHanded;
		Dictionary<String^, Point>^ attachPoints;
	};
	public ref class AddZoneStruct
	{
	public:
		System::String^ name;
		UInt32^ ID;
		Double^ X;
		Double^ Y;
		System::String^ background;
		System::String^ loadingScreen;
		System::String^ loadingScreenMessage;

	};
	public ref class Objective
	{
	public:
		String^ Type;
		Int32^ TypeIndex;
		String^ Name;
		String^ Description;
		Tuple<String^, UInt32>^ Target;
		Tuple<String^, UInt32>^ DestinationZone;
		Tuple<String^, UInt32>^ TargetDestination;
		UInt32^ Count;
		System::Boolean^ IsBonusObjective;
	};
	public ref class Reward
	{
	public: 
		Tuple<String^, UInt32>^ Item;
		String^ Name;
		UInt32^ Count;
	};
	public ref class ManagedGame
	{ 
		// ManagedGame_Messages
		ListView^ infoMessages;
		void addErrorMessage(String^ message);
		void addInfoMessage(String^ message);
	public:
		void setMessageWindow(ListView^lv);
		//ManagedGame
		NativeContainer *mc;
		~ManagedGame();
		bool isModLoaded();
		void TestAdd();
		void ManagedWindowLoop();
		void ManagedQuit();
		void setUpWindows(IntPtr^ handle);
		bool getRightClickedObject();
		void showHideHitboxes();

		//ManagedGame_Zones
		AddZoneStruct^ getZone();
		void editZone(AddZoneStruct^ myNewZone, ListView^ lv);
		void addZone(AddZoneStruct^ myNewZone, ListView^ lv);
		void setUpZonesList(ListView^ lv);
		void loadZone(String^ name, UInt32^ID, ListView^ lv);

		//ManagedGame_Mod
		String^ newMod(String^ modName, List<String^>^ dependencies, Boolean^ isMainFile);
		String^ loadMod(String^ modToLoad);
		String^ getLoadedMod();
		void save();
		void getDependencies(String^ myMod, ListBox^ dependencies);

		//ManagedGame_Tooltip
		void setTooltipText(ItemStruct^ item);
		void setTooltipPreview(IntPtr^ handle);
		//ManagedGame_DragDrop
		void addObjectToGame(ListViewItem^itm, ListView^lv);
		
		//ManagedGame_ListView
		void setUpList(TreeView^ tv);
		void setUpDetailedListZone(ListView^ myList);
		void setUpDetailedList(String^ tag, String^ path, ListView^ myList);

		//ManagedGame_Quests
		void addQuest(String ^ Name, String^ Description, UInt32^ID, UInt32^ Coins, List<Objective^> ^Objectives, List<Reward^> ^Rewards);
		ListViewItem^ addQuest(String^Name, UInt32^ ID);
		int removeQuest(String^name, UInt32^ ID);

		//ManagedGame_Quests
		void addItem(ItemStruct^ item);
		ListViewItem^ addItem(String^Name, UInt32^ ID);
		int removeItem(String^name, UInt32^ ID);

		//ManagedGame_Prefab
		void previewPrefab(PrefabStruct^ prefab);
		void setPrefabPreview(IntPtr^ handle);
		List<String^>^ getEntityNames(String^ model);
		List<String^>^ getSceneFiles();
		void removeSpriterModel(String^ modelFileName);
		List<String^>^ getTextureMaps(String^ model);
		Dictionary<String^, TextureMapPointStruct^>^ getTextureMapPoints(String^ model, String^ modName, String^ textureMap);
		void addTextureMap(String^ model, String^ textureMap);
		void removeTextureMap(String^ model, String^ modName, String^ textureMap);
		void setPointPosition(String^ model, String^ modName, String^ TextureMap, String^ pointName, TextureMapPointStruct^ point);
		List<String^>^ getAnimations(String^model, String^entity);
		void setPrefabAnimation(String^ animationName);
	};
}


#endif