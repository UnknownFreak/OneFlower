#ifdef _DEBUG
#ifndef ENGINEQUESTCREATORWINDOW_HPP
#define ENGINEQUESTCREATORWINDOW_HPP
#include <Windows.h>
#include "../../../Vector.h"
#include "../ItemCreator/EngineItemCreatorImageField.hpp"
#include "QuestObjectiveCreator.hpp"
#include "QuestRewardSelector.hpp"
#include "../../../Game/Quest/QuestObjective.hpp"
class EngineQuestCreator
{
public:
	HINSTANCE hInstance;
	HWND hWnd;

	~EngineQuestCreator();
	//EngineItemCreator() = default;
	void start();
	void show();
	void setNextValidID();

	void openRewardWindow(bool edit);
	void openObjectiveWindow(bool edit);

	void addReward();
	void editReward();
	void removeReward();
	void addObjective();
	void editObjective();

	int getCurrentSelectedReward();
	int getCurrentSelectedObjective();

	std::vector<QuestObjective*> objectives;
private:

	std::vector<std::pair<unsigned int, int>> rewards;


	HWND NameHWnd;	   			//Textfield
	HWND NameLabelHWnd;			//Label

	HWND IDLabelHWnd;		  	//Label
	HWND IDHWnd;			  	//Textfiel
	HWND IDButtonHWnd;		  	//Button

	HWND DescriptionHWnd;	  	//Textfield
	HWND DescriptionLabelHWnd;	//Label

	HWND ObjectiveListHWnd;		//ListBox
	HWND ObjectiveListLabelHWnd;//Label

	HWND AddObjectiveButton;	//Button
	HWND RemoveObjectiveButton;	//Button
	HWND EditObjectiveButton;	//Button

	HWND RewardListHWnd;		//ListBox
	HWND RewardListLabelHWnd;	//Label

	HWND AddRewardButton;		//Button
	HWND RemoveRewardButton;	//Button
	HWND EditRewardButton;		//Button

	EngineItemCreatorImageField iconField;
	QuestRewardSelectorWindow rewardsWindow;
	QuestObjectiveCreator objectiveWindow;
	size_t ID;
	Vector2 size;
	WNDCLASSEX wc;
	LPCTSTR windowDefinedName;
};


#endif
#endif