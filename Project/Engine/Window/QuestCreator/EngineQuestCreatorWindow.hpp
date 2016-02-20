#ifdef _DEBUG
#ifndef ENGINEQUESTCREATORWINDOW_HPP
#define ENGINEQUESTCREATORWINDOW_HPP
#include <Windows.h>
#include "../../../Vector.h"
#include "../ItemCreator/EngineItemCreatorImageField.hpp"
#include "QuestRewardSelector.hpp"
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

	void addReward();
	void editReward();
	void removeReward();
	void addObjective();
	void editObjective();

	int getCurrentSelectedReward();


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
	size_t ID;
	Vector2 size;
	WNDCLASSEX wc;
	LPCTSTR windowDefinedName;
};


#endif
#endif